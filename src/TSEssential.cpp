#include "TSEssential.h"

#include <ll/api/event/player/PlayerJoinEvent.h>

namespace TSEssential {

bool Load() {
    LOGGER.info("Plugin Loaded!");
    return true;
}
bool UnLoad() {
    LOGGER.info("Plugin Unload!");
    return true;
}
bool Enable() {
    LOGGER.info("Plugin Enable!");
    return true;
}
bool Disable() {
    LOGGER.info("Plugin Disable");
    return true;
}
} // namespace TSEssential
