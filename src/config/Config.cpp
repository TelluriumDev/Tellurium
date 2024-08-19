#include "config/Config.hpp"
#include "config/Config.h"


namespace TSEssential::Config {
static TSEssential::Config::PluginConfig *instance = nullptr;

TSEssential::Config::PluginConfig::GetInstance() { return *instance; }
}