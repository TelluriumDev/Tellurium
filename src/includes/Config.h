#pragma once
#include "ConfigType.h"

namespace TSEssential::Config {
class PluginConfig {
public:
    PluginConfig();

    AutoUpdateConfig      AutoUpdate;
    SelectFormConfig      SelectForm;
    LanguageConfig        Language;
    TeleportAskerConfig   TPA;
    WarpConfig            Warp;
    BackConfig            Back;
    HomeConfig            Home;
    EconomyConfig         Economy;
    NoticeConfig          Notice;
    ShopConfig            Shop;
    DynamicMotdConfig     DynamicMotd;
    RandomTeleportConfig  TPR;
    RefreshChunkConfig    RefreshChunk;
    FarmLandProtectConfig FarmLandProtect;

    static PluginConfig* GetInstance();
};
} // namespace TSEssential::Config