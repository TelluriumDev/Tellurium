#include "Config.h"


namespace TSEssential::Config {
static PluginConfig *instance;
PluginConfig *PluginConfig::GetInstance() {
    return instance;
}
PluginConfig::PluginConfig() {
  
}
}