#pragma once

#include <filesystem>
#include <ll/api/i18n/I18n.h>
#include <ll/api/mod/NativeMod.h>


using namespace ll::i18n_literals;


namespace Tellurium::I18n {

void                  initI18n(ll::mod::NativeMod&);
std::string_view      translate(std::string_view key, std::string_view locale);
std::filesystem::path getLangDir();

} // namespace Tellurium::I18n
