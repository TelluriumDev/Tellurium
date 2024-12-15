#include "Tellurium/base/Global.h"
#include "Tellurium/modules/HomeSystem/HomeSystem.h"

#include <algorithm>
#include <memory>
#include <vector>


#define _AMD64_

namespace Tellurium {

HomeSystem::HomeSystem() {
    homeDb = std::make_unique<ll::data::KeyValueDB>(Config::getInstance()->DataPath + "home.json");
}

std::optional<HomeSystem>& HomeSystem::getInstance() {
    static std::optional<HomeSystem> instance;
    if (!instance.has_value() && Config::getInstance()->HomeSystem.Enabled) {
        instance.emplace();
    }
    return instance;
}

bool HomeSystem::addHome(Player& player, std::string name) {
    try {
        HomeDate home(name, player.getPosition(), player.getDimensionId().id);
        auto     beforeEvent = Event::AddHomeBeforeEvent(player, home);
        ll::event::EventBus::getInstance().publish(beforeEvent);
        if (beforeEvent.isCancelled()) return false;
        mce::UUID             uuid = player.getUuid();
        std::vector<HomeDate> homeDataList;
        if (!homeDb->has(uuid.asString())) {
            homeDataList.push_back(home);
            homeDb->set(uuid.asString(), ll::reflection::serialize<nlohmann::ordered_json>(homeDataList)->dump());
            return true;
        }
        nlohmann::json json = nlohmann::json::parse(homeDb->get(uuid.asString()).value());
        homeDataList        = ll::reflection::deserialize_to<std::vector<HomeDate>>(json).value();
        homeDataList.push_back(home);
        homeDb->set(uuid.asString(), ll::reflection::serialize<nlohmann::ordered_json>(homeDataList)->dump());
        auto afterEvent = Event::AddHomeAfterEvent(player, home);
        ll::event::EventBus::getInstance().publish(afterEvent);
        return true;
    } catch (...) {
        return false;
    }
}

bool HomeSystem::deleteHome(Player& player, std::string name) {
    try {
        mce::UUID             uuid = player.getUuid();
        std::vector<HomeDate> homeDataList;
        if (!homeDb->has(uuid.asString())) return false;
        homeDataList = ll::reflection::deserialize_to<std::vector<HomeDate>>(
                           nlohmann::json::parse(homeDb->get(uuid.asString()).value())
        )
                           .value();
        std::for_each(homeDataList.begin(), homeDataList.end(), [&player, &homeDataList, name](HomeDate& homeData) {
            if (homeData.name == name) {
                auto beforeEvent = Event::DeleteHomeBeforeEvent(player, homeData);
                ll::event::EventBus::getInstance().publish(beforeEvent);
                if (beforeEvent.isCancelled()) return;
                homeDataList.erase(homeDataList.begin());
                auto afterEvent = Event::DeleteHomeAfterEvent(player, homeData);
                ll::event::EventBus::getInstance().publish(beforeEvent);
                return;
            }
        });
        homeDb->set(uuid.asString(), ll::reflection::serialize<nlohmann::ordered_json>(homeDataList)->dump());
        return true;
    } catch (...) {
        return false;
    }
    return false;
}

bool HomeSystem::teleportHome(Player& player, std::string name) {
    try {
        mce::UUID             uuid = player.getUuid();
        std::vector<HomeDate> homeDataList;
        if (!homeDb->has(uuid.asString())) return false;
        homeDataList = ll::reflection::deserialize_to<std::vector<HomeDate>>(
                           nlohmann::json::parse(homeDb->get(uuid.asString()).value())
        )
                           .value();
        std::for_each(homeDataList.begin(), homeDataList.end(), [&player, name](HomeDate& homeData) {
            if (homeData.name == name) {
                auto beforeEvent = Event::TeleportHomeBeforeEvent(player, homeData);
                ll::event::EventBus::getInstance().publish(beforeEvent);
                if (beforeEvent.isCancelled()) return;
                player.teleport(homeData.position, homeData.dimensionId);
                auto afterEvent = Event::TeleportHomeAfterEvent(player, homeData);
                ll::event::EventBus::getInstance().publish(beforeEvent);
                return;
            }
        });
        return true;
    } catch (...) {
        return false;
    }
    return false;
}

std::vector<HomeSystem::HomeDate> HomeSystem::getHome(mce::UUID target) {
    try {
        if (!homeDb->has(target.asString())) return {};
        return ll::reflection::deserialize_to<std::vector<HomeDate>>(
                   nlohmann::json::parse(homeDb->get(target.asString()).value())
        )
            .value();
    } catch (...) {
        return {};
    }
};
} // namespace Tellurium
