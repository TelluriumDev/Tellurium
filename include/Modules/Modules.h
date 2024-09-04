#pragma once

#include "Modules/Back/Back.h"
#include "Modules/Money/Money.h"
#include "Modules/TPA/TPA.h"


namespace TLModule {

enum ModuleType : int { ModuleTPA = 0, ModuleMoney, ModuleBack, ModuleTPR };

class Modules {
private:
    // 卸载模块
    ~Modules();

public:
    TPA*   mTPA   = nullptr;
    Money* mMoney = nullptr;
    Back*  mBack  = nullptr;

    // 构造函数内进行初始化所有模块
    Modules();

    bool destroy();
    bool destroy(ModuleType& type);
};

void initModules();

Modules* getModulesInstance();
} // namespace TLModule