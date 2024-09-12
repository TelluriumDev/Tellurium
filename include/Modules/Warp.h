#pragma once

#include "Utils/JsonHandler.h"


#include "mc/math/Vec3.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/level/dimension/Dimension.h"

#include <memory>
#include <string>

namespace TLModule {

class Warp {
public:
    Warp();

private:
    std::unique_ptr<TLUtil::JsonHandler> mWarpData;

public:
    bool                     addWarp(std::string name, const Vec3& pos, Dimension& dim);
    bool                     removeWarp(std::string name);
    bool                     warpTo(Player& player, std::string name);
    std::vector<std::string> listWarps();
};

} // namespace TLModule