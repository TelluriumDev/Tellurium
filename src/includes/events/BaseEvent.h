#pragma once
#include <string>
#include <functional>

template<typename Param>
class BaseEvent {
public:
    BaseEvent();
    ~BaseEvent();

    std::string& getName();
    bool getCanExport();
    bool getCanCancel();

    bool execute(const T&) = 0;
    void onBefore(std::func) {

    }

private:
    std::string name;
    bool CanExport;
    bool CanCancel;
    
    std::function<bool(T&)> before;
    std::function<bool(T&)> after;
}