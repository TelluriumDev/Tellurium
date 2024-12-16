#include "Tellurium/Entry.h"
#include "Tellurium/base/Global.h"
#include "Tellurium/modules/EconomicSystem/EconomicSystem.h"
#include "Tellurium/modules/HomeSystem/HomeSystem.h"

#include <GMLIB/Files/FileUtils.h>
#include <GMLIB/Files/Language/ResourceLanguage.h>
#include <GMLIB/Server/I18nAPI.h>
#include <ll/api/io/FileUtils.h>
#include <ll/api/mod/RegisterHelper.h>
#include <ll/api/utils/StringUtils.h>
#include <memory>
#include <pl/Config.h>

namespace Tellurium {

void printWelcomeMsg() {
    auto& logger = LoggerManage::getInstance()->getOrCreateLogger("WelcomeMsg");

    auto print = [&logger](std::string const& str) -> void {
        logger->info(
            ll::sys_utils::isStdoutSupportAnsi() && pl::pl_color_log ? fmt::format(fmt::fg(fmt::color::aqua), str) : str
        );
    };

    print(R"(                                                                               )");
    print(R"(           _______     _  _               _                                    )");
    print(R"(          |__   __|   | || |             (_)                                   )");
    print(R"(             | |  ___ | || | _   _  _ __  _  _   _  _ __ ___                   )");
    print(R"(             | | / _ \| || || | | || '__|| || | | || '_ ` _ \                  )");
    print(R"(             | ||  __/| || || |_| || |   | || |_| || | | | | |                 )");
    print(R"(             |_| \___||_||_| \__,_||_|   |_| \__,_||_| |_| |_|                 )");
    print(R"(                                                                               )");
    print(R"(          Tellurium is a free mod under GPL Version 3 License.                 )");
    print(R"(    Help us improve Tellurium! -> https://github.com/TelluriumDev/Tellurium    )");
    print(R"(                    Copyright (C)  2024 TelluriumDev                           )");
    print(R"(                                                                               )");

    LoggerManage::getInstance()->removeLogger("WelcomeMsg");
}

std::unique_ptr<Entry>& Entry::getInstance() {
    static std::unique_ptr<Entry> instance;
    return instance;
}

bool Entry::load() {
    auto& config = Config::getInstance();
    config->loadConfig();
    config->saveConfig();

    EconomicSystem::getInstance();
    HomeSystem::getInstance();
    return true;
}

bool Entry::enable() {
    auto version = getSelf().getManifest().version.value_or(ll::data::Version(0, 0, 0));

    I18nAPI::loadLanguagesFromDirectory(getSelf().getLangDir());

    GMLIB::Files::ResourceLanguage
        language(getSelf().getLangDir(), "Tellurium", version.major, version.minor, version.patch);
    for (auto& name : GMLIB::Files::FileUtils::getAllFileFullNameInDirectory(getSelf().getLangDir())) {
        if (!name.ends_with(".lang")) continue;
        auto content = ll::file_utils::readFile(getSelf().getLangDir() / name);
        if (!content.has_value() || content->empty()) continue;
        language.addLanguage(ll::string_utils::replaceAll(name, ".lang", ""), *content);
    }

    printWelcomeMsg();
    return true;
}

bool Entry::disable() {
    Config::getInstance().reset();
    LoggerManage::getInstance().reset();
    return true;
}

bool Entry::unload() { return true; }

ll::mod::Mod& getSelfMod() { return Entry::getInstance()->getSelf(); }
} // namespace Tellurium

LL_REGISTER_MOD(Tellurium::Entry, Tellurium::Entry::getInstance());