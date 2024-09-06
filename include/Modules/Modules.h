#pragma once

#include "Modules/Back/Back.h"
#include "Modules/Home/Home.h"
#include "Modules/Money/Money.h"
#include "Modules/TPA/TPA.h"
#include "Modules/Warp/Warp.h"


namespace TLModule {

class Modules {
private:
public:
    // std::shared_ptr<TPA>   mTPA;
    // std::shared_ptr<Money> mMoney;
    // std::shared_ptr<Back>  mBack;
    std::shared_ptr<Warp> mWarp;
    std::shared_ptr<Home>  mHome;


    // 构造函数内进行初始化所有模块
    Modules();
};

void initModules();

Modules* getInstance();

} // namespace TLModule