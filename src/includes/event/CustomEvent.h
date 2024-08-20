#pragma once
#include <string>
#include <unordered_map>

template <typename T>
class CustomEventBase {
public:
    CustomEventBase(const std::string& name, const bool& isExportEvent, const bool& canCancel = true);

    inline std::string getName() { return name; }
    inline bool getCanCancel(){ return canCancel; }

    inline bool unBefore(int id) {
        beforeListener.erase(id);
        return true;
    };
    inline bool unAfter(int id) {
        afterListener.erase(id);
        return true;
    };
    int on(const T& func);
    int onAfter(const T& func);

    // PLEASE OVERWRITE!!!
    bool CALL(...);

protected:
    std::string name;
    bool        isExportEvent;
    bool        canCancel;
    std::unordered_map<int, T> beforeListener;
    std::unordered_map<int, T> afterListener;
    long index;// auto++
};