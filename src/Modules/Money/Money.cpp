#include "Modules/Money/Money.h"
#include "Event/MoneyEvent/MoneyAddEvent.h"
#include "Event/MoneyEvent/MoneyReduceEvent.h"
#include "Event/MoneyEvent/MoneySetEvent.h"
#include "Event/MoneyEvent/MoneyTransEvent.h"
#include "Global.h"


#include <ll/api/event/EventBus.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/service/Bedrock.h>
#include <ll/api/service/PlayerInfo.h>

// #include <mc/nbt.h>
#include <mc/server/commands/CommandContext.h>
#include <mc/server/commands/CommandPermissionLevel.h>
#include <mc/server/commands/MinecraftCommands.h>
#include <mc/server/commands/ServerCommandOrigin.h>
#include <mc/world/Minecraft.h>
#include <mc/world/actor/player/PlayerScoreSetFunction.h>
#include <mc/world/level/Level.h>
#include <mc/world/scores/PlayerScoreboardId.h>
#include <mc/world/scores/ScoreInfo.h>

#include <LLMoney.h>

using namespace ll::event;

std::string UUID2XUID(const mce::UUID& uuid) {
    auto info = ll::service::PlayerInfo::getInstance().fromUuid(uuid);
    return info->xuid;
}
namespace TLModule {

Money::Money(std::string& scoreName) : mScoreName(scoreName) {
    if (scoreName.empty()) return;
    isLLMoney   = false;
    mScoreboard = &ll::service::getLevel()->getScoreboard();
    mObjective  = mScoreboard->getObjective(scoreName);
    if (mObjective == nullptr) {
        logger.warn("Scoreboard objective {0} not found, will create"_tr(scoreName));
        mObjective = mScoreboard->addObjective(scoreName, scoreName, *mScoreboard->getCriteria("dummy"));
    }
    logger.debug("Money module loaded!");
    // auto _this = this;
}

Money::Money() { logger.debug("Money module loaded2!"); }

Money::~Money() { logger.debug("Money module unloaded!"); }

long long Money::getMoney(Player& player) {
    if (isLLMoney) {
        return LLMoney_Get(player.getXuid());
    }
    return getPlayerScore(player);
}
long long Money::getMoney(const mce::UUID& playerUUID) {
    auto pl = ll::service::getLevel()->getPlayer(playerUUID);
    if (pl != nullptr) {
        return getMoney(*pl);
    }
    return getPlayerScore(playerUUID);
}

bool Money::setMoney(Player& player, int money, const std::string& note, ::MoneySetOptions option) {
    auto event = TLEvent::MoneySetEvent(&player, money, *const_cast<std::string*>(&note), option);
    ll::event::EventBus::getInstance().publish(event);
    if (event.isCancelled() && option != sync) {
        return false;
    }
    if (isLLMoney) {
        return LLMoney_Set(player.getXuid(), money); // 就让LLMoney处理去吧
    }
    if (option != pay) { // 记录
        // TODO Hist
    }
    return setPlayerScore(player, money);
}
bool Money::setMoney(const mce::UUID& playerUUID, int money, const std::string& note, ::MoneySetOptions option) {
    auto pl = ll::service::getLevel()->getPlayer(playerUUID);
    if (pl != nullptr) {
        return setMoney(*pl, money, note, option);
    }
    auto event = TLEvent::MoneySetEvent(playerUUID, money, note, option);
    ll::event::EventBus::getInstance().publish(event);
    if (event.isCancelled() && option != sync) {
        return false;
    }
    if (option != pay) { // 记录
        // TODO Hist
    }
    return setPlayerScore(playerUUID, money);
}

bool Money::addMoney(Player& player, int money, const std::string& note) {
    auto event = TLEvent::MoneyAddEvent(&player, money, *const_cast<std::string*>(&note));
    ll::event::EventBus::getInstance().publish(event);
    if (event.isCancelled()) {
        return false;
    }
    if (isLLMoney) {
        return LLMoney_Add(player.getXuid(), money); // 就让LLMoney处理去吧,就不做统一api了
    }
    return setMoney(player, int(getMoney(player) + money), note, set);
}
bool Money::addMoney(const mce::UUID& playerUUID, int money, const std::string& note) {
    auto pl = ll::service::getLevel()->getPlayer(playerUUID);
    if (pl != nullptr) {
        return addMoney(*pl, money, note);
    }
    auto event = TLEvent::MoneyAddEvent(playerUUID, money, note);
    ll::event::EventBus::getInstance().publish(event);
    if (event.isCancelled()) {
        return false;
    }
    return setMoney(playerUUID, int(getMoney(playerUUID) + money), note, set);
}

bool Money::reduceMoney(Player& player, int money, const std::string& note) {
    auto event = TLEvent::MoneyReduceEvent(&player, money, note);
    ll::event::EventBus::getInstance().publish(event);
    if (event.isCancelled()) {
        return false;
    }
    if (isLLMoney) {
        return LLMoney_Reduce(player.getXuid(), money); // 就让LLMoney处理去吧,就不做统一api了
    }
    return setMoney(player, int(getMoney(player) - money), note, set);
}
bool Money::reduceMoney(const mce::UUID& playerUUID, int money, const std::string& note) {
    auto pl = ll::service::getLevel()->getPlayer(playerUUID);
    if (pl != nullptr) {
        return reduceMoney(*pl, money, note);
    }
    auto event = TLEvent::MoneyReduceEvent(playerUUID, money, note);
    ll::event::EventBus::getInstance().publish(event);
    if (event.isCancelled()) {
        return false;
    }
    return setMoney(playerUUID, int(getMoney(playerUUID) - money), note, set);
}

bool Money::transMoney(Player& player, Player& target, int money, const std::string& note) {
    auto event = TLEvent::MoneyTransEvent(&player, &target, money, note);
    ll::event::EventBus::getInstance().publish(event);
    if (event.isCancelled()) {
        return false;
    }
    auto fee = int(floor(money * getPayTax()));
    if (isLLMoney) {
        LLMoney_Trans(player.getXuid(), target.getXuid(), money, note); // 就让LLMoney处理去吧,就不做统一api了
        if (fee) {
            LLMoney_Trans(target.getXuid(), "", fee, "money pay fee");
        }
        return true;
    }
    setMoney(player, int(getMoney(player) - money), note, set);
    setMoney(target, int(getMoney(target) + money - fee), note, set);
    // TODO Hist DB!
    // TODO Hist
    return true;
}
bool Money::transMoney(const mce::UUID& playerUUID, const mce::UUID& targetUUID, int money, const std::string& note) {
    auto pl     = ll::service::getLevel()->getPlayer(playerUUID);
    auto target = ll::service::getLevel()->getPlayer(targetUUID);
    if (pl != nullptr && target != nullptr) {
        return transMoney(*pl, *target, money, note);
    }
    auto event = TLEvent::MoneyTransEvent(playerUUID, targetUUID, money, note);
    ll::event::EventBus::getInstance().publish(event);
    if (event.isCancelled()) {
        return false;
    }
    auto fee = int(floor(money * getPayTax()));
    if (isLLMoney) {
        LLMoney_Trans(UUID2XUID(playerUUID), UUID2XUID(targetUUID), money, note); // 就让LLMoney处理去吧,就不做统一api了
        if (fee) {
            LLMoney_Trans(UUID2XUID(targetUUID), "", fee, "money pay fee");
        }
        return true;
    }
    setMoney(playerUUID, int(getMoney(playerUUID) - money), note, set);
    setMoney(playerUUID, int(getMoney(targetUUID) + money - fee), note, set);
    // TODO Hist DB!
    // TODO Hist
    return true;
}
const ScoreboardId* Money::getOrCreatePlayerScoreId(Player& player) {
    // ll::service::getLevel()->getLevelStorage().getCompoundTag()
    if (mScoreboard->mObjectives.find(mScoreName) == mScoreboard->mObjectives.end()) {
        logger.warn("Scoreboard objective {0} not found, will create"_tr(mScoreName));
        mObjective = mScoreboard->addObjective(mScoreName, mScoreName, *mScoreboard->getCriteria("dummy"));
    }
    const ScoreboardId* id = &mScoreboard->getScoreboardId(player);
    if (!id->isValid()) {
        id = &mScoreboard->createScoreboardId(player);
    } else if (!id->isValid()) { // 非有效使用命令创建,鬼知道mj对scoreboard做了什么
        logger.debug("Player {0} ScoreboardId create failed, will use command to create", player.getName());
        auto cmd        = fmt::format("scoreboard players add \"{0}\" {1} 0", player.getName(), mScoreName);
        auto cmdContext = CommandContext(
            cmd,
            std::make_unique<ServerCommandOrigin>(
                "Server",
                ll::service::getLevel()->asServer(),
                CommandPermissionLevel::Owner,
                0
            )
        );
        ll::service::getMinecraft()->getCommands().executeCommand(cmdContext, true);
    }
    return id;
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
bool Money::setPlayerScore(const mce::UUID&, int) { return false; } // TODO 等待PlayerData写完

int Money::getPlayerScore(Player& pl) {
    auto id = getOrCreatePlayerScoreId(pl);
    if (id == nullptr) {
        return 0;
    }
    auto money = mObjective->getPlayerScore(*id).mScore;
    // TODO 玩家在线以Scoreboard为准,玩家离线以PlayerData为准，等待playerData写完然后在playerData同步money
    return money;
}
int Money::getPlayerScore(const mce::UUID& playerUUID) {
    auto pl = ll::service::getLevel()->getPlayer(playerUUID);
    if (pl != nullptr) {
        return getPlayerScore(*pl);
    }
    // TODO playerData
    return 0;
}

bool Money::checkMoney(Player& player, int money) { return getMoney(player) >= money; }
bool Money::checkMoney(const mce::UUID& player, int money) { return getMoney(player) >= money; }

double Money::getPayTax() { return 0.00; } // TODO

}; // namespace TLModule