#include <string>
#include <functional>

#define __HPP_CLASS_FUNCTION_CONTENT__                                \
    bool onExport(const std::string& alias);                          \
    inline std::string getName() { return name; }                     \
    inline bool getIsExportEvent(){ return isExportEvent; }           \
    inline bool getCanCancel(){ return canCancel; }                   \
    inline bool unBefore(long id);                                    \
    inline bool unAfter(long id);                                     \
    inline long on(std::function<bool(T& param)> func);               \
    inline long onAfter(std::function<bool(T& param)> func);          \
    // inline long on(const std::function<void(T& param)> func);      \
    // inline long onAfter(const std::function<void(T& param)> func); \
    inline bool CALL(const T& param);                                 \