#pragma once

#include "Tellurium/base/Macro.h"

#include <ll/api/Logger.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace Tellurium {
class LoggerManage {
private:
    std::unordered_map<std::string, std::shared_ptr<ll::Logger>> mLoggers;

public:
    TUAPI static std::unique_ptr<LoggerManage>& getInstance();

    TUAPI std::shared_ptr<ll::Logger> getOrCreateLogger(std::string const& moduleName);
};
} // namespace Tellurium