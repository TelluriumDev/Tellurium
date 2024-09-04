#pragma once

#include "mc/deps/core/mce/UUID.h"

class CompoundTag;

namespace OfflinePlayerNbtUtils {
CompoundTag* getOfflinePlayerNbt(mce::UUID& uuid);
bool         saveOfflinePlayerNbt(mce::UUID& uuid, CompoundTag* nbt);
bool         deleteOfflinePlayerNbt(mce::UUID& uuid);
} // namespace OfflinePlayerNbtUtils