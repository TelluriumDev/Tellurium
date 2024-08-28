#pragma once

#include "mc/world/actor/player/Player.h"
#include "mc/world/scores/Objective.h"
#include "mc/world/scores/Scoreboard.h"

#include <string>

namespace TSModule {
class Money {
public:
    Money(std::string& scoreName);

    // 无任何实现 可以直接用在 llmoney 上
    Money();

private:
    std::string mScoreName = "";
    //  是否启用LLMoney 别问为什么要用 因为防止意外情况
    bool        isLLmoney   = true;
    Scoreboard* mScoreboard = nullptr;
    Objective*  mObjective  = nullptr;

public:
    long long getMoney(Player& player);
    bool      addMoney(Player& player, int money);
    bool      eraseMoney(Player& player, int money);
    bool      setMoney(Player& player, int money);
    bool      checkMoney(Player& player, int money);
    bool      transMoney(Player& player, Player& target, int money);
    // !: only Scoreboard can use this function
    bool modifyPlayerScore(Player& player, int money, const PlayerScoreSetFunction& function);
};
}; // namespace TSModule