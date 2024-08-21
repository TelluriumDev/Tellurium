#pragma once
#include "CustomEvent.h"

#include <ll/api/mod/NativeMod.h>


struct PluginUnloadEventParam {
    ll::mod::NativeMod&  mSelf;
};
class PluginUnloadEvent : public CustomEventBase<PluginUnloadEventParam> {
public:
    PluginUnloadEvent() : CustomEventBase<PluginUnloadEventParam>("PluginUnload", false, false){};
};