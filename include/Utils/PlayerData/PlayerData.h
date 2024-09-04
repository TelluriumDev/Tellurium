#pragma once

#include "Utils/Data/JsonHandler.h"

namespace TLUtil::PlayerData {
void initPlayerData();

JsonHandler& getInstance();
} // namespace TLUtil::PlayerData