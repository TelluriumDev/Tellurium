#include "Tellurium/base/Global.h"

#include <GMLIB/Server/I18nAPI.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/world/actor/player/Player.h>

namespace Tellurium::I18n {

std::string tr(std::string const& key, std::string const& language, std::vector<std::string> const& params) try {
    return I18nAPI::get(key, params, language.empty() ? I18nAPI::getCurrentLanguageCode() : language);
} catch (...) {
    return key;
}

std::string tr(std::string const& key, Player const& player, std::vector<std::string> const& params) {
    return tr(key, player.getLocaleName(), params);
}

std::string tr(std::string const& key, CommandOrigin const& origin, std::vector<std::string> const& params) {
    auto* entity = origin.getEntity();
    return tr(key, entity != nullptr && entity->isPlayer() ? ((Player*)entity)->getLocaleName() : "", params);
}
} // namespace Tellurium::I18n