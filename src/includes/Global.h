#pragma once

#include "Config.h"
#include "Entry.h"

#include "utils/I18n.h"
#include <ll/api/Logger.h>
#include <ll/api/i18n/I18n.h>
#include <ll/api/mod/NativeMod.h>
#include <ll/api/utils/ErrorUtils.h>

#define TARGET_NETWORK_VERSION 686 // BDS 1.21.3.01

using namespace ll::i18n_literals;

static ll::Logger& logger = *new ll::Logger("TSEssential");

const static auto ModRootDir = ll::mod::getModsRoot();
const static auto ModDir     = ModRootDir / "TSEssential";
const static auto ConfigDir  = ModDir / "config";
const static auto ConfigPath = ConfigDir / "config.json";
const static auto DataDir    = ModDir / "data";
const static auto LangDir    = ModDir / "lang";

extern TSEssential::Config config;