#include "Global.h"
#include <ll/api/io/FileUtils.h>

#include <filesystem>

namespace fs = std::filesystem;

namespace TSEssential {
bool ExtractLang() {
    bool isExtracted = false;
    isExtracted      = true;
    if (!fs::exists(LangDir)) {
        fs::create_directories(LangDir);
    }
    // todo: add more languages
    if (!fs::exists(LangDir / "zh_CN.json")) {
        auto zh_CN_LangPath = LangDir / "zh_CN.json";
        // extract lang file
        ll::utils::file_utils::writeFile(zh_CN_LangPath, zh_CN);
        isExtracted = true;
    }
    return isExtracted;
}
} // namespace TSEssential