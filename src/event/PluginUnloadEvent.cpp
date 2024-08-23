#include "event/PluginUnloadEvent.h"

#define T PluginUnloadEventParam

bool PluginUnloadEvent::CALL(const T& param) {
    return CustomEventBase<T>::CALL(param);
}