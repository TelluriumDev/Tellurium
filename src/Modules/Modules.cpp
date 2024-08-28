#include "Modules/Modules.h"
#include "Global.h"

namespace TSModule {

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

Modules* getModulesInstance() {
    if (modules != nullptr) {
        return modules;
    } else {
        logger.info("Cannot find modules instance, please call initModules() first!!!"_tr());
        initModules();
        return modules;
    }
}
Modules::Modules() {
    // mTPA   = new TPA();
    // mTPR   = new TPR();
    // mMoney = new Money();
    // mBack  = new Back();
    // TODO: 其他模块
}

Modules::~Modules() {
    delete mTPA;
    delete mTPR;
    delete mMoney;
    delete mBack;
    // TODO: 其他模块

    // ?: 应该没有问题...
    delete modules;

    // 防止悬空指针 别问 问就是 CodeGeeX
    mTPA    = nullptr;
    mTPR    = nullptr;
    mMoney  = nullptr;
    mBack   = nullptr;
    modules = nullptr;
}

bool Modules::destroy() {
    try {
        delete modules;
        // 防止悬空指针
        modules = nullptr;
        return true;
    } catch (...) {
        logger.error("Cannot destroy modules!!!"_tr());
        return false;
    }
}

bool Modules::destroy(ModuleType& type) {
    switch (type) {
    case ModuleType::ModuleTPA: {
        try {
            delete mTPA;
            mTPA = nullptr;
            return true;
        } catch (...) {
            logger.error("Cannot destroy TPA module!!!"_tr());
            return false;
        }
        break;
    }
    case ModuleType::ModuleTPR: {
        try {
            delete mTPR;
            mTPR = nullptr;
            return true;
        } catch (...) {
            logger.error("Cannot destroy TPR module!!!"_tr());
            return false;
        }
        break;
    }
    case ModuleType::ModuleMoney: {
        try {
            delete mMoney;
            mMoney = nullptr;
            return true;
        } catch (...) {
            logger.error("Cannot destroy Money module!!!"_tr());
            return false;
        }
        break;
    }
    case ModuleBack: {
        try {
            delete mBack;
            mBack = nullptr;
            return true;
        } catch (...) {
            logger.error("Cannot destroy Back module!!!"_tr());
            return false;
        }
        break;
    }
    default: {
        return false;
        break;
    }
    }
}
} // namespace TSModule