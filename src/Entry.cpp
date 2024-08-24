#include "Entry.h"
#include "TSEssential.h"

#include <memory>

#include "Global.h"
#include "ll/api/mod/RegisterHelper.h"
#include <ll/api/Versions.h>

namespace TSEssential {

static std::unique_ptr<Entry> instance;

Entry& Entry::getInstance() { return *instance; }
// 放在这里让TSEssential.cpp好看一点 qwq
void CheckProtocolVersion() {
    logger.debug("Checking Network Protocol Version...");
    auto NetworkVersion = ll::getNetworkProtocolVersion();
    if (NetworkVersion != TARGET_NETWORK_VERSION) {
        logger.warn("Unsupported Network Version: " + std::to_string(NetworkVersion));
        logger.warn("The mod probably won't work correctly");
        logger.warn("Target Network Version: " + std::to_string(TARGET_NETWORK_VERSION));
    }
}
bool Entry::load() {
    CheckProtocolVersion(); // 协议版本不阻止插件加载，所以不要返回值
    return TSEssential::Load();
}
bool Entry::enable() { return TSEssential::Enable(); }

bool Entry::disable() { return TSEssential::Disable(); }

bool Entry::unload() { return TSEssential::Unload(); }
} // namespace TSEssential

// 不要动，谁动谁死
LL_REGISTER_MOD(TSEssential::Entry, TSEssential::instance);