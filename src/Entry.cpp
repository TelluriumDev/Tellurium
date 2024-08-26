#include "Entry.h"
#include "Global.h"

#include <memory>

#include "ll/api/Logger.h"
#include "ll/api/mod/RegisterHelper.h"

ll::Logger logger("TSEssential");

namespace TSEssential {

static std::unique_ptr<Entry> instance;

Entry& Entry::getInstance() { return *instance; }

bool Entry::load() {
    return true;
}

bool Entry::enable() {
    return true;
}

bool Entry::disable() {
    return true;
}

bool Entry::unload() {
    return true;
}

} // namespace TSEssential

LL_REGISTER_MOD(TSEssential::Entry, TSEssential::instance);

