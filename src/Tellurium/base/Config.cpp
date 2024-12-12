#include "Tellurium/base/Global.h"

#include <ll/api/Config.h>

namespace Tellurium {

std::unique_ptr<Config>& Config::getInstance() {
    static std::unique_ptr<Config> instance;
    if (!instance) instance = std::make_unique<Config>();
    return instance;
}

void Config::loadConfig() {
    try {
        ll::config::loadConfig(*getInstance(), getSelfMod().getConfigDir() / "config.json");
    } catch (...) {
        ll::error_utils::printCurrentException(*LoggerManage::getInstance()->getOrCreateLogger("Config"));
    }
}

void Config::saveConfig() {
    try {
        ll::config::saveConfig(*getInstance(), getSelfMod().getConfigDir() / "config.json");
    } catch (...) {
        ll::error_utils::printCurrentException(*LoggerManage::getInstance()->getOrCreateLogger("Config"));
    }
}

} // namespace Tellurium