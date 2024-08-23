#include "Config.h"
#include "TSEssential.h"

#include "utils/json.hpp"

#include <filesystem>
#include <fstream>

using namespace std;
using namespace nlohmann;

namespace TSEssential::Config {
static void AutoUpdateConfig_JSON(json& conf) {
    
}

static PluginConfig *instance;
PluginConfig *PluginConfig::GetInstance() {
    return instance;
}
PluginConfig::PluginConfig() {
    auto path = SELF.getConfigDir();
    if (!filesystem::exists(path)) { 
        filesystem::create_directories(path);
    }
    path / "config.json";
    if (!filesystem::exists(path)) {
        //TODO create default config
    }
    fstream conf(path);
    auto json = json::parse(conf);

    conf.clear();
    conf << json.dump(4);
    instance = this;
}
}