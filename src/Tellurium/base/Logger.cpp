#include "Tellurium/base/Global.h"

#ifdef TU_DEBUG
#include <ll/api/service/Bedrock.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/level/Level.h>
#endif

namespace Tellurium {

std::unique_ptr<LoggerManage>& LoggerManage::getInstance() {
    static std::unique_ptr<LoggerManage> instance;
    if (!instance) instance = std::make_unique<LoggerManage>();
    return instance;
}

std::unique_ptr<ll::Logger>& LoggerManage::getOrCreateLogger(std::string const& name) {
    if (!mLoggers.contains(name)) {
        mLoggers[name] = std::make_unique<ll::Logger>(I18n::tr("Tellurium.Logger.Title." + name));
#ifdef TU_DEBUG
        mLoggers[name]->setPlayerOutputFunc([](std::string_view msg) -> void {
            ll::service::getLevel().and_then([&msg](Level& level) -> bool {
                level.forEachPlayer([&msg](Player& player) -> bool {
                    player.sendMessage(msg);
                    return true;
                });
                return true;
            });
        });
#endif
    }
    return mLoggers[name];
}

void LoggerManage::removeLogger(std::string const& name) { mLoggers.erase(name); }
} // namespace Tellurium