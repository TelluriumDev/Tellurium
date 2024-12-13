#include "Tellurium/base/Global.h"

#include <GMLIB/Server/UserCache.h>
#include <ll/api/service/PlayerInfo.h>

#define CALLBACK(FUNC_NAME)                                                                                            \
    if (auto entry = ll::service::PlayerInfo::getInstance().FUNC_NAME(identifier)) {                                   \
        return PlayerInfoEntry{entry->uuid, entry->name, entry->xuid};                                                 \
    }                                                                                                                  \
    if (auto entry = GMLIB::UserCache::FUNC_NAME(identifier)) {                                                        \
        return PlayerInfoEntry{entry->mUuid, entry->mName, entry->mXuid};                                              \
    }                                                                                                                  \
    return std::nullopt;

namespace Tellurium::PlayerInfo {

std::optional<PlayerInfoEntry> fromUuid(mce::UUID const& identifier) { CALLBACK(fromUuid); }

std::optional<PlayerInfoEntry> fromName(std::string const& identifier) { CALLBACK(fromXuid); }

std::optional<PlayerInfoEntry> fromXuid(std::string const& identifier) { CALLBACK(fromXuid); }

} // namespace Tellurium::PlayerInfo