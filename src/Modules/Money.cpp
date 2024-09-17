#include "Modules/Money.h"
#include "Event/MoneyEvent/MoneyAddEvent.h"
#include "Event/MoneyEvent/MoneyReduceEvent.h"
#include "Event/MoneyEvent/MoneySetEvent.h"
#include "Event/MoneyEvent/MoneyTransEvent.h"
#include "Global.h"

#include "ll/api/event/EventBus.h"
#include "ll/api/service/Bedrock.h"
#include "ll/api/service/PlayerInfo.h"

#include "mc/deps/core/mce/UUID.h"
#include "mc/world/ActorUniqueID.h"
#include "mc/world/actor/player/PlayerScoreSetFunction.h"
#include "mc/world/level/Level.h"
#include "mc/world/scores/PlayerScoreboardId.h"
#include "mc/world/scores/ScoreInfo.h"
#include "mc/world/scores/ScoreboardId.h"

#include <windows.h>

using namespace ll::event;

namespace TLModule {

Money::Money(const std::string& scoreName) : mScoreName(scoreName) {
    if (scoreName.empty()) return;
    isLLMoney   = false;
    mScoreboard = &ll::service::getLevel()->getScoreboard();
    mObjective  = mScoreboard->getObjective(scoreName);
    if (mObjective == nullptr) {
        logger.warn("Scoreboard objective {} not found, will create"_tr(scoreName));
        mObjective = mScoreboard->addObjective(scoreName, scoreName, *mScoreboard->getCriteria("dummy"));
    }
    // 如果 scoreboard 也为空 这里并不考虑继续使用 LLMoney 而是直接废除经济系统
};


bool Money::addMoney(const mce::UUID& uuid, long long money, const std::string& note) {
    auto event = TLEvent::MoneyAddEvent(uuid, money, note);
    EventBus::getInstance().publish(event);
    if (event.isCancelled()) return false;
    bool result = false;
    if (mScoreboard && mObjective) {
        result = modifyPlayerScore(uuid, money, PlayerScoreSetFunction::Add).value();
    } else if (isLLMoney) {
        result = LegacyMoney::add(ll::service::PlayerInfo::getInstance().fromUuid(uuid)->xuid, money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
    }
    return result;
}

std::optional<int>
Money::modifyPlayerScore(const mce::UUID& uuid, long long money, const PlayerScoreSetFunction& function) {
    bool                success;
    const ScoreboardId& id  = getOrCreatePlayerScoreId(uuid);
    auto                res = mScoreboard->modifyPlayerScore(success, id, *mObjective, (int)money, function);
    if (success) return res;
    return {};
}

bool Money::setMoney(const mce::UUID& uuid, long long money, const std::string& note) {
    auto event = TLEvent::MoneySetEvent(uuid, money, note);
    EventBus::getInstance().publish(event);
    if (event.isCancelled()) return false;
    bool result = false;
    if (mScoreboard && mObjective) {
        result = modifyPlayerScore(uuid, money, PlayerScoreSetFunction::Set).value();
    } else if (isLLMoney) {
        result = LegacyMoney::set(ll::service::PlayerInfo::getInstance().fromUuid(uuid)->xuid, money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    return result;
}


long long Money::getMoney(const mce::UUID& uuid) {
    if (mScoreboard && mObjective) {
        const ScoreboardId& id    = getOrCreatePlayerScoreId(uuid);
        int                 money = mObjective->getPlayerScore(id).mScore;
        return money;
    } else if (isLLMoney) {
        return LegacyMoney::get(uuid);
        return 0;
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        return 0;
    }
}


bool Money::reduceMoney(const mce::UUID& uuid, long long money, const std::string& note) {
    auto event = TLEvent::MoneyReduceEvent(uuid, money, note);
    EventBus::getInstance().publish(event);
    if (event.isCancelled()) return false;
    bool result = false;
    if (mScoreboard && mObjective) {
        if (!checkMoney(uuid, money)) {
            return false;
        }
        result = modifyPlayerScore(uuid, money, PlayerScoreSetFunction::Subtract).value();
    } else if (isLLMoney) {
        result = LegacyMoney::add(ll::service::PlayerInfo::getInstance().fromUuid(uuid)->xuid, money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    return result;
};

bool Money::transMoney(const mce::UUID& uuid, const mce::UUID& uuid2, long long money, const std::string& note) {
    auto event = TLEvent::MoneyTransEvent(uuid, uuid2, money, note);
    EventBus::getInstance().publish(event);
    if (event.isCancelled()) return false;
    bool result = false;
    if (mScoreboard && mObjective) {
        if (!checkMoney(uuid, money)) {
            return false;
        }
        result = modifyPlayerScore(uuid, money, PlayerScoreSetFunction::Subtract)
              && modifyPlayerScore(uuid2, money, PlayerScoreSetFunction::Add);
    } else if (isLLMoney) {
        result = LegacyMoney::trans(uuid, uuid2, money, note);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    return result;
}

bool Money::checkMoney(const mce::UUID& uuid, long long money) { return getMoney(uuid) >= money; }

const ScoreboardId& Money::getOrCreatePlayerScoreId(const mce::UUID& uuid) {
    const auto  uniqueId = ActorUniqueID::fromUUID(uuid);
    auto        psid     = PlayerScoreboardId(uniqueId.id);
    const auto& id       = mScoreboard->getScoreboardId(psid);
    if (!id.isValid()) {
        auto fakeid = mScoreboard->createScoreboardId(std::to_string(psid.mActorUniqueId));
        if (uniqueId.id != ActorUniqueID::INVALID_ID.id) {
            return mScoreboard->mIdentityDict.convertFakeToReal(fakeid, psid);
        }
    }
    return id;
}

}; // namespace TLModule


namespace LegacyMoney {

const wchar_t* fileName = L"LegacyMoney.dll";

bool isValid() { return GetModuleHandle(fileName) != nullptr; }

std::vector<std::pair<std::string, long long>> ranking(ushort num) {
    try {
        return ((std::vector<std::pair<std::string, long long>> (*)(ushort))GetProcAddress(
        GetModuleHandle(fileName),
        "?LLMoney_Ranking@@YA?AV?$vector@U?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_J@std@@"
        "V?$allocator@U?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_J@std@@@2@@std@@G@Z"
    ))(num);
    } catch (...) {
        return std::vector<std::pair<std::string, long long>>();
    }
}

bool add(std::string xuid, long long money) {
    try {
        return ((bool (*)(std::string, long long)
        )GetProcAddress(GetModuleHandle(fileName), "LLMoney_Add"))(xuid, money);
    } catch (...) {
        return false;
    }
}

void clearHist(int difftime) {
    try {
        ((void (*)(int))GetProcAddress(GetModuleHandle(fileName), "LLMoney_ClearHist"))(difftime);
    } catch (...) {}
}

long long get(std::string xuid) {
    try {
        return ((long long (*)(std::string))GetProcAddress(GetModuleHandle(fileName), "LLMoney_Get"))(xuid);
    } catch (...) {
        return 0;
    }
}

std::string getHist(std::string xuid, int timediff) {
    try {
        return ((std::string(*)(std::string, int)
        )GetProcAddress(GetModuleHandle(fileName), "LLMoney_GetHist"))(xuid, timediff);
    } catch (...) {
        return "";
    }
}

bool reduce(std::string xuid, long long money) {
    try {
        return ((bool (*)(std::string, long long)
        )GetProcAddress(GetModuleHandle(fileName), "LLMoney_Reduce"))(xuid, money);
    } catch (...) {
        return false;
    }
}

bool set(std::string xuid, long long money) {
    try {
        return ((bool (*)(std::string, long long)
        )GetProcAddress(GetModuleHandle(fileName), "LLMoney_Set"))(xuid, money);
    } catch (...) {
        return false;
    }
}

bool trans(std::string from, std::string to, long long val, std::string const& note) {
    try {
        return ((bool (*)(std::string, std::string, long long, std::string const&)
        )GetProcAddress(GetModuleHandle(fileName), "LLMoney_Trans"))(from, to, val, note);
    } catch (...) {
        return false;
    }
}

void listenAfterEvent(LLMoneyAfterEventCallback callback) {
    try {
        ((void (*)(LLMoneyAfterEventCallback)
        )GetProcAddress(GetModuleHandle(fileName), "LLMoney_ListenAfterEvent"))(callback);
    } catch (...) {}
}

void listenBeforeEvent(LLMoneyBeforeEventCallback callback) {
    try {
        ((void (*)(LLMoneyBeforeEventCallback)
        )GetProcAddress(GetModuleHandle(fileName), "LLMoney_ListenBeforeEvent"))(callback);
    } catch (...) {}
}

std::string getXuidFromUuid(mce::UUID const& uuid, std::string const& defaultValue) {
    try {
        return ll::service::PlayerInfo::getInstance().fromUuid(uuid)->xuid;
    } catch (...) {
        return defaultValue;
    }
}

bool add(mce::UUID uuid, long long money) { return add(getXuidFromUuid(uuid), money); }

bool reduce(mce::UUID uuid, long long money) { return reduce(getXuidFromUuid(uuid), money); }

bool set(mce::UUID uuid, long long money) { return set(getXuidFromUuid(uuid), money); }

std::string getHist(mce::UUID uuid, int timediff) { return getHist(getXuidFromUuid(uuid), timediff); }

bool trans(mce::UUID from, mce::UUID to, long long val, std::string const& note) {
    return trans(getXuidFromUuid(from), getXuidFromUuid(to), val, note);
}

long long get(mce::UUID uuid) { return get(getXuidFromUuid(uuid)); }
} // namespace LegacyMoney
