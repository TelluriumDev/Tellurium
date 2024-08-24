#include <Global.h>

namespace TSEssential {
bool LoadConfig() {
    try {
        if (!ll::config::loadConfig(config, ConfigPath)) {
            logger.warn("Updateing config.json");
            ll::config::saveConfig(config, ConfigDir);
            return true;
        }
    } catch (...) {
        logger.error("Failed to load config.json");
        ll::error_utils::printCurrentException(logger);
        logger.error("TSEssential will refuse to startup.");
        return false;
    }
    try {
        if (ll::config::saveConfig(config, ConfigDir)) {
            logger.warn("Overwrited config.json successfully");
        } else {
            logger.error("Your config.json is broken, please check it");
            logger.error("TSEssential will refuse to startup.");
            return false;
        }
    } catch (...) {
        ll::error_utils::printCurrentException(logger);
        logger.error("Can't confirm if your config.json is broken, TSEssential will refuse to startup.");
        return false;
    }
    return true;
}
} // namespace TSEssential
bool saveConfig() {
    try {
        if (ll::config::saveConfig(config, ConfigPath)) {
            logger.error("Failed to save config.json");
            return false;
        }
    } catch (...) {
        ll::error_utils::printCurrentException(logger);
    }
    return true;
} // namespace TSEssential