#include "Tellurium/base/Global.h"

#include <ll/api/i18n/I18n.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/world/actor/player/Player.h>

namespace Tellurium::I18n {

std::string tr(std::string const& key, std::string const& language) {
    return std::string(ll::i18n::getInstance()->get(key, language));
}

template <typename... Args>
std::string tr(std::string const& key, std::string const& language, Args&&... args) {
    return fmt::vformat(tr(key, language), fmt::make_format_args(args...));
}

template <typename... Args>
std::string tr(std::string const& key, Player const& player, Args&&... args) {
    return fmt::vformat(tr(key, player.getLocaleName()), fmt::make_format_args(args...));
}

template <typename... Args>
std::string tr(std::string const& key, CommandOrigin const& origin, Args&&... args) {
    auto* entity = origin.getEntity();
    return fmt::vformat(
        tr(key, entity != nullptr && entity->isPlayer() ? ((Player*)entity)->getLocaleName() : ""),
        fmt::make_format_args(args...)
    );
}
} // namespace Tellurium::I18n