
#pragma once
#include "modules/Economy.h"
#include "modules/FarmLandProtect.h"
#include <string>
#include <vector>


namespace TSEssential::Config {
struct BaseEnable {
    // 开关
    bool Enable;
};
struct BaseFuncConfig : BaseEnable {
    // 消耗经济
    int Consume;
};
struct AutoUpdateConfig : BaseEnable {
    // 自动重载
    bool AutoReload;
};
struct SelectFormConfig : BaseEnable {
    // 分页数量
    int Subsection;
};
struct LanguageConfig {
    // 默认语言包
    std::string Default;
    // 切换语言命令(此项可能与其他语言切换冲突)
    std::string Cmd;
};
struct TeleportAskerConfig : BaseFuncConfig {
    // 过期时间(s)
    int ExpirationTime;
};
struct WarpConfig : BaseFuncConfig {};
struct BackConfig : BaseFuncConfig {
    // 最大记录长度
    int MaxSave;
    // 保存到数据库
    bool SaveToDB;
    // 返回后无敌时间
    int InvincibleTime;
    // 是否显示死亡信息
    bool DeathMsg;
};
struct HomeConfig : BaseEnable {
    // 最大家数量
    int MaxHome;
    // 添加家标记所需
    int AddHomeConsume;
    // 去往家标记所需
    int GoHomeConsume;
    // 删除家标记所反
    int DelHomeBackConsume;
};
struct EconomyConfig : BaseEnable {
    Economy::EconomyType EconomyType;
    std::string          EconomyName;
    float                PayTaxRate;
    int                  HistoryLength;
    int                  MaxRankingQuantity;
    bool                 MoneyChangeMsg;
    int                  PlayerInitialMoney;
};
struct NoticeConfig : BaseFuncConfig {
    bool        JoinOpenNotice;
    std::string NoticeTitle;
    std::string NoticeContent;
};
struct ShopConfig : BaseFuncConfig {};
struct DynamicMotdConfig : BaseFuncConfig {
    int                      ChangeTime;
    std::vector<std::string> MotdList;
};
struct Vec2 {
    float x;
    float z;
};
struct RandomTeleportConfig : BaseFuncConfig {
    std::vector<Vec2> Coordinates;
};
struct RefreshChunkConfig : BaseFuncConfig {};
struct FarmLandProtectConfig : BaseFuncConfig {
    FarmLandProtect::ProtectType WorkType;
};
} // namespace TSEssential::Config