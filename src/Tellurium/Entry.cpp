#include "Tellurium/Entry.h"
#include "Tellurium/base/Global.h"

#include <ll/api/i18n/I18n.h>
#include <pl/Config.h>
#include <ll/api/mod/RegisterHelper.h>
#include <memory>

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

    ll::i18n::load(getSelf().getLangDir());
    if (ll::i18n::getInstance() == nullptr) {
        getSelf().getLogger().error("Failed to load i18n.");
        return false;
    }

    printWelcomeMsg();
    return true;
}

bool Entry::enable() { return true; }

bool Entry::disable() { return true; }

bool Entry::unload() { return true; }

ll::mod::Mod& getSelfMod() { return Entry::getInstance()->getSelf(); }
} // namespace Tellurium

LL_REGISTER_MOD(Tellurium::Entry, Tellurium::Entry::getInstance());