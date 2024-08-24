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