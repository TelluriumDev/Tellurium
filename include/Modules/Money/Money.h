#pragma once

#include "mc/world/actor/player/Player.h"
#include "mc/world/scores/Objective.h"
#include "mc/world/scores/Scoreboard.h"
#include "mc/world/scores/ScoreboardId.h"

#include <string>

enum MoneySetOptions : int {
    sync, // llmoney同步，playerdata同步(不可拦截)
    set,  // add reduce都是这个类型
    init, // 玩家初始化经济
    pay   // 玩家交易
};
namespace TLModule {
class Money {
public:
    Money(std::string& scoreName);

    // 无任何实现 可以直接用在 llmoney 上
    Money();

private:
    std::string mScoreName{""};
    //  是否启用LLMoney 别问为什么要用 因为防止意外情况
    bool        isLLmoney{true};
    Scoreboard* mScoreboard{nullptr};
    Objective*  mObjective{nullptr};

public:
    long long getMoney(mce::UUID& uuid);
    long long getMoney(Player& uuid);

    bool setMoney(mce::UUID& playerUUID, int money, std::string& note, ::MoneySetOptions option = set);
    bool setMoney(Player& player, int money, std::string& note, ::MoneySetOptions option = set);

    // bool addMoney(mce::UUID& playerUUID, int money, std::string& note);
    // bool addMoney(Player& playerUUID, int money, std::string& note);

    // bool reduceMoney(mce::UUID& playerUUID, int money, std::string& note);
    // bool reduceMoney(Player& player, int money, std::string& note);

    // bool transMoney(mce::UUID& playerUUID, mce::UUID& targetPlayerUUID, int money, std::string& note);
    // bool transMoney(Player& player, Player& target, int money, std::string& note);

    // bool checkMoney(mce::UUID& playerUUID, int money);
    // bool checkMoney(Player& player, int money);

private:
    // !: only Scoreboard can use this function
    ScoreboardId* getOrCreatePlayerScoreId(Player& player);
    // !: only Scoreboard can use this function(MCFunction)
    bool setPlayerScore(Player& player, int money);

    bool getOfflinePlayerNbt(mce::UUID& uuid);
};
}; // namespace TLModule