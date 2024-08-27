#include "Modules/Money/Money.h"
#include "Global.h"

#include <ll/api/service/Bedrock.h>

#include "mc/world/actor/player/PlayerScoreSetFunction.h"
#include "mc/world/scores/ScoreInfo.h"
#include "mc/world/scores/ScoreboardId.h"
#include <mc/world/level/Level.h>


#include <LLMoney.h>

namespace TSModule {

Money::Money(std::string& scoreName) : mScoreName(scoreName) {
    if (!scoreName.empty()) return;
    isLLmoney   = false;
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


bool Money::addMoney(Player& player, int money) {
    bool result = false;
    if (mScoreboard && mObjective) {
        result = modifyPlayerScore(player, money, PlayerScoreSetFunction::Add);
    } else if (isLLmoney) {
        result = LLMoney_Add(player.getXuid(), money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
    }
    if (!result) player.sendMessage("§cFailed to add money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
    return result;
}

bool Money::modifyPlayerScore(Player& player, int money, const PlayerScoreSetFunction& function) {
    bool                success;
    const ScoreboardId& id = mScoreboard->getScoreboardId(player);
    mScoreboard->modifyPlayerScore(success, id, *mObjective, money, function);
    return success;
}

bool Money::setMoney(Player& player, int money) {
    bool result = false;
    if (mScoreboard && mObjective) {
        result = modifyPlayerScore(player, money, PlayerScoreSetFunction::Set);
    } else if (isLLmoney) {
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
    } else if (isLLmoney) {
        return LLMoney_Get(player.getXuid());
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        return 0;
    }
}

bool Money::eraseMoney(Player& player, int money) {
    bool result = false;
    if (mScoreboard && mObjective) {
        if (!checkMoney(player, money)) {
            player.sendMessage("§cMoney not enough"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
            return false;
        }
        result = modifyPlayerScore(player, money, PlayerScoreSetFunction::Subtract);
    } else if (isLLmoney) {
        result = LLMoney_Reduce(player.getXuid(), money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    if (!result) player.sendMessage("§cFailed to add money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
    return result;
};

bool Money::transMoney(Player& player, Player& target, int money) {
    bool result = false;
    if (mScoreboard && mObjective) {
        if (!checkMoney(player, money)) {
            player.sendMessage("§cMoney not enough"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
            return false;
        }
        result = modifyPlayerScore(player, money, PlayerScoreSetFunction::Subtract)
              && modifyPlayerScore(target, money, PlayerScoreSetFunction::Add);
    } else if (isLLmoney) {
        result = LLMoney_Trans(player.getXuid(), target.getXuid(), money);
    } else {
        logger.error("No scoreboard or LLMoney"_tr());
        result = false;
    }
    if (!result) player.sendMessage("§cFailed to add money"_tr()); // TODO: 由于玩家数据系统缺失 i18n 搁置
    return result;
}

bool Money::checkMoney(Player& player, int money) { return getMoney(player) >= money; }
}; // namespace TSModule