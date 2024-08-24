#pragma once
#include "Global.h"
#include "nlohmann/json.hpp"
#include "utils/I18n.h"

#include <filesystem>
#include <iostream>

#include <ll/api/i18n/I18n.h>
#include <ll/api/io/FileUtils.h>


static std::string zh_CN = R"({
})";

static std::string en_US = R"({
})";

namespace TSEssential {
    bool ExtractLang();
}