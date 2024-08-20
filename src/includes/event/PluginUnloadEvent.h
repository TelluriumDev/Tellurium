#pragma once

#include "CustomEvent.h"
#include <functional>

class PluginUnloadEvent : public CustomEventBase<std::function<void(void)>> {
public:
    PluginUnloadEvent();
    bool CALL();
};