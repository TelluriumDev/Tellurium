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

#include <LLMoney.h>
#include <string>

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
        result = LLMoney_Add(ll::service::PlayerInfo::getInstance().fromUuid(uuid)->xuid, money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
    }
    // if (!result) player.sendMessage("§cFailed to add money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
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
        result = LLMoney_Set(ll::service::PlayerInfo::getInstance().fromUuid(uuid)->xuid, money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    // if (!result) player.sendMessage("§cFailed to set money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
    return result;
}


long long Money::getMoney(const mce::UUID& uuid) {
    if (mScoreboard && mObjective) {
        const ScoreboardId& id    = getOrCreatePlayerScoreId(uuid);
        int                 money = mObjective->getPlayerScore(id).mScore;
        return money;
    } else if (isLLMoney) {
        // return LLMoney_Get(actorUniqueid);
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
            // player.sendMessage("§cMoney not enough"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
            return false;
        }
        result = modifyPlayerScore(uuid, money, PlayerScoreSetFunction::Subtract).value();
    } else if (isLLMoney) {
        result = LLMoney_Reduce(ll::service::PlayerInfo::getInstance().fromUuid(uuid)->xuid, money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    // if (!result) player.sendMessage("§cFailed to add money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
    return result;
};

bool Money::transMoney(const mce::UUID& uuid, const mce::UUID& uuid2, long long money, const std::string& note) {
    auto event = TLEvent::MoneyTransEvent(uuid, uuid2, money, note);
    EventBus::getInstance().publish(event);
    if (event.isCancelled()) return false;
    bool result = false;
    if (mScoreboard && mObjective) {
        if (!checkMoney(uuid, money)) {
            // player.sendMessage("§cMoney not enough"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
            return false;
        }
        result = modifyPlayerScore(uuid, money, PlayerScoreSetFunction::Subtract)
              && modifyPlayerScore(uuid2, money, PlayerScoreSetFunction::Add);
    } else if (isLLMoney) {
        result = LLMoney_Trans(
            ll::service::PlayerInfo::getInstance().fromUuid(uuid)->xuid,
            ll::service::PlayerInfo::getInstance().fromUuid(uuid2)->xuid,
            money
        );
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    // if (!result) player.sendMessage("§cFailed to add money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
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
