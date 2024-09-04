#pragma once

#include "mc/world/actor/player/Player.h"
#include "mc/world/scores/Objective.h"
#include "mc/world/scores/Scoreboard.h"
#include "mc/world/scores/ScoreboardId.h"

#include <string>

namespace TLModule {
class Money {
public:
    Money(std::string& scoreName);

    // 无任何实现 可以直接用在 llmoney 上
    Money();

private:
    std::string mScoreName = "";
    //  是否启用LLMoney 别问为什么要用 因为防止意外情况
    bool        isLLMoney   = true;
    Scoreboard* mScoreboard = nullptr;
    Objective*  mObjective  = nullptr;

public:
    long long getMoney(Player& player);

    bool setMoney(Player& player, long long money, const std::string& note);

    bool addMoney(Player& player, long long money, const std::string& note);

    bool reduceMoney(Player& player, long long money, const std::string& note);

    bool transMoney(Player& player, Player& target, long long money, const std::string& note);

    bool checkMoney(Player& player, long long money);

private:
    // !: only Scoreboard can use this function
    const ScoreboardId* getOrCreatePlayerScoreId(Player& player);

    bool modifyPlayerScore(Player& player, long long money, const PlayerScoreSetFunction& function);
};
} // namespace TLModule