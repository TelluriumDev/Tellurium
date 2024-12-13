#pragma once

#include "Tellurium/base/Macro.h"

#include <ll/api/Logger.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace Tellurium {
class LoggerManage {
private:
    std::unordered_map<std::string, std::unique_ptr<ll::Logger>> mLoggers;

public:
    TUAPI static std::unique_ptr<LoggerManage>& getInstance();

    TUAPI std::unique_ptr<ll::Logger>& getOrCreateLogger(std::string const& name);

    TUAPI void removeLogger(std::string const& name);
};
} // namespace Tellurium