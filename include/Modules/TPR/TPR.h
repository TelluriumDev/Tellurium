#pragma once

#include "mc/world/level/dimension/Dimension.h"
#include <mc/math/Vec3.h>
#include <mc/world/actor/player/Player.h>


namespace TSModule {
class TPR {

public:
    ~TPR();

private:
    // ?: 这里至于为什么不在生成坐标函数里加维度参数 是因为没必要 (可能有必要吧 但是也没必要)
    // 检查生成坐标是否安全
    bool isSafe(Vec3& pos, Dimension* dim);
    // 生成一个坐标
    Vec3 generatePos(Vec3& pos);

public:
    static bool TPRPlayer(Player* player);
};
} // namespace TSModule