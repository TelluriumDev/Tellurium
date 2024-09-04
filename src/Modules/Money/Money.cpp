#include "Modules/Money/Money.h"
#include "Event/MoneyEvent/MoneyAddEvent.h"
#include "Event/MoneyEvent/MoneyReduceEvent.h"
#include "Event/MoneyEvent/MoneySetEvent.h"
#include "Event/MoneyEvent/MoneyTransEvent.h"
#include "Global.h" // IWYU pragma: keep

#include <ll/api/event/EventBus.h>
#include <ll/api/service/Bedrock.h>


#include <mc/world/actor/player/PlayerScoreSetFunction.h>
#include <mc/world/level/Level.h>
#include <mc/world/scores/ScoreInfo.h>
#include <mc/world/scores/ScoreboardId.h>


#include <LLMoney.h>

using namespace ll::event;

namespace TLModule {

Money::Money(std::string& scoreName) : mScoreName(scoreName) {
    if (!scoreName.empty()) return;
    isLLMoney   = false;
    mScoreboard = &ll::service::getLevel()->getScoreboard();
    mObjective  = mScoreboard->getObjective(scoreName);
    if (mObjective == nullptr) {
        logger.warn("Scoreboard objective {} not found, will create"_tr(scoreName));
        mObjective = mScoreboard->addObjective(
            scoreName,
            scoreName,
            *const_cast<ObjectiveCriteria*>(mScoreboard->getCriteria("dummy"))
        );
    }
    // 如果 scoreboard 也为空 这里并不考虑继续使用 LLMoney 而是直接废除经济系统
};


bool Money::addMoney(Player& player, long long money, const std::string& note) {
    auto event = TLEvent::MoneyAddEvent(&player, money, note);
    EventBus::getInstance().publish(event);
    if (event.isCancelled()) return false;
    bool result = false;
    if (mScoreboard && mObjective) {
        result = modifyPlayerScore(player, money, PlayerScoreSetFunction::Add);
    } else if (isLLMoney) {
        result = LLMoney_Add(player.getXuid(), money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
    }
    if (!result) player.sendMessage("§cFailed to add money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
    return result;
}

bool Money::modifyPlayerScore(Player& player, long long money, const PlayerScoreSetFunction& function) {
    bool                success;
    const ScoreboardId& id = mScoreboard->getScoreboardId(player);
    mScoreboard->modifyPlayerScore(success, id, *mObjective, (int)money, function);
    return success;
}

bool Money::setMoney(Player& player, long long money, const std::string& note) {
    auto event = TLEvent::MoneySetEvent(&player, money, note);
    EventBus::getInstance().publish(event);
    if (event.isCancelled()) return false;
    bool result = false;
    if (mScoreboard && mObjective) {
        result = modifyPlayerScore(player, money, PlayerScoreSetFunction::Set);
    } else if (isLLMoney) {
        result = LLMoney_Set(player.getXuid(), money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    if (!result) player.sendMessage("§cFailed to set money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
    return result;
}

long long Money::getMoney(Player& player) {
    if (mScoreboard && mObjective) {
        const ScoreboardId& id    = mScoreboard->getScoreboardId(player);
        int                 money = mObjective->getPlayerScore(id).mScore;
        return money;
    } else if (isLLMoney) {
        return LLMoney_Get(player.getXuid());
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        return 0;
    }
}

bool Money::reduceMoney(Player& player, long long money, const std::string& note) {
    auto event = TLEvent::MoneyReduceEvent(&player, money, note);
    EventBus::getInstance().publish(event);
    if (event.isCancelled()) return false;
    bool result = false;
    if (mScoreboard && mObjective) {
        if (!checkMoney(player, money)) {
            player.sendMessage("§cMoney not enough"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
            return false;
        }
        result = modifyPlayerScore(player, money, PlayerScoreSetFunction::Subtract);
    } else if (isLLMoney) {
        result = LLMoney_Reduce(player.getXuid(), money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    if (!result) player.sendMessage("§cFailed to add money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
    return result;
};

bool Money::transMoney(Player& player, Player& target, long long money, const std::string& note) {
    auto event = TLEvent::MoneyTransEvent(&player, &target, money, note);
    EventBus::getInstance().publish(event);
    if (event.isCancelled()) return false;
    bool result = false;
    if (mScoreboard && mObjective) {
        if (!checkMoney(player, money)) {
            player.sendMessage("§cMoney not enough"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
            return false;
        }
        result = modifyPlayerScore(player, money, PlayerScoreSetFunction::Subtract)
              && modifyPlayerScore(target, money, PlayerScoreSetFunction::Add);
    } else if (isLLMoney) {
        result = LLMoney_Trans(player.getXuid(), target.getXuid(), money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    if (!result) player.sendMessage("§cFailed to add money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
    return result;
}

bool Money::checkMoney(Player& player, long long money) { return getMoney(player) >= money; }
}; // namespace TLModule