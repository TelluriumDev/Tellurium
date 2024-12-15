#include "Tellurium/base/Global.h"
#include "Tellurium/modules/HomeSystem/HomeSystem.h"

#include <GMLIB/Server/PlayerAPI.h>

#define CATCH(result)                                                                                                  \
    catch (...) {                                                                                                      \
        ll::error_utils::printCurrentException(*LoggerManage::getInstance()->getOrCreateLogger("Home"));                \
        return result;                                                                                                 \
    }

namespace Tellurium {

std::optional<HomeSystem>& HomeSystem::getInstance() {
    static std::optional<HomeSystem> instance;
    if (!instance.has_value() && Config::getInstance()->HomeSystem.Enabled) {
        instance.emplace();
        instance->getHomeStorage();
    }
    return instance;
}

std::unique_ptr<ll::data::KeyValueDB>& HomeSystem::getHomeStorage() {
    if (!homeStorage) homeStorage = std::make_unique<ll::data::KeyValueDB>(getSelfMod().getDataDir() / "home");
    return homeStorage;
}

mce::UUID HomeSystem::getNewHomeId() {
    do {
        auto uuid = mce::UUID::random();
        if (!getHomeStorage()->has(uuid.asString())) return uuid;
    } while (true);
}

std::optional<HomeSystem::HomeDate> HomeSystem::getHome(mce::UUID homeId) try {
    if (!getHomeStorage()->has(homeId.asString())) return std::nullopt;
    HomeSystem::HomeDate data;
    ll::reflection::deserialize(data, nlohmann::json::parse(*getHomeStorage()->get(homeId.asString()))).value();
    return data;
}
CATCH(std::nullopt)

std::vector<HomeSystem::HomeDate> HomeSystem::getHomes(mce::UUID player) try {
    std::vector<HomeSystem::HomeDate> result;
    getHomeStorage()->iter([&result, &player](std::string_view, std::string_view value) -> bool {
        HomeSystem::HomeDate data;
        ll::reflection::deserialize(data, nlohmann::json::parse(value)).value();
        if (data.owner == player) result.emplace_back(data);
        return true;
    });
    return result;
}
CATCH({})

std::optional<HomeSystem::HomeDate>
HomeSystem::addHome(mce::UUID player, std::string name, std::pair<Vec3, int> position) try {
    auto data        = HomeDate{this->getNewHomeId(), player, name, position};
    auto beforeEvent = Event::AddHomeBeforeEvent(data);
    ll::event::EventBus::getInstance().publish(beforeEvent);
    if (beforeEvent.isCancelled()) return std::nullopt;
    if (homeStorage->set(data.id.asString(), ll::reflection::serialize<nlohmann::ordered_json>(data)->dump())) {
        ll::event::EventBus::getInstance().publish(Event::AddHomeAfterEvent(data));
        return data;
    }
    return std::nullopt;
}
CATCH(std::nullopt)

bool HomeSystem::deleteHome(mce::UUID homeId) try {
    if (!getHomeStorage()->has(homeId.asString())) return false;
    auto beforeEvent = Event::DeleteHomeBeforeEvent(homeId);
    ll::event::EventBus::getInstance().publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    if (getHomeStorage()->del(homeId.asString())) {
        ll::event::EventBus::getInstance().publish(Event::DeleteHomeAfterEvent(homeId));
        return true;
    }
    return false;
}
CATCH(false)

bool HomeSystem::teleportHome(mce::UUID player, mce::UUID homeId) try {
    auto data = this->getHome(homeId);
    if (!data.has_value()) return false;
    auto beforeEvent = Event::TeleportHomeBeforeEvent(player, *data);
    ll::event::EventBus::getInstance().publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    if (GMLIB_Player::setPlayerPosition(player, data->position.first, data->position.second)) {
        ll::event::EventBus::getInstance().publish(Event::TeleportHomeAfterEvent(player, *data));
        return true;
    }
    return false;
}
CATCH(false)
} // namespace Tellurium
