#pragma once

#include "mc/world/actor/player/Player.h"
#include "mc/world/scores/Objective.h"
#include "mc/world/scores/Scoreboard.h"

#include <string>

namespace TLModule {
class Money {
public:
    Money(const std::string& scoreName);

private:
    std::string mScoreName  = "";
    bool        isLLMoney   = true;
    Scoreboard* mScoreboard = nullptr;
    Objective*  mObjective  = nullptr;

public:
    long long getMoney(Player& player);
    bool      setMoney(Player& player, long long money, const std::string& note);
    bool      addMoney(Player& player, long long money, const std::string& note);
    bool      reduceMoney(Player& player, long long money, const std::string& note);
    bool      transMoney(Player& player, Player& target, long long money, const std::string& note);
    bool      checkMoney(Player& player, long long money);

private:
    // !: only Scoreboard can use this function
    // const ScoreboardId* getOrCreatePlayerScoreId(Player& player);
    bool modifyPlayerScore(Player& player, long long money, const PlayerScoreSetFunction& function);
};
} // namespace TLModule