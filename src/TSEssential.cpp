#include "TSEssential.h"
#include "Config.h"
#include "Exception.h"
#include "event/PluginUnloadEvent.h"

#include <ll/api/event/EventBus.h>

namespace TSEssential {
static bool loaded = false;
static PluginUnloadEvent unLoadEvent{};
PluginUnloadEvent& getUnloadEvent(){ return unLoadEvent; }

bool Load() {
    try {
        if (loaded == false) {
            LOGGER.warn("TSEssential has be loaded!");
            return true;
        }
        loaded = true;
        auto conf = new Config::PluginConfig();
        
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
    EventBus
    unLoadEvent.CALL({SELF});
    loaded = false;
    return true;
}
} // namespace TSEssential
