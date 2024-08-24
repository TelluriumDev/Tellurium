#include "TSEssential.h"
#include "Config.h"
#include "Global.h"
#include "utils/I18n.h"

#include <ll/api/command/Command.h>

namespace TSEssential {
bool Load() {
    if (!LoadConfig()) {
        return false;
    }
    // Load Language
    ExtractLang();
    ll::i18n::load(LangDir);
    ll::i18n::getInstance()->mDefaultLocaleName = config.Language;
    return true;
}
bool Unload() { return true; }
bool Enable() { return true; }
bool Disable() {
    delete &logger;
    return true;
}
} // namespace TSEssential
