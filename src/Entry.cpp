// Private Headers
#include "Entry.h"
#include "Global.h"
#include "TSEssential.h"

// C++ STL Headers
#include <memory>

// LLAPI Headers
#include "ll/api/mod/RegisterHelper.h"
#include <ll/api/Config.h>

namespace TSEssential {

static std::unique_ptr<Entry> instance;

Entry &Entry::getInstance() { return *instance; }

bool Entry::load() {
  getSelf().getLogger().debug("Checking Network Version...");
  CheckProtocolVersion();
  getSelf().getLogger().info("Loading config.json...");
  LoadConfig();
  LoadModules();
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

bool Entry::unload() {
  getSelf().getLogger().debug("Unloading...");
  // Code for unloading the mod goes here.
  return true;
}
} // namespace TSEssential

LL_REGISTER_MOD(TSEssential::Entry, TSEssential::instance);
