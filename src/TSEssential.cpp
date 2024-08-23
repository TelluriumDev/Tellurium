#include "TSEssential.h"
#include "Config.h"
#include "Exception.h"
#include "event/PluginUnloadEvent.h"

namespace TSEssential {
static bool loaded = false;
static PluginUnloadEvent unLoadEvent{};
PluginUnloadEvent& getUnloadEvent(){ return unLoadEvent; }

bool Load() {
    LOGGER.info("Loading Plugin...");
    unLoadEvent.on([](const PluginUnloadEvent& info) -> bool { 
        LOGGER.warn("Plugin Unloaded!");
        return true; 
    });
    try {
        if (loaded == false) {
            LOGGER.warn("TSEssential has be loaded!");
            return true;
        }
        loaded = true;
        new Config::PluginConfig();
        LOGGER.info("Plugin Loaded!");
    } catch (...) {
        _CATCH_CODES("Load Plugin")
        return false;
    }
    return true;
}
bool Unload() {
    return unLoadEvent.CALL({SELF});
}
bool Enable() {
    if (loaded) {
        return true;
    }
    Load();
    return true;
}
bool Disable() {
    unLoadEvent.CALL({SELF});
    loaded = false;
    return true;
}
} // namespace TSEssential
