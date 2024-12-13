#include "Tellurium/base/Global.h"

namespace Tellurium {

std::unique_ptr<LoggerManage>& LoggerManage::getInstance() {
    static std::unique_ptr<LoggerManage> instance;
    if (!instance) instance = std::make_unique<LoggerManage>();
    return instance;
}

std::unique_ptr<ll::Logger>& LoggerManage::getOrCreateLogger(std::string const& name) {
    if (!mLoggers.contains(name)) {
        mLoggers[name] = std::make_unique<ll::Logger>(getSelfMod().getManifest().name + "-" + name);
    }
    return mLoggers[name];
}

void LoggerManage::removeLogger(std::string const& name) { mLoggers.erase(name); }
} // namespace Tellurium