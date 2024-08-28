#include "Utils/I18n/I18n.h"
#include "Config/Config.h"

namespace Tellurium::I18n {
void initI18n(ll::mod::NativeMod& self) {
    langDir = self.getLangDir();
    ll::i18n::load(langDir);
    ll::i18n::getInstance()->mDefaultLocaleName = config.Language;
}
std::string_view translate(std::string_view key, std::string_view locale) {
    i18n.load(langDir);
    i18n.mDefaultLocaleName = locale;
    return i18n.get(key);
}

} // namespace Tellurium::I18n