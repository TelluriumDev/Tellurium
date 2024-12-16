#pragma once

#include "Tellurium/base/Macro.h"

#include <string>
#include <vector>

class Player;
class CommandOrigin;

namespace Tellurium::I18n {

TUAPI std::string
      tr(std::string const& key, std::string const& language = {}, std::vector<std::string> const& params = {});

TUAPI std::string tr(std::string const& key, Player const& player, std::vector<std::string> const& params = {});

TUAPI std::string tr(std::string const& key, CommandOrigin const& origin, std::vector<std::string> const& params = {});

} // namespace Tellurium::I18n