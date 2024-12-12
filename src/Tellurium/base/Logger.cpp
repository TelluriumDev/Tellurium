#include "Tellurium/base/Global.h"

namespace Tellurium {

std::unique_ptr<LoggerManage>& LoggerManage::getInstance() {
    static std::unique_ptr<LoggerManage> instance;
    if (!instance) instance = std::make_unique<LoggerManage>();
    return instance;
}

std::shared_ptr<ll::Logger> LoggerManage::getOrCreateLogger(std::string const& moduleName) {
    if (!mLoggers.contains(moduleName)) {
        mLoggers[moduleName] =
            std::make_shared<ll::Logger>(fmt::format("{0}-{1}", getSelfMod().getManifest().name, moduleName));
    }
    return mLoggers[moduleName];
}

} // namespace Tellurium