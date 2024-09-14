#pragma once

#include "Utils/JsonHandler.h"

#include "mc/world/actor/player/Player.h"

namespace TLUtil::PlayerData {
void initPlayerData();

JsonHandler& getInstance();

void setPlayerLang(Player& player, std::string lang);

std::string getPlayerLang(Player& player);

void setPlayerAnnouncement(Player& player, bool announcement);

bool getPlayerAnnouncement(Player& player);
} // namespace TLUtil::PlayerData