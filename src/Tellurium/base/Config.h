#pragma once

#include "Tellurium/base/Macro.h"

#include <ll/api/base/StdInt.h>
#include <memory>
#include <optional>
#include <string>

namespace Tellurium {
struct Config {
public:
    enum class EconomicType {
        LLMoney,
        Scoreboard,
    };

public:
    int64 version = 1;

    struct {
        bool                       Enabled        = false;
        bool                       RegisterCmd    = true;
        EconomicType               Type           = EconomicType::LLMoney;
        std::optional<std::string> scoreboardName = "money";
    } EconomicSystem;

    struct {
        bool Enabled     = false;
        bool RegisterCmd = true;
        struct {
            uint PerPlayerMaxHome        = 3;
            uint DeleteHomeReturn        = 0;
            uint CreateHomeConsumption   = 0;
            uint TeleportHomeConsumption = 0;
        } Home;
    } HomeSystem;

public:
    TUAPI static std::unique_ptr<Config>& getInstance();
    TUAPI static void                     loadConfig();
    TUAPI static void                     saveConfig();
};
} // namespace Tellurium