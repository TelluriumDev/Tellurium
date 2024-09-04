#include "Modules/Warp/Warp.h"
#include "Config/Config.h"
#include "Global.h"
#include "Utils/Data/JsonHandler.h"


namespace TLModule {
Warp::Warp() { mWarpData = std::make_unique<TLUtil::JsonHandler>(TLConfig::getDataDir() / "warp.json"); }

bool Warp::addWarp(std::string& name, Vec3& pos, Dimension& dim) {
    try {
        mWarpData->set(name, json({pos.x, pos.y, pos.z, dim.getDimensionId().id}));
        return true;
    } catch (std::exception& e) {
        logger.error("Failed to add warp: {0}"_tr(e.what()));
        return false;
    }
}

bool Warp::removeWarp(std::string& name) {
    try {
        mWarpData->del(name);
        return true;
    } catch (std::exception& e) {
        logger.error("Failed to remove warp: {0}"_tr(e.what()));
        return false;
    }
}

std::vector<std::string> Warp::listWarps() {
    std::vector<std::string> warps;
    try {
        for (auto it = mWarpData->begin(); it != mWarpData->end(); ++it) {
            auto pos  = it.value().get<std::vector<int>>();
            auto name = it.key();
            warps.push_back(
                fmt::v10::format("Warp: {0}, Pos: {1}, {2}, {3}, Dim: {4}", name, pos[0], pos[1], pos[2], pos[3])
            );
        }
    } catch (std::exception& e) {
        logger.error("Failed to list warps: {0}"_tr(e.what()));
    }
    return warps;
}

bool Warp::warpTo(Player& player, std::string& name) {
    try {
        auto pos = mWarpData->get<json>(name).get<std::vector<int>>();
        player.teleport(Vec3(pos[0], pos[1], pos[2]), DimensionType(pos[3]));
        return true;
    } catch (std::exception& e) {
        logger.error("Failed to warp to {0}: {1}"_tr(name, e.what()));
        return false;
    }
}

} // namespace TLModule