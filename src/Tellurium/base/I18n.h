#pragma once

#include "Tellurium/base/Macro.h"

#include <string>

class Player;
class CommandOrigin;

namespace Tellurium::I18n {

TUAPI std::string tr(std::string const& key, std::string const& language = {});

template <typename... Args>
TUAPI std::string tr(std::string const& key, std::string const& language, Args&&... args);

template <typename... Args>
TUAPI std::string tr(std::string const& key, Player const& player, Args&&... args);

template <typename... Args>
TUAPI std::string tr(std::string const& key, CommandOrigin const& origin, Args&&... args);

} // namespace Tellurium::I18n