<<<<<<< HEAD
=======
// Private Headers
#include "Entry.h"
#include "Global.h"
>>>>>>> de92f11e1cc3f2ee7c1abc7bb0e065c8204913a1
#include "TSEssential.h"
#include "ll/api/memory/Memory.h"
#define LL_MEMORY_OPERATORS

#include <ll/api/memory/MemoryOperators.h> // IWYU pragma: keep

#include "./Entry.h"
#include "./TSEssential.h"

// C++ STL Headers
#include <memory>

<<<<<<< HEAD
=======
// LLAPI Headers
#include "ll/api/mod/RegisterHelper.h"
>>>>>>> de92f11e1cc3f2ee7c1abc7bb0e065c8204913a1
#include <ll/api/Config.h>
#include <ll/api/memory/Memory.h>
#include <ll/api/mod/RegisterHelper.h>

#define TARGET_NETWORK_VERSION 686 // BDS 1.21.3.01

namespace TSEssential::Entry {

void CheckProtocolVersion() {
  auto NetworkVersion = *(int *)ll::memory::resolveSymbol(
      "?NetworkProtocolVersion@SharedConstants@@3HB");
  if (NetworkVersion != TARGET_NETWORK_VERSION) {
    LOGGER.warn("Unsupported Network Version: " +
                std::to_string(NetworkVersion));
    LOGGER.warn("The mod probably won't work correctly");
    LOGGER.warn("Target Network Version: " +
                std::to_string(TARGET_NETWORK_VERSION));
  }
}

static std::unique_ptr<Entry> instance;

Entry &Entry::getInstance() { return *instance; }

bool Entry::load() {
  CheckProtocolVersion();
  return TSEssential::Load();
}
bool Entry::enable() { return true; }

bool Entry::disable() { return false; }

bool Entry::unload() { return TSEssential::UnLoad(); }
} // namespace TSEssential::Entry

LL_REGISTER_MOD(TSEssential::Entry::Entry, TSEssential::Entry::instance);
