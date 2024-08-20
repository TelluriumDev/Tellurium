#include "Config.h"
#include "TSEssential.h"

#include <filesystem>


namespace TSEssential::Config {
static PluginConfig *instance;
PluginConfig *PluginConfig::GetInstance() {
    return instance;
}
PluginConfig::PluginConfig() {
    auto json = SELF.getConfigDir() / "config.json";
    
}
}