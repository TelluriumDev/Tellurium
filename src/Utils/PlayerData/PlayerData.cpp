
#include "Utils/PlayerData/PlayerData.h"
#include "Config/Config.h"
#include "Utils/Data/JsonHandler.h"

#include <memory>
#include <string>

namespace TLUtil::PlayerData {

std::shared_ptr<JsonHandler> playerData = nullptr;

void initPlayerData() { playerData = std::make_shared<JsonHandler>(TLConfig::getDataDir() / "playerData.json"); }

JsonHandler& getInstance() { return *playerData.get(); };

std::string getPlayerLang(Player& player) { return getInstance().get<json>(player.getUuid().asString())["lang"]; }
} // namespace TLUtil::PlayerData