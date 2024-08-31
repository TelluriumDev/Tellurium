#include "Modules/Money/Money.h"
#include "Event/MoneyEvent/MoneyAddEvent.h"
#include "Event/MoneyEvent/MoneyReduceEvent.h"
#include "Event/MoneyEvent/MoneySetEvent.h"
#include "Event/MoneyEvent/MoneyTransEvent.h"
#include "Global.h" // IWYU pragma: keep

#include <ll/api/event/EventBus.h>
#include <ll/api/service/Bedrock.h>

#include <mc/server/commands/MinecraftCommands.h>
#include <mc/world/Minecraft.h>
#include <mc/world/actor/player/PlayerScoreSetFunction.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/storage/DBStorage.h>
#include <mc/world/scores/PlayerScoreboardId.h>
#include <mc/world/scores/ScoreInfo.h>

#include <LLMoney.h>

using namespace ll::event;

namespace TLModule {

Money::Money(std::string& scoreName) : mScoreName(scoreName) {
    if (scoreName.empty()) return;
    isLLmoney   = false;
    mScoreboard = &ll::service::getLevel()->getScoreboard();
    mObjective  = mScoreboard->getObjective(scoreName);
    if (mObjective == nullptr) {
        logger.warn("Scoreboard objective {0} not found, will create"_tr(scoreName));
        mObjective = mScoreboard->addObjective(scoreName, scoreName, *mScoreboard->getCriteria("dummy"));
    }
};

Money::Money() {}

bool Money::setMoney(Player& player, int money, std::string& note, ::MoneySetOptions option) {
    auto event = TLEvent::MoneySetEvent(&player, money, note, option);
    ll::event::EventBus::getInstance().publish(event);
    if (event.isCancelled() && option != sync) {
        return false;
    }
    if (isLLmoney) {
        return LLMoney_Set(player.getXuid(), money); // 就让LLMoney处理去吧
    }
    return setPlayerScore(player, money);
}

bool Money::setMoney(mce::UUID& playerUUID, int money, std::string& note, ::MoneySetOptions option) {
    auto pl = ll::service::getLevel()->getPlayer(playerUUID);
    if (pl != nullptr) {
        return setMoney(*pl, money, note, option);
    }
    //
    return false;
}


ScoreboardId* Money::getOrCreatePlayerScoreId(Player& player) {
    // ll::service::getLevel()->getLevelStorage().getCompoundTag()
    if (mScoreboard->mObjectives.find(mScoreName) == mScoreboard->mObjectives.end()) {
        logger.warn("Scoreboard objective {0} not found, will create"_tr(mScoreName));
        mObjective = mScoreboard->addObjective(mScoreName, mScoreName, *mScoreboard->getCriteria("dummy"));
    }
    ScoreboardId& id = (ScoreboardId&)mScoreboard->getScoreboardId(player);
    if (!id.isValid()) {
        id = mScoreboard->createScoreboardId(player);
    } else if (!id.isValid()) { // 非有效使用命令创建
        logger.debug("Player {0} ScoreboardId create failed, will use command to create", player.getName());
        // runcmdEx
        id = mScoreboard->getScoreboardId(player);
        if (!id.isValid()) {
            logger.error("Player {0} ScoreboardId create failed!!!", player.getName());
            return nullptr;
        }
    }
    return &id;
}
bool Money::setPlayerScore(Player& player, int money) {
    bool success;
    auto id = getOrCreatePlayerScoreId(player);
    if (id == nullptr) {
        return false;
    }
    mScoreboard->modifyPlayerScore(success, *id, *mObjective, money, ::PlayerScoreSetFunction::Set);
    return success;
}
bool Money::getOfflinePlayerNbt(mce::UUID&) {
    // DBStorage& storage = ll::service::getLevel()->getLevelStorage();

    return true;
}
// bool Money::checkMoney(Player& player, int money) { return getMoney(player) >= money; }
// bool Money::checkMoney(mce::UUID& player, int money) { return getMoney(player) >= money; }

}; // namespace TLModule