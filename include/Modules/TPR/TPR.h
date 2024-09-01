#pragma once

#include <mc/math/Vec3.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/level/BlockPos.h>
#include <mc/world/level/dimension/Dimension.h>


namespace TLModule {
class TPR {


private:
    // 检查生成坐标是否安全
    bool isSafe(BlockPos pos, Dimension& dim);
    // 生成一个坐标
    BlockPos generatePos();

    int random(int min, int max);

public:
 bool TPRPlayer(Player& player, bool &res);
};
} // namespace TLModule