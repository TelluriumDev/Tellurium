#include <Global.h>

TSEssential::Config config;

namespace TSEssential {
bool LoadConfig() {
    try {
        if (!ll::config::loadConfig(config, ConfigPath)) {
            ll::config::saveConfig(config, ConfigDir);
            return true;
        }
    } catch (...) {
        logger.error("Failed to load config.json");
        ll::error_utils::printCurrentException(logger);
        return false;
    }
    return true;
}
} // namespace TSEssential
bool saveConfig() {
    try {
        if (ll::config::saveConfig(config, ConfigPath)) {
            logger.info("Config saved successfully");
        }
    } catch (...) {
        logger.error("Failed to save config.json");
        ll::error_utils::printCurrentException(logger);
    }
    return true;
} // namespace TSEssential