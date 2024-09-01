#include "Utils/OfflinePlayerNbt/OfflinePlayerNbtUtils.h"
#include "Global.h"

#include <mc/common/DBHelpers.h>
#include <mc/nbt/CompoundTag.h>
#include <mc/nbt/StringTag.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/storage/DBStorage.h>

#include <ll/api/service/Bedrock.h>

#include <string>

namespace OfflinePlayerNbtUtils {
std::string getServerId(mce::UUID& uuid) {
    DBStorage&  storage = *static_cast<DBStorage*>(&ll::service::getLevel()->getLevelStorage());
    std::string key     = "player_" + uuid.asString();
    if (!storage.hasKey(key, DBHelpers::Category::Player)) {
        return "";
    }
    auto data = storage.getCompoundTag(key, DBHelpers::Category::Player);
    if (!data) {
        return "";
    }
    auto serverId = *static_cast<StringTag*>(&data->at("ServerId").get());
    if (serverId.empty()) {
        return "";
    }
    return serverId;
}

CompoundTag* getOfflinePlayerNbt(mce::UUID& uuid) {
    DBStorage& storage  = *static_cast<DBStorage*>(&ll::service::getLevel()->getLevelStorage());
    auto       serverId = getServerId(uuid);
    if (serverId == "") {
        return nullptr;
    }
    // logger.warn("ServerId: {0}", serverId);
    auto nbt = storage.getCompoundTag(serverId, DBHelpers::Category::Player);
    return nbt.release();
}
bool saveOfflinePlayerNbt(mce::UUID& uuid, CompoundTag* nbt) {
    DBStorage& storage  = *static_cast<DBStorage*>(&ll::service::getLevel()->getLevelStorage());
    auto       serverId = getServerId(uuid);
    if (serverId == "") {
        return false;
    }
    storage.saveData(serverId, nbt->toBinaryNbt(), DBHelpers::Category::Player);
    return true;
}
bool deleteOfflinePlayerNbt(mce::UUID& uuid) {
    DBStorage& storage  = *static_cast<DBStorage*>(&ll::service::getLevel()->getLevelStorage());
    auto       serverId = getServerId(uuid);
    if (serverId == "") {
        return false;
    }
    storage.deleteData(serverId, DBHelpers::Category::Player);
    return true;
}
} // namespace OfflinePlayerNbtUtils