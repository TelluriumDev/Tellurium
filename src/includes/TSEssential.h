#pragma once

// Global.h

#include "./Entry.h" // IWYU pragma: export

#define LOGGER TSEssential::Entry::Entry::getInstance().getSelf().getLogger()
#define SELF TSEssential::Entry::Entry::getInstance().getSelf()

namespace TSEssential {
bool Load();
bool UnLoad();
} // namespace TSEssential