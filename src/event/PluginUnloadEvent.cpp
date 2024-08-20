#include "event/PluginUnloadEvent.h"
#include "Exception.h"
#include "TSEssential.h"

#include <string>

// template <>
// PluginUnloadEvent<std::function<void(void)>>::PluginUnloadEvent() {}


PluginUnloadEvent::PluginUnloadEvent() : CustomEventBase<std::function<void(void)>>("Plugin Unload", false,false){}

bool PluginUnloadEvent::CALL() {
    try {
        for (auto val :beforeListener) {
            val.second();
        }
    } catch (...) {
        std::string str = "CALL CustomEvent \"" + getName() + "\"(BEFORE)";
        _CATCH_CODES(str)
        return false;// 遭遇错误
    }
    try {
        for (auto val : afterListener) {
            val.second();
        }
    } catch (...) {
        std::string str = "CALL CustomEvent \"" + getName() + "\"(AFTER)";
        _CATCH_CODES(str)
        return false; // 遭遇错误
    }
    return true;
}