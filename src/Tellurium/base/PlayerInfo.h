#pragma once

#include "Tellurium/base/Macro.h"

#include <mc/deps/core/mce/UUID.h>
#include <optional>
#include <string>

namespace Tellurium::PlayerInfo {

struct PlayerInfoEntry {
    mce::UUID const&   uuid;
    std::string const& name;
    std::string const& xuid;
};

TUAPI std::optional<PlayerInfoEntry> fromUuid(mce::UUID const& uuid);

TUAPI std::optional<PlayerInfoEntry> fromName(std::string const& name);

TUAPI std::optional<PlayerInfoEntry> fromXuid(std::string const& xuid);

} // namespace Tellurium::PlayerInfo