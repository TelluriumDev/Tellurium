#include "Modules/Home/Home.h"
#include "Config/Config.h"
#include "Event/HomeEvent/HomeAddEvent.h"
#include "Event/HomeEvent/HomeDelEvent.h"
#include "Event/HomeEvent/HomeGoEvent.h"
#include "Global.h"
#include "Utils/Data/JsonHandler.h"


#include "ll/api/event/EventBus.h"

using namespace ll::event;

#include <memory>
#include <vector>

namespace TLModule {
Home::Home() { mHomeData = std::make_unique<TLUtil::JsonHandler>(TLConfig::getDataDir() / "home.json"); }

bool Home::addHome(Player& player, std::string name) {
    try {
        auto& pos   = player.getPosition();
        auto  homes = mHomeData.get()->get<json>(player.getUuid().asString());
        if (!homes.is_array()) homes = json::array();
        // if (!homes.is_array()) return false;
        for (auto& home : homes) {
            if (home["name"] == name) {
                return false;
            }
        }
        auto event = TLEvent::HomeAddEvent(&player, name, pos, player.getDimension());
        EventBus::getInstance().publish(event);
        if (event.isCancelled()) return false;
        json j;
        j["name"] = name;
        j["pos"]  = {(int)pos.x, (int)pos.y, (int)pos.z, player.getDimensionId().id};
        homes.push_back(j);
        mHomeData.get()->set(player.getUuid().asString(), homes);
        return true;
    } catch (std::exception& e) {
        logger.error("Error adding home: {0}"_tr(e.what()));
        return false;
    }
}

bool Home::delHome(Player& player, std::string name) {
    try {
        auto homes = mHomeData.get()->get<json>(player.getUuid().asString());
        if (!homes.is_array()) return false;
        int index = 0;
        for (auto& home : homes) {
            if (home["name"] == name) {
                auto event = TLEvent::HomeDelEvent(&player, name);
                EventBus::getInstance().publish(event);
                if (event.isCancelled()) return false;
                homes.erase(index);
                mHomeData->set(player.getUuid().asString(), homes);
                return true;
            }
            index++;
        }
        return false;
    } catch (std::exception& e) {
        logger.error("Error deleting home: {0}"_tr(e.what()));
        return false;
    }
};

bool Home::teleportHome(Player& player, std::string name) {
    try {
        auto homes = mHomeData.get()->get<json>(player.getUuid().asString());
        if (!homes.is_array()) return false;
        for (auto& home : homes) {
            if (home["name"] == name) {
                auto pos   = home["pos"].get<std::vector<int>>();
                auto event = TLEvent::HomeGoEvent(&player, name, Vec3(pos[0], pos[1], pos[2]), player.getDimension());
                EventBus::getInstance().publish(event);
                if (event.isCancelled()) return false;
                player.teleport(Vec3(pos[0], pos[1], pos[2]), DimensionType(pos[3]));
                return true;
            }
        }
        return false;
    } catch (std::exception& e) {
        logger.error("Error teleporting home: {0}"_tr(e.what()));
        return false;
    }
};

std::vector<HomeData> Home::listPlayerHome(Player& player) {
    try {
        auto homes = mHomeData.get()->get<json>(player.getUuid().asString());
        if (!homes.is_array()) return {};
        std::vector<HomeData> homeData;
        for (auto& home : homes) {
            homeData.push_back({home["name"].get<std::string>(), home["pos"].get<std::vector<int>>()});
        }
        return homeData;
    } catch (std::exception& e) {
        logger.error("Error listing home: {0}"_tr(e.what()));
        return {};
    }
};

std::map<std::string, std::vector<HomeData>> Home::listAllHome() {
    try {
        std::map<std::string, std::vector<HomeData>> homeData;
        for (auto home = mHomeData->begin(); home != mHomeData->end(); ++home) {
            std::vector<HomeData> homeVec;
            auto                  playerHomes = home.value();
            for (auto& playerHome : playerHomes) {
                homeVec.push_back({playerHome["name"].get<std::string>(), playerHome["pos"].get<std::vector<int>>()});
            }
            homeData[home.key()] = homeVec;
        }
        return homeData;
    } catch (std::exception& e) {
        logger.error("Error listing all home: {0}"_tr(e.what()));
        return {};
    }
}

} // namespace TLModule