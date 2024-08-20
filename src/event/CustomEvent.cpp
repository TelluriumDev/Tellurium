#include "event/CustomEvent.h"


template <typename T>
CustomEventBase<T>::CustomEventBase(const std::string& name, const bool& isExportEvent, const bool& canCancel) {
    this->name =          name;
    this->isExportEvent = isExportEvent;
    this->canCancel =     canCancel;
}
// void CustomEvent<T>::unBefore(int id) {
//     beforeListener.erase(id);
// }

template <typename T>
int CustomEventBase<T>::on(const T& func) {
    index++;
    beforeListener[index] = func;
}
template <typename T>
int CustomEventBase<T>::onAfter(const T& func) {
    index++;
    afterListener[index] = func;
}