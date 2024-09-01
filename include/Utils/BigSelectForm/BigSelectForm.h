#pragma once
#include <functional>
#include <string>
#include <vector>

#include <ll/api/form/CustomForm.h>

#define BIG_SELECT_FORM_MAX_BUTTONS_PER_PAGE 2

class Player;
struct BigSelectFormSeacrhInfo {
    // BigSelectFormSeacrhInfo(
    //     std::string&                           searchKey,
    //     size_t                                 page,
    //     size_t                                 maxPage,
    //     std::vector<std::vector<std::string>>& buttons
    // )
    // : mSearchKey(searchKey),
    //   mPage(page),
    //   mMaxPage(maxPage),
    //   mButtons(buttons) {}
    std::string                           mSearchKey = "";
    size_t                                mPage      = SIZE_MAX;
    size_t                                mMaxPage   = SIZE_MAX;
    std::vector<std::vector<std::string>> mButtons{};
};

class BigSelectForm {
private:
    std::string                                                             mTitle;
    std::string                                                             mContent;
    std::vector<std::vector<std::string>>                                   mButtons{}; // 包括页码，从0开始
    std::vector<std::string>                                                mSelectedButtons{};
    std::function<void(Player&, std::vector<std::string>& selectedButtons)> mCallback{[](Player&,
                                                                                         std::vector<std::string>&) {}};


    size_t mPage{0};
    size_t mMaxPage;
    int    mMaxButtonsPerPage{BIG_SELECT_FORM_MAX_BUTTONS_PER_PAGE};

    BigSelectFormSeacrhInfo mSearchInfo{};

public:
    BigSelectForm(const std::string& title, const std::string& content, const std::vector<std::string>& buttons);
    ~BigSelectForm();

    inline void setCallback(const std::function<void(Player&, std::vector<std::string>&)>& callback);
    void        sendToPlayer(Player& pl);
    inline void jumpToPage(size_t page); // 跳转到指定页

    void        startSearch(const std::string& searchKey);
    void        clearSearch();
    inline bool inSearching();

private:
    void makeForm(ll::form::CustomForm& form, Player& pl);
    // tsVec: to select vector
    void handle(
        Player&                           pl,
        const ll::form::CustomFormResult& res,
        ll::form::FormCancelReason,
        std::vector<std::string>& tsVec
    );
};