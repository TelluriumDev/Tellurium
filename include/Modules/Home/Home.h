#pragma once

#include "Utils/Data/JsonHandler.h"

#include "mc/world/actor/player/Player.h"

#include <map>
#include <memory>
#include <string>
#include <vector>


struct HomeData {
    std::string      name;
    std::vector<int> position;
};


namespace TLModule {
class Home {
public:
    Home();

private:
    std::unique_ptr<TLUtil::JsonHandler> mHomeData;

public:
    bool                                         addHome(Player& player, std::string name);
    bool                                         delHome(Player& player, std::string name);
    bool                                         teleportHome(Player& player, std::string name);
    std::vector<HomeData>                        listPlayerHome(Player& player);
    std::map<std::string, std::vector<HomeData>> listAllHome();
};
} // namespace TLModule