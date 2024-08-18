#pragma once

#include "config/Config.h"
#include "Entry.h"

#include <ll/api/Logger.h>
#include <ll/api/data/Version.h>

#include <map>

#define TARGET_NETWORK_VERSION 686 // BDS 1.21.3.01

#define CURRENT_CONFIG_VERSION 1
#define logger  ll::Logger("Myelsyse")

static TMEssential::Config config;

static std::unordered_map<std::string, std::string> TPATemp;



void LoadModules(); //