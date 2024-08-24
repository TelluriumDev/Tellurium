#include "events/PluginUnloadEvent.h"

#include <mc/nbt/CompoundTag.h>

void PluginUnloadEvent::serialize(CompoundTag& nbt) const {
    Event::serialize(nbt);
    nbt["mSelf"] = (uintptr_t)&self();
}