#pragma once

#include "Utils/Data/JsonHandler.h"
#include "mc/math/Vec3.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/level/dimension/Dimension.h"

#include <memory>
#include <string>

namespace TLModule {

class Warp {
public:
    Warp();
    ~Warp();

private:
    std::unique_ptr<TLUtil::JsonHandler> mWarpData;

public:
    bool addWarp(std::string& name, Vec3& pos, Dimension& dim);

    bool removeWarp(std::string& name);

    std::vector<std::string> listWarps();

    bool warpTo(Player& player, std::string& name);
};

} // namespace TLModule