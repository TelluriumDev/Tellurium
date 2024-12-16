#pragma once

#include <span> // temporary repair workflow

#include "Tellurium/base/Config.h"
#include "Tellurium/base/I18n.h"
#include "Tellurium/base/Logger.h"
#include "Tellurium/base/Macro.h"
#include "Tellurium/base/PlayerInfo.h"

#include <ll/api/base/StdInt.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/server/ServerStartedEvent.h>
#include <ll/api/mod/Mod.h>
#include <ll/api/reflection/DESerialization.h>
#include <ll/api/reflection/Serialization.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>

#include <ll/api/utils/ErrorUtils.h>
#include <memory>
#include <nlohmann/json.hpp>

namespace Tellurium {
extern TUAPI ll::mod::Mod& getSelfMod();
extern TUAPI void          printWelcomeMsg();
} // namespace Tellurium