#pragma once

#include "./Entry.h"

#define LOGGER TSEssential::Entry::Entry::getInstance().getSelf().getLogger()

namespace TSEssential {
bool Load();
bool UnLoad();
} // namespace TSEssential