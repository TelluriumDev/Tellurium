#include "Utils/SQLite/SQLite.h"

namespace TLUtils::PlayerData{
void initPlayerData();

SQLite* getPlayerDataInstance();

void destroyPlayerDataInstance();
}