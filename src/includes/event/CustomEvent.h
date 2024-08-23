#pragma once
#include "event/DefineHContent.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

// template <typename T>
// class CustomEventBase;

// template <typename T>
// std::vector<CustomEventBase<T>*> allEvent;

template <typename T>
class CustomEventBase {
private:
    static std::vector<CustomEventBase<T>*>& getEvents();

public:
    static CustomEventBase* getEvent(const std::string& name) {
        for (CustomEventBase<T>* event : getEvents()) {
            if (event->getName().starts_with(name)) {
                return event;
            }
        }
        return nullptr;
    }
    static std::vector<CustomEventBase<T>*>::iterator EventListBegin() { return getEvents().begin(); }
    static std::vector<CustomEventBase<T>*>::iterator EventListEnd() { return getEvents().end(); }

public:
    CustomEventBase(const std::string& name1, const bool& isExportEvent1, const bool& canCancel1 = true);
    ~CustomEventBase();
    __HPP_CLASS_FUNCTION_CONTENT__

protected:
    std::string name;
    bool        isExportEvent;
    bool        canCancel;
    std::unordered_map<int, const std::function<bool(T& param)>> beforeListener{};
    std::unordered_map<int, const std::function<bool(T& param)>> afterListener{};
    long index = 0;// auto++
};
