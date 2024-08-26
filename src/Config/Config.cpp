#include "Config/Config.h"
#include "Entry.h"
#include "Global.h"

#include "ll/api/Config.h"


TSConfig::Config config;

namespace TSConfig {

const auto& ConfigDir = TSEssential::Entry::getInstance().getSelf().getConfigDir();

const auto& ConfigFile = ConfigDir / "config.json";

void loadConfig(const std::filesystem::path& path) {
    if (!ll::config::loadConfig(config, path)) {
        logger.warn("Old config file detected, upgrading...");
        saveConfig(path);
    }
}

void saveConfig(const std::filesystem::path& path) {
    if (!ll::config::saveConfig(config, path)) {
        logger.error("Failed to save config file.");
    }
}

void initConfig() { loadConfig(ConfigFile); };

} // namespace TSConfig
