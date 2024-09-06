#include "Utils/I18n/I18n.h"
#include "Config/Config.h"

#include <filesystem>


namespace TLUtil::I18n {

std::filesystem::path   LangDir;
ll::i18n::MultiFileI18N i18n;

void initI18n(ll::mod::NativeMod& self) {
    LangDir = self.getLangDir();
    std::filesystem::create_directory(LangDir);
    ll::i18n::load(LangDir);
    ll::i18n::getInstance()->mDefaultLocaleName = config.Language;
}
std::string translate(const std::string& key, const std::string& locale) {
    i18n.load(LangDir);
    i18n.mDefaultLocaleName = locale;
    return std::string(i18n.get(key));
}
std::filesystem::path getLangDir() { return LangDir; }

} // namespace TLUtil::I18n