#pragma once
#include "CustomEvent.h"

#include <ll/api/mod/NativeMod.h>
#include <ll/api/event/Event.h>
#include <ll/api/event/EventBus.h>


struct PluginUnloadEventParam {
    ll::mod::NativeMod&  mSelf;
};
class PluginUnloadEvent : public CustomEventBase<PluginUnloadEventParam> {
public:
    PluginUnloadEvent() : CustomEventBase<PluginUnloadEventParam>("PluginUnload", false, false){};
    bool CALL(const PluginUnloadEventParam &param);
    // bool 
};