#pragma once

#include "mc/deps/core/mce/UUID.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/scores/Objective.h"
#include "mc/world/scores/Scoreboard.h"
#include "mc/world/scores/ScoreboardId.h"

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
    long long getMoney(const mce::UUID& uuid);
    bool      setMoney(const mce::UUID& uuid, long long money, const std::string& note);
    bool      addMoney(const mce::UUID& uuid, long long money, const std::string& note);
    bool      reduceMoney(const mce::UUID& uuid, long long money, const std::string& note);
    bool      transMoney(const mce::UUID& uuid, const mce::UUID& target, long long money, const std::string& note);
    bool      checkMoney(const mce::UUID& uuid, long long money);

private:
    // !: only Scoreboard can use this function
    // const ScoreboardId* getOrCreatePlayerScoreId(Player& player);
    std::optional<int>
    modifyPlayerScore(const mce::UUID& uuid, long long money, const PlayerScoreSetFunction& function);
    const ScoreboardId& getOrCreatePlayerScoreId(const mce::UUID& uuid);
};
} // namespace TLModule