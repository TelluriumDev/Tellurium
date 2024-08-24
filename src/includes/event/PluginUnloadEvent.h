#pragma once

#include <ll/api/mod/NativeMod.h>

#include <ll/api/event/Event.h>
#include <ll/api/event/EventBus.h>

class CompoundTag;

class PluginUnloadEvent : public ll::event::Event {
private:
    ll::mod::NativeMod&  mSelf;

public:
    constexpr explicit PluginUnloadEvent(ll::mod::NativeMod& self) : mSelf(self) {};

    inline ll::mod::NativeMod& self() const { return mSelf; };

    LLAPI void serialize(CompoundTag&) const override;
};