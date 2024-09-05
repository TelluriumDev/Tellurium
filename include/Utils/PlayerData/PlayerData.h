#pragma once

#include "Utils/Data/JsonHandler.h"

#include "mc/world/actor/player/Player.h"

namespace TLUtil::PlayerData {
void initPlayerData();

JsonHandler& getInstance();

std::string getPlayerLang(Player& player);
} // namespace TLUtil::PlayerData