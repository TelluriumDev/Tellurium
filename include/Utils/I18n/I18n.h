#pragma once

#include "Config/Config.h"
#include "Global.h"
#include <ll/api/i18n/I18n.h>

using namespace ll::i18n_literals;

static std::filesystem::path   langDir;
static ll::i18n::MultiFileI18N i18n;

namespace Tellurium::I18n {

void             initI18n(ll::mod::NativeMod&);
std::string_view translate(std::string_view key, std::string_view locale);

} // namespace Tellurium::I18n
