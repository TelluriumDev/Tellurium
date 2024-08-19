#include "config/Config.hpp"


namespace TSEssential::Config {
static TSEssential::Config::PluginConfig *instance = nullptr;

TSEssential::Config::PluginConfig::GetInstance() { return *instance; }
}