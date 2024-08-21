#include "event/CustomEvent.h"
#include "Exception.h"
#include "TSEssential.h"
#include <functional>
#include <vector>

// CustomEventBase<T>*
// 模板类vector实在是太复杂了，用void*代替
static std::vector<void*> events{};
template <typename T>
std::vector<CustomEventBase<T>*>& CustomEventBase<T>::getEvents() {
    return (std::vector<CustomEventBase<T>*>&)events;
}

template <typename T>
CustomEventBase<T>::CustomEventBase(const std::string& name1, const bool& isExportEvent1, const bool& canCancel1)
: name(name1),
  isExportEvent(isExportEvent1),
  canCancel(canCancel1) {
    events.push_back((void*)this);
}
template <typename T>
CustomEventBase<T>::~CustomEventBase() {
    for (auto begin = events.begin(),end = events.end();begin!=end;begin++) {
        if (*begin == (void*)this) {
            events.erase(begin);
        }
    }
}
template <typename T>
long CustomEventBase<T>::on(const std::function<void(T& param)>& func) {
    index++;
    beforeListener[index] = func;
    return index;
}
template <typename T>
long CustomEventBase<T>::onAfter(const std::function<void(T& param)>& func) {
    index++;
    afterListener[index] = func;
    return index;
}
template <typename T>
bool CustomEventBase<T>::unBefore(long id) {
    beforeListener.erase(id);
    return true;
}
template <typename T>
bool CustomEventBase<T>::unAfter(long id) {
    afterListener.erase(id);
    return true;
}
template <typename T>
bool CustomEventBase<T>::CALL(const T& param) {
    bool res = true;
    try {
        for (auto& val : beforeListener) {
            val.second(param);
        }
    } catch (...) {
        std::string str = "CALL CustomEvent \"" + getName() + "\"(BEFORE)";
        _CATCH_CODES(str)
        res = false; // 遭遇错误
    }
    try {
        for (auto& val : afterListener) {
            val.second(param);
        }
    } catch (...) {
        std::string str = "CALL CustomEvent \"" + getName() + "\"(AFTER)";
        _CATCH_CODES(str)
        res = false; // 遭遇错误
    }
    return res;
}