#include "Tellurium/base/Global.h"
#include "Tellurium/modules/EconomicSystem/EconomicSystem.h"

#define _AMD64_
#include <GMLIB/Server/ScoreboardAPI.h>
#include <libloaderapi.h>

namespace Tellurium {

bool EconomicSystem::isValid() {
    auto& setting = Config::getInstance()->EconomicSystem;

    switch (setting.Type) {
    case Config::EconomicType::LLMoney: {
        if (!GetModuleHandleW(L"LegacyMoney.dll")) return false;
    }
    case Config::EconomicType::Scoreboard: {
        if (!setting.scoreboardName.has_value()) setting.scoreboardName.emplace();
        if (!GMLIB_Scoreboard::getInstance()->getObjective(setting.scoreboardName.value())) return false;
    }
    default: {
        return false;
    }
    }
}

std::optional<EconomicSystem>& EconomicSystem::getInstance() {
    static std::optional<EconomicSystem> instance;
    if (!instance.has_value() && Config::getInstance()->EconomicSystem.Enabled && isValid()) {
        instance.emplace();
    }
    return instance;
}

int EconomicSystem::getMoney(mce::UUID target) const {
    if (!isValid()) return 0;
    switch (Config::getInstance()->EconomicSystem.Type) {
    case Config::EconomicType::LLMoney: {
        auto playerInfo = PlayerInfo::fromUuid(target);
        if (!playerInfo.has_value()) return 0;
        auto result = ((llong(*)(std ::string xuid)
        )GetProcAddress(GetModuleHandleW(L"LegacyMoney.dll"), "LLMoney_Get"))(playerInfo->xuid);
        return result > INT_MAX ? INT_MAX : (int)result;
    }
    case Config::EconomicType::Scoreboard: {
        return GMLIB_Scoreboard::getInstance()
            .transform([&target](GMLIB_Scoreboard& scoreboard) -> int {
                return scoreboard.getPlayerScore(*Config::getInstance()->EconomicSystem.scoreboardName, target)
                    .value_or(0);
            })
            .value_or(0);
        break;
    }
    default:
        return 0;
    }
}

#define ECONOMIC_FUNC_MACRO(NAME, LLMONEY_SYMBOL, OBJECT_TYPE, EVENT_PREFIX)                                           \
    bool EconomicSystem::NAME(mce::UUID target, int value) {                                                           \
        if (!isValid()) return false;                                                                                  \
        auto beforeEvent = Event::EVENT_PREFIX##EconomicBeforeEvent(target, value);                                    \
        ll::event::EventBus::getInstance().publish(beforeEvent);                                                       \
        if (beforeEvent.isCancelled()) return false;                                                                   \
        bool result = false;                                                                                           \
        switch (Config::getInstance()->EconomicSystem.Type) {                                                          \
        case Config::EconomicType::LLMoney: {                                                                          \
            auto playerInfo = PlayerInfo::fromUuid(target);                                                            \
            if (!playerInfo.has_value()) return false;                                                                 \
            result = ((bool (*)(std ::string xuid, llong value)                                                        \
            )GetProcAddress(GetModuleHandleW(L"LegacyMoney.dll"), LLMONEY_SYMBOL))(playerInfo->xuid, value);           \
            break;                                                                                                     \
        }                                                                                                              \
        case Config::EconomicType::Scoreboard: {                                                                       \
            result = GMLIB_Scoreboard::getInstance()                                                                   \
                         .transform([&target, &value](GMLIB_Scoreboard& scoreboard) -> bool {                          \
                             return scoreboard                                                                         \
                                 .setPlayerScore(                                                                      \
                                     *Config::getInstance()->EconomicSystem.scoreboardName,                            \
                                     target,                                                                           \
                                     value,                                                                            \
                                     PlayerScoreSetFunction::OBJECT_TYPE                                               \
                                 )                                                                                     \
                                 .has_value();                                                                         \
                         })                                                                                            \
                         .value_or(false);                                                                             \
            break;                                                                                                     \
        }                                                                                                              \
        default:                                                                                                       \
            return false;                                                                                              \
        }                                                                                                              \
        if (result) {                                                                                                  \
            ll::event::EventBus::getInstance().publish(Event::EVENT_PREFIX##EconomicAfterEvent(target, value));        \
        }                                                                                                              \
        return result;                                                                                                 \
    }

ECONOMIC_FUNC_MACRO(addMoney, "LLMoney_Add", Add, Add);

ECONOMIC_FUNC_MACRO(reduceMoney, "LLMoney_Reduce", Subtract, Reduce);

ECONOMIC_FUNC_MACRO(setMoney, "LLMoney_Set", Set, Set);

} // namespace Tellurium