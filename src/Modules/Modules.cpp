#include "Modules/Modules.h"
#include "Global.h"
#include <memory>

namespace TLModule {

// ! 究极大屎山

Modules* modules = nullptr;


void initModules() {
    if (modules == nullptr) {
        modules = new Modules();
    }
    if (modules == nullptr) {
        logger.error("Cannot initialize modules!!!"_tr());
    } else {
        logger.debug("Modules initialized!!!"_tr());
    }
}

Modules* getInstance() {
    if (modules != nullptr) {
        return modules;
    } else {
        logger.info("Cannot find modules instance, please initModules first!!!"_tr());
        initModules();
        return modules;
    }
}
Modules::Modules() {
    // mTPA   = std::make_shared<TPA>();
    // mMoney = std::make_shared<Money>("money");
    mWarp = std::make_shared<Warp>();
    mHome = std::make_shared<Home>();
    // mBack  = std::make_shared<Back>();
}
} // namespace TLModule