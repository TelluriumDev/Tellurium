#pragma once

#include "Tellurium/base/Macro.h"

#include <ll/api/base/StdInt.h>
#include <memory>

namespace Tellurium {
struct Config {
public:
    int64 version = 1;

public:
    TUAPI static std::unique_ptr<Config>& getInstance();
    TUAPI static void                     loadConfig();
    TUAPI static void                     saveConfig();
};
} // namespace Tellurium