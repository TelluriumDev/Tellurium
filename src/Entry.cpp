#include "Entry.h"
#include "Config/Config.h"
#include "Global.h"

#include <ll/api/Versions.h>
#include <ll/api/mod/RegisterHelper.h>
#include <memory>

ll::Logger logger("Tellurium");

namespace Tellurium {

void printWelcomeMsg() {
    logger.info(R"(     ___________ ______                     __  _       __     )");
    logger.info(R"(    /_  __/ ___// ____/____________  ____  / /_(_)___ _/ /     )");
    logger.info(R"(     / /  \__ \/ __/ / ___/ ___/ _ \/ __ \/ __/ / __ `/ /      )");
    logger.info(R"(    / /  ___/ / /___(__  |  )  __/ / / / /_/ / /_/ / / /       )");
    logger.info(R"(   /_/  /____/_____/____/____/\___/_/ /_/\__/_/\__,_/_/        )");
    logger.info(R"(   ------------------------------------------------------      )");
    logger.info(R"(           Light-Weight Mod Loader for your needs              )");
    logger.info(R"(   ------------------------------------------------------      )");
    logger.info(R"(    Tellurium is a free mod licensed under {0}               )", "LGPLv3");
}

static std::unique_ptr<Entry> instance;

Entry& Entry::getInstance() { return *instance; }

bool Entry::load() {
    printWelcomeMsg();
    if (TARGET_PROTOCOL != ll::getNetworkProtocolVersion()) {
        logger.warn("You are running on an unsupport protocol version! This may result in crash!");
        logger.warn(
            "Support protocol {0}, current protocol {1}.",
            std::to_string(TARGET_PROTOCOL),
            std::to_string(ll::getNetworkProtocolVersion())
        );
    }
    TSConfig::initConfig(getSelf());
    return true;
}

bool Entry::enable() {
    logger.info("Tellurium Enabled!");
    logger.info("Repository: {0}", "https://github.com/TelluriumDev/Tellurium");
    return true;
}

bool Entry::disable() { return true; }

bool Entry::unload() { return true; }

} // namespace Tellurium

LL_REGISTER_MOD(Tellurium::Entry, Tellurium::instance);
