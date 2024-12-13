#pragma once

#include <span> // temporary repair workflow

#include "Tellurium/base/Config.h"
#include "Tellurium/base/Logger.h"
#include "Tellurium/base/Macro.h"
#include "Tellurium/base/I18n.h"

#include <ll/api/base/StdInt.h>
#include <ll/api/mod/Mod.h>
#include <ll/api/utils/ErrorUtils.h>
#include <memory>

namespace Tellurium {
extern TUAPI ll::mod::Mod& getSelfMod();
extern TUAPI void          printWelcomeMsg();
} // namespace Tellurium