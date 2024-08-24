#include "event/PluginUnloadEvent.h"

#include "mc/nbt/CompoundTag.h"

void PluginUnloadEvent::serialize(CompoundTag& nbt) const {
    Event::serialize(nbt);
    nbt["self"] = (uintptr_t)&self();
}