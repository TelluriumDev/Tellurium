#pragma once

#include "Entry.h"
#include "Config.h"

#include <ll/api/Logger.h>
#include <ll/api/mod/NativeMod.h>


#define TARGET_NETWORK_VERSION 686 // BDS 1.21.3.01

static ll::Logger &logger = *new ll::Logger("TSEssential");

static auto ModRootDir = ll::mod::getModsRoot(); // Get the root directory of the mods
static auto ModDir = ModRootDir / "TSEssential"; // Get the dir of this mod
static auto ConfigDir = ModDir / "config"; // Get the config dir of this mod
static auto DataDir = ModDir / "data";     // Get the data dir of this mod
static auto LangDir = ModDir / "lang";     // Get the lang dir of this mod

#define CONFIG_VERSION 1


extern TSEssential::Config config;