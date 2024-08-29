#include "Entry.h"
#include "Config/Config.h"
#include "Global.h"
#include "Modules/Modules.h"
#include "Utils/I18n/I18n.h"
#include "Versions.h"

#include <ll/api/Versions.h>
#include <ll/api/mod/RegisterHelper.h>
#include <memory>

ll::Logger logger("Tellurium");

void RegTPRCmd();

namespace Tellurium {

void printWelcomeMsg() {
    auto lock = logger.lock();
    logger.info("");
    logger.info(R"(   _______     _  _               _                       )");
    logger.info(R"(  |__   __|   | || |             (_)                      )");
    logger.info(R"(     | |  ___ | || | _   _  _ __  _  _   _  _ __ ___      )");
    logger.info(R"(     | | / _ \| || || | | || '__|| || | | || '_ ` _ \     )");
    logger.info(R"(     | ||  __/| || || |_| || |   | || |_| || | | | | |    )");
    logger.info(R"(     |_| \___||_||_| \__,_||_|   |_| \__,_||_| |_| |_|    )");
    logger.info("");
    logger.info("Tellurium is a free mod under GPL Version 3 License.");
    logger.info("Help us improve Tellurium! -> https://github.com/TelluriumDev/Tellurium");
    logger.info("Copyright (C) 2024 TelluriumDev");
}

static std::unique_ptr<Entry> instance;

Entry& Entry::getInstance() { return *instance; }

bool Entry::load() {
    TSConfig::initConfig(getSelf());
    I18n::initI18n(getSelf());
    printWelcomeMsg();
    if (TARGET_BDS_PROTOCOL_VERSION != ll::getNetworkProtocolVersion()) {
        logger.warn("You are running on an unsupport protocol version! This may result in crash!"_tr());
        logger.warn("Support protocol {0}, current protocol {1}."_tr(
            std::to_string(TARGET_BDS_PROTOCOL_VERSION),
            std::to_string(ll::getNetworkProtocolVersion())
        ));
    }
    // logger.info(I18n::translate("test","zh_CN"));
    // logger.info(I18n::translate("test","en_US"));
    return true;
}

bool Entry::enable() {
    logger.info("Tellurium Enabled!");
    logger.info("Repository: {0}"_tr("https://github.com/TelluriumDev/Tellurium"));
    TSModule::initModules();
    RegTPRCmd();
    return true;
}

bool Entry::disable() { return true; }

bool Entry::unload() { return true; }

} // namespace Tellurium

LL_REGISTER_MOD(Tellurium::Entry, Tellurium::instance);
