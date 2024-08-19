#include "Config.h"

#include <filesystem>


namespace TSEssential::Config {
static PluginConfig *instance;
PluginConfig *PluginConfig::GetInstance() {
    return instance;
}
PluginConfig::PluginConfig() {
    if ()
}
}