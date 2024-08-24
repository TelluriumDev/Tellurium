#include "TSEssential.h"
#include "Config.h"
#include "Global.h"
#include "utils/I18n.h"


namespace TSEssential {
bool Load() {
    logger.info("Loading TSEssential...");
    if (!LoadConfig()) {
        return false;
    }
    return true;
}
bool Unload() {
    logger.info("Unloading TSEssential...");
    return true;
}
bool Enable() {
    logger.info("Enabling TSEssential...");
    return true;
}
bool Disable() {
    logger.info("Disabling TSEssential...");
    delete &logger;
    return true;
}
} // namespace TSEssential
