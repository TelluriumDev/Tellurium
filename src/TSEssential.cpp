#include "TSEssential.h"
#include "Config.h"
#include "Exception.h"
#include "event/PluginUnloadEvent.h"

namespace TSEssential {
static bool loaded = false;
static PluginUnloadEvent unLoadEvent{};
PluginUnloadEvent& getUnloadEvent(){ return unLoadEvent; }

bool Load() {
    try{
        if (loaded) {
            unLoadEvent.
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
    // LOGGER.info("Plugin Unload!");
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
    // LOGGER.info("Plugin Disable");

    loaded = false;
    return true;
}
} // namespace TSEssential
