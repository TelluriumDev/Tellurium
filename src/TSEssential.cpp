#include "TSEssential.h"
#include "Global.h"
#include "Config.h"

namespace TSEssential
{
    bool Load()
    {
        logger.info("Loading TSEssential...");
        LoadConfig();
        return true;
    }
    bool Unload()
    {
        logger.info("Unloading TSEssential...");
        return true;
    }
    bool Enable()
    {
        logger.info("Enabling TSEssential...");
        return true;
    }
    bool Disable()
    {
        logger.info("Disabling TSEssential...");
        return true;
    }
} // namespace TSEssential
