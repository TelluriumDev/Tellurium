#pragma once


#include "ll/api/i18n/I18n.h"
#include "ll/api/mod/NativeMod.h"

#include <filesystem>

using namespace ll::i18n_literals;

namespace TLUtil::I18n {

void        initI18n(ll::mod::NativeMod&);
std::string translate(const std::string& key, const std::string& locale);

std::filesystem::path getLangDir();

} // namespace TLUtil::I18n
