#include "Tellurium/Entry.h"

#include <ll/api/mod/RegisterHelper.h>
#include <memory>

namespace Tellurium {

static std::unique_ptr<Entry> instance;

Entry& Entry::getInstance() { return *instance; }

bool Entry::load() { return true; }

bool Entry::enable() { return true; }

bool Entry::disable() { return true; }

bool Entry::unload() { return true; }

} // namespace Tellurium

LL_REGISTER_MOD(Tellurium::Entry, Tellurium::instance);