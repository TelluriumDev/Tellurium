#include "mod/TSEssential.h"

#include <memory>

#include "ll/api/mod/RegisterHelper.h"

namespace TSEssential {

static std::unique_ptr<Entry> instance;

Entry& Entry::getInstance() { return *instance; }

bool Entry::load() {
    getSelf().getLogger().debug("Loading...");
    // Code for loading the mod goes here.
    return true;
}

bool Entry::enable() {
    getSelf().getLogger().debug("Enabling...");
    // Code for enabling the mod goes here.
    return true;
}

bool Entry::disable() {
    getSelf().getLogger().debug("Disabling...");
    // Code for disabling the mod goes here.
    return true;
}

} // namespace TSEssential

LL_REGISTER_MOD(TSEssential::Entry, TSEssential::instance);
