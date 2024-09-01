#include "Utils/I18n/I18n.h"
#include "Config/Config.h"

#include <filesystem>

#include <mc/certificates/WebToken.h>
#include <mc/network/ConnectionRequest.h>
#include <mc/network/ServerNetworkHandler.h>
#include <mc/world/actor/player/Player.h>

#include <ll/api/service/Bedrock.h>

namespace Tellurium::I18n {

std::filesystem::path   LangDir;
ll::i18n::MultiFileI18N i18n;

void initI18n(ll::mod::NativeMod& self) {
    LangDir = self.getLangDir();
    ll::i18n::load(LangDir);
    ll::i18n::getInstance()->mDefaultLocaleName = config.Language;
}
std::string translate(const std::string& key, const std::string& locale) {
    i18n.load(LangDir);
    i18n.mDefaultLocaleName = locale;
    return std::string(i18n.get(key));
}
std::string translate(const std::string& key, Player& pl) {
    auto json = // TODO 完成PlayerData后需要重写
        ll::service::getServerNetworkHandler()->fetchConnectionRequest(pl.getNetworkIdentifier()).mRawToken->mDataInfo;
    auto langCode = json.get("LanguageCode", "Unknown").asString("Unknown");
    return translate(key, langCode);
}
std::filesystem::path getLangDir() { return LangDir; }

} // namespace Tellurium::I18n