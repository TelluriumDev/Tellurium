#include "Utils/BigSelectForm/BigSelectForm.h"
#include "Global.h"

#include "mc/world/actor/player/Player.h"

#include <cmath>
#include <stdlib.h>
#include <string>
#include <variant>

// #include "ll/api/event/EventBus.h>
// #include "ll/api/event/player/PlayerJoinEvent.h>
// #include "ll/api/utils/StringUtils.h>

using namespace Tellurium::I18n;

struct BigSelectFormData {
    std::vector<std::vector<std::string>> mButtons;
    size_t                                mMaxPage;
};

BigSelectFormData makeBigSelectFormData(const std::vector<std::string>& buttons, int maxButtonsPerPage) {
    auto mMaxPage = (size_t)floor(buttons.size() / maxButtonsPerPage);
    if (buttons.size() % maxButtonsPerPage != 0) {
        mMaxPage++;
    }
    size_t                                index_buttons = 0;
    size_t                                max_buttons   = buttons.size();
    std::vector<std::vector<std::string>> mButtons{};
    for (size_t i = 0; i < mMaxPage; i++) {
        std::vector<std::string> buttons_p{};
        for (int i_min = 0; i_min != maxButtonsPerPage && index_buttons != max_buttons; i_min++, index_buttons++) {
            buttons_p.push_back(buttons[index_buttons]);
        }
        mButtons.push_back(buttons_p);
    }
    return {mButtons, mMaxPage};
}


size_t stringIndexOf(const std::string& str, const std::string& target) {
    auto it = std::search(str.begin(), str.end(), target.begin(), target.end());
    if (it != str.end()) {
        return (size_t)std::distance(str.begin(), it);
    } else {
        return SIZE_MAX;
    }
}

BigSelectForm::BigSelectForm(
    const std::string&              title,
    const std::string&              content,
    const std::vector<std::string>& buttons
)
: mTitle(title),
  mContent(content) {
    auto data = makeBigSelectFormData(buttons, mMaxButtonsPerPage);
    mButtons  = data.mButtons;
    mMaxPage  = data.mMaxPage;
}

BigSelectForm::~BigSelectForm() { logger.debug("BigSelectdForm estruction..."); }

inline void BigSelectForm::setCallback(const std::function<void(Player&, std::vector<std::string>&)>& callback) {
    mCallback = callback;
}

void BigSelectForm::sendToPlayer(Player& pl) {
    auto form = ll::form::CustomForm();
    makeForm(form, pl);
    // auto handleFunc = handle;
    form.sendTo(
        pl,
        [_this = this, searchInfo = this->mSearchInfo, buttons = this->mButtons, page = this->mPage](
            Player&                           pl,
            const ll::form::CustomFormResult& res,
            ll::form::FormCancelReason        reason
        ) -> void {
            auto inSearching = _this->inSearching();
            auto v           = inSearching ? searchInfo.mButtons[searchInfo.mPage] : buttons[page];
            _this->handle(pl, res, reason, v);
        }
    );
}

void BigSelectForm::makeForm(ll::form::CustomForm& form, Player& pl) {
    form.setTitle(mTitle);
    form.appendLabel(mContent);
    form.appendInput("SearchContent", translate("§l§bSearch", pl), "(String)", mSearchInfo.mSearchKey);
    // std::string tr1 = translate("§l§bPage: {0}/{1}", pl);

    auto tr1 = fmt::format(
        "§l§bPage: {0}/{1}",
        inSearching() ? mSearchInfo.mPage + 1 : mPage + 1,
        inSearching() ? mSearchInfo.mMaxPage : mMaxPage
    );
    form.appendSlider(
        "PageSelector",
        tr1,
        1.00,
        double(inSearching() ? mSearchInfo.mMaxPage : mMaxPage),
        1.00,
        double(inSearching() ? mSearchInfo.mPage + 1 : mPage + 1)
    );
    std::string selects = "";
    for (auto& button : mSelectedButtons) {
        if (selects == "") {
            selects = button;
        } else {
            selects += ", " + button;
        }
    }
    // std::string tr2 = translate("§l§bSelected: {0}", pl);

    auto tr2 = fmt::format("§l§bSelected: {0}", selects);
    form.appendLabel(tr2);
    int index = 0;
    for (auto& button : (inSearching() ? mSearchInfo.mButtons[mSearchInfo.mPage] : mButtons[mPage])) { // 能用！别动！
        // logger.info("Button" + std::to_string(index));
        form.appendToggle(
            "Button" + std::to_string(index),
            button,
            std::count(mSelectedButtons.begin(), mSelectedButtons.end(), button) != 0
        );
        index++;
    }
    form.appendToggle("Enter", translate("§l§bEnter", pl), false);
}

inline void BigSelectForm::jumpToPage(size_t page) {
    if (page < (inSearching() ? mSearchInfo.mMaxPage : mMaxPage)) {
        if (inSearching()) {
            mSearchInfo.mPage = page;
        } else {
            mPage = page;
        }
    }
}

inline bool BigSelectForm::inSearching() { return mSearchInfo.mSearchKey != ""; }

void BigSelectForm::startSearch(const std::string& searchKey) {
    mPage = 0;

    mSearchInfo.mSearchKey = searchKey;
    mSearchInfo.mPage      = 0;
    std::vector<std::pair<std::string, size_t>> res;
    for (auto& buttons : mButtons) {
        for (auto& button : buttons) {
            auto index = stringIndexOf(button, searchKey);
            if (index != SIZE_MAX) {
                res.push_back({button, index});
            }
        }
    }
    qsort(res.data(), res.size(), sizeof(std::pair<std::string, size_t>), [](const void* a, const void* b) -> int {
        auto a_ = *(std::pair<std::string, size_t>*)a;
        auto b_ = *(std::pair<std::string, size_t>*)b;
        if (a_.second < b_.second) return -1;
        // if (a_.second > b_.second) return 1;
        return 1;
    });
    std::vector<std::string> res1{};
    for (auto& i : res) {
        res1.push_back(i.first);
    }
    auto searchInfo      = makeBigSelectFormData(res1, mMaxButtonsPerPage);
    mSearchInfo.mButtons = searchInfo.mButtons;
    mSearchInfo.mMaxPage = searchInfo.mMaxPage;
}

void BigSelectForm::clearSearch() {
    mSearchInfo.mSearchKey = "";
    mSearchInfo.mPage      = SIZE_MAX;
    mSearchInfo.mMaxPage   = SIZE_MAX;
    mSearchInfo.mButtons.clear();
}
// tsVec: to select vector
void BigSelectForm::handle(
    Player&                           pl,
    const ll::form::CustomFormResult& res,
    ll::form::FormCancelReason,
    std::vector<std::string>& tsVec
) {
    if (!res.has_value()) {
        pl.sendMessage(translate("§l§bYou have giveup the form.", pl));
        return;
    }
    size_t index = 0;
    for (auto& button : tsVec) {
        // logger.info("Button" + std::to_string(index));
        auto& swi = std::get<uint64>(res->at("Button" + std::to_string(index)));
        if (swi == 1 && std::count(mSelectedButtons.begin(), mSelectedButtons.end(), button) == 0) {
            mSelectedButtons.push_back(button);
        } else if (swi == 0 && std::count(mSelectedButtons.begin(), mSelectedButtons.end(), button) == 1) {
            mSelectedButtons.erase(
                std::remove(mSelectedButtons.begin(), mSelectedButtons.end(), button),
                mSelectedButtons.end()
            );
        }
        index++;
    }
    auto& search = std::get<std::string>(res->at("SearchContent"));
    if (search == "") { // 搜索功能直接跳转
        if (inSearching()) {
            clearSearch();
            return sendToPlayer(pl);
        }
    } else if (mSearchInfo.mSearchKey != search) {
        clearSearch(); // 复位重新搜索
        startSearch(search);
        return sendToPlayer(pl);
    }
    auto& page = std::get<double>(res->at("PageSelector"));
    jumpToPage(size_t(page - 1));

    auto& enter = std::get<uint64>(res->at("Enter"));
    if (enter == 1) {
        mCallback(pl, mSelectedButtons);
    } else {
        sendToPlayer(pl);
    }
}