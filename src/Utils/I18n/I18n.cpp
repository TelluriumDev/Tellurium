#include "Utils/I18n/I18n.h"
#include "Config/Config.h"
#include <filesystem>

namespace Tellurium::I18n {

std::filesystem::path   LangDir;
ll::i18n::MultiFileI18N i18n;

void initI18n(ll::mod::NativeMod& self) {
    LangDir = self.getLangDir();
    ll::i18n::load(LangDir);
    ll::i18n::getInstance()->mDefaultLocaleName = config.Language;
}
std::string_view translate(std::string_view key, std::string_view locale) {
    i18n.load(LangDir);
    i18n.mDefaultLocaleName = locale;
    return i18n.get(key);
}
std::filesystem::path getLangDir() { return LangDir; }

} // namespace Tellurium::I18n