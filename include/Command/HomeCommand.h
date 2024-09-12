#pragma once

#include <string>

namespace TLCommand::HomeCommand {

struct Param {
    std::string name;
};


void RegHomeCommand();

}; // namespace TLCommand::HomeCommand