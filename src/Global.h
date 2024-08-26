#pragma once

#include <ll/api/Logger.h>

extern ll::Logger logger;

void printWelcomeMsg() {

    logger.info(R"(     ___________ ______                     __  _       __     )");
    logger.info(R"(    /_  __/ ___// ____/____________  ____  / /_(_)___ _/ /     )");
    logger.info(R"(     / /  \__ \/ __/ / ___/ ___/ _ \/ __ \/ __/ / __ `/ /      )");
    logger.info(R"(    / /  ___/ / /___(__  |  )  __/ / / / /_/ / /_/ / / /       )");
    logger.info(R"(   /_/  /____/_____/____/____/\___/_/ /_/\__/_/\__,_/_/        )");
    logger.info(R"(   ------------------------------------------------------      )");
    logger.info(R"(           Light-Weight Mod Loader for your needs              )");
    logger.info(R"(   ------------------------------------------------------      )");

    logger.info("TSEssential is a free software licensed under {}", "LGPLv3");
}