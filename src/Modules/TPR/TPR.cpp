#include "Modules/TPR/TPR.h"
#include "Modules/Modules.h"

namespace TSModule {
TPR::~TPR() {
    delete getModulesInstance()->mTPR;
    getModulesInstance()->mTPR = nullptr;
}
} // namespace TSModule