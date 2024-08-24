#pragma once
#include <string>
#include <funct

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
    
    std::function<bool(const T&)> before;
    std::function<bool(const T&)> after;
}