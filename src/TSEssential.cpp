#include "TSEssential.h"
#include "Exception.h"
#include "includes/Config.h"
#include "includes/event/PluginUnloadEvent.h"

#include <ll/api/event/player/PlayerJoinEvent.h>

namespace TSEssential {

static bool loaded = false;

bool Load() {
    try{
        if (loaded) {
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
    LOGGER.info("Plugin Unload!");
    return true;
}
bool Enable() {
    // LOGGER.info("Plugin Enable!");
    return true;
}
bool Disable() {
    // LOGGER.info("Plugin Disable");

    loaded = false;
    return true;
}
} // namespace TSEssential
