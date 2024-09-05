#pragma once

#include <string>

namespace TLCommand::WarpCommand {

struct Param {
    std::string name;
};

void RegWarpCommand();

}; // namespace TLCommand::WarpCommand