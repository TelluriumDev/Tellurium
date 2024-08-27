#include "Entry.h"
#include "Config/Config.h"
#include "Global.h"

#include <memory>

#include "ll/api/Logger.h"
#include "ll/api/mod/RegisterHelper.h"


ll::Logger logger("TSEssential");

namespace TSEssential {

void printWelcomeMsg() {
    logger.info(R"(     ___________ ______                     __  _       __     )");
    logger.info(R"(    /_  __/ ___// ____/____________  ____  / /_(_)___ _/ /     )");
    logger.info(R"(     / /  \__ \/ __/ / ___/ ___/ _ \/ __ \/ __/ / __ `/ /      )");
    logger.info(R"(    / /  ___/ / /___(__  |  )  __/ / / / /_/ / /_/ / / /       )");
    logger.info(R"(   /_/  /____/_____/____/____/\___/_/ /_/\__/_/\__,_/_/        )");
    logger.info(R"(   ------------------------------------------------------      )");
    logger.info(R"(           Light-Weight Mod Loader for your needs              )");
    logger.info(R"(   ------------------------------------------------------      )");
    logger.info(R"(    TSEssential is a free software licensed under {}           )", "LGPLv3");
}

static std::unique_ptr<Entry> instance;

Entry& Entry::getInstance() { return *instance; }

bool Entry::load() {
    printWelcomeMsg();
    TSConfig::initConfig(this->mSelf);
    return true;
}

bool Entry::enable() { return true; }

bool Entry::disable() { return true; }

bool Entry::unload() { return true; }

} // namespace TSEssential

LL_REGISTER_MOD(TSEssential::Entry, TSEssential::instance);
