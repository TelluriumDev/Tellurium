#pragma once

#include "Utils/Data/JsonHandler.h"

namespace TLUtils::PlayerData {
void initPlayerData();

JsonHandler& getInstance();
} // namespace TLUtils::PlayerData