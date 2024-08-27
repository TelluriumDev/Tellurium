#include "Config/Config.h"
#include "Global.h"

#include <ll/api/Config.h>

TSConfig::Config config;

namespace TSConfig {


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

void initConfig(ll::mod::NativeMod& self) {
    const auto& ConfigDir  = self.getConfigDir();
    const auto& ConfigFile = ConfigDir / "config.json";
    loadConfig(ConfigFile);
};

} // namespace TSConfig
