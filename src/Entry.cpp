#include "Entry.h"
#include "Global.h"
#include "TMEssential.h"


#include <memory>

#include <ll/api/Config.h>
#include "ll/api/mod/RegisterHelper.h"


namespace TMEssential
{

    static std::unique_ptr<Entry> instance;

    Entry &Entry::getInstance() { return *instance; }

    bool Entry::load()
    {
        getSelf().getLogger().debug("Checking Network Version...");
        CheckProtocolVersion();
        getSelf().getLogger().info("Loading config.json...");
        LoadConfig();
        LoadModules();
        return true;
    }
    bool Entry::enable()
    {
        getSelf().getLogger().debug("Enabling...");
        // Code for enabling the mod goes here.
        return true;
    }

    bool Entry::disable()
    {
        getSelf().getLogger().debug("Disabling...");
        // Code for disabling the mod goes here.
        return true;
    }

    bool Entry::unload()
    {
        getSelf().getLogger().debug("Unloading...");
        // Code for unloading the mod goes here.
        return true;
    }
} // namespace Muelsyse

LL_REGISTER_MOD(TMEssential::Entry, TMEssential::instance);
