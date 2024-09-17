#pragma once

#include <ll/api/base/StdInt.h>

#include "mc/deps/core/mce/UUID.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/scores/Objective.h"
#include "mc/world/scores/Scoreboard.h"
#include "mc/world/scores/ScoreboardId.h"

#include <string>
#include <vector>

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


enum LLMoneyEvent { Set, Add, Reduce, Trans };
typedef void (*LLMoneyAfterEventCallback)(LLMoneyEvent type, std::string from, std::string to, llong value);
typedef bool (*LLMoneyBeforeEventCallback)(LLMoneyEvent type, std::string from, std::string to, llong value);

namespace LegacyMoney {

bool isValid();

std::vector<std::pair<std::string, long long>> ranking(ushort num);

bool add(std::string xuid, long long money);

void clearHist(int difftime);

long long get(std::string xuid);

std::string getHist(std::string xuid, int timediff);

bool reduce(std::string xuid, long long money);

bool set(std::string xuid, long long money);

bool trans(std::string from, std::string to, long long val, std::string const& note);

void listenAfterEvent(LLMoneyAfterEventCallback callback);

void listenBeforeEvent(LLMoneyBeforeEventCallback callback);

// 以下为实例提供的函数

// 从UUID获取XUID
std::string getXuidFromUuid(mce::UUID const& uuid, std::string const& defaultValue = "");

bool add(mce::UUID uuid, long long money);

bool reduce(mce::UUID uuid, long long money);

bool set(mce::UUID uuid, long long money);

bool trans(mce::UUID from, mce::UUID to, long long val, std::string const& note);

long long get(mce::UUID from);

} // namespace LegacyMoney