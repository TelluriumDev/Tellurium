
#include "Utils/PlayerData.h"
#include "Config/Config.h"
#include "Utils/JsonHandler.h"

#include <memory>
#include <string>

namespace TLUtil::PlayerData {

std::shared_ptr<JsonHandler> playerData = nullptr;

void initPlayerData() { playerData = std::make_shared<JsonHandler>(TLConfig::getDataDir() / "playerData.json"); }

JsonHandler& getInstance() { return *playerData.get(); };

void setPlayerLang(Player& player, std::string lang) {
    json j = getInstance().get<json>(player.getUuid().asString());
    if (j.empty()) {
        j = json();
    }
    j["lang"] = lang;
    getInstance().set(player.getUuid().asString(), j);
}

std::string getPlayerLang(Player& player) { return getInstance().get<json>(player.getUuid().asString())["lang"]; }

void setPlayerAnnouncement(Player& player, bool announcement) {
    json j = getInstance().get<json>(player.getUuid().asString());
    if (j.empty()) {
        j = json();
    }
    j["announcement"] = announcement;
    getInstance().set(player.getUuid().asString(), j);
}

bool getPlayerAnnouncement(Player& player) {
    return getInstance().get<json>(player.getUuid().asString())["announcement"];
}
} // namespace TLUtil::PlayerData