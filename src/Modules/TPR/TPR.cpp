#include "Modules/TPR/TPR.h"
#include "Config/Config.h"
#include "mc/math/Vec3.h"

#include <mc/world/level/BlockPos.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/ChunkPos.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/actor/BlockActor.h>
#include <mc/world/level/chunk/ChunkSource.h>
#include <mc/world/level/chunk/LevelChunk.h>


#include <stdlib.h>


namespace TLModule {

bool TPR::isSafe(BlockPos, Dimension&) {
    return false;
}


int TPR::random(int min, int max) { return rand() % (max - min + 1) + min; };


BlockPos TPR::generatePos() {
    BlockPos pos = BlockPos(
        random(config.Modules.TPR.MinPosRange, config.Modules.TPR.MinPosRange),
        random(-64, 320),
        random(config.Modules.TPR.MinPosRange, config.Modules.TPR.MinPosRange)
    );
    return pos;

};

// ! 感觉有大问题跑路

bool TPR::TPRPlayer(Player& player, bool& res) {
    auto pos = generatePos();
    res      = isSafe(generatePos(), player.getDimension());
    if (res) {
        pos.y += 1;
        player.teleport(pos, player.getDimension().getDimensionId(), player.getRotation());
    } else {
       
    }
    return res;
}
} // namespace TLModule