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


namespace TSModule {

bool TPR::isSafe(BlockPos pos, Dimension& dim) {

    bool  res         = false;
    auto& blockSource = dim.getBlockSourceFromMainChunkSource();
    auto& chunkSource = blockSource.getChunkSource();

    ChunkPos chunkPos = ChunkPos(pos);

    chunkSource.getOrLoadChunk(chunkPos, ChunkSource::LoadMode::Deferred, false);

    auto& block      = blockSource.getBlock(pos);
    pos.y           += 1;
    auto& blockUp    = blockSource.getBlock(pos);
    pos.y           += 1;
    auto& blockUpUp  = blockSource.getBlock(pos);
    if (block.isEmpty() || block.isAir() || block.isLavaFlammable() || block.isWaterBlocking()
        || (!blockUp.isAir() && !blockUpUp.isAir())) {
        res = false;
    } else {
        res = true;
    }

    return res;
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
} // namespace TSModule