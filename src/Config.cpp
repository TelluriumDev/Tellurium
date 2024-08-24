#include <Global.h>

TSEssential::Config config;

namespace TSEssential
{
    void LoadConfig()
    {
        auto path = ConfigDir / "config.json";
        try {
            if (!ll::config::loadConfig(config, path)){
                ll::config::saveConfig(config, path);
            }
        } catch (...) { return; }
        return;
    }
}