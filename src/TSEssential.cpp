#include "TSEssential.h"

namespace TSEssential {

bool Load() {
    LOGGER.info("Plugin Loaded!");
    return true;
}
bool UnLoad() {
    LOGGER.info("Plugin Unload!");
    return true;
}
} // namespace TSEssential
