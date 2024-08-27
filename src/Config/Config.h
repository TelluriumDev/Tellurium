#pragma once

#include <filesystem>
#include <ll/api/base/StdInt.h>
#include <ll/api/mod/NativeMod.h>
#include <string>
#include <unordered_map>

namespace TSConfig {
enum BanExplosionMode {
    None,           // 无视
    NoDestoryBlock, // 禁止破坏方块
    NoExplosion,    // 禁止爆炸
};
struct Config {
    // 配置文件版本
    int version = 1;
    // 是否启用此模组，禁用后插件会自动卸载
    bool Enabled = true;
    // 插件在控制台使用的语言
    std::string Language = "zh_CN";
    // 模块设置
    struct {
        // 互传模块设置
        struct {
            // 是否启用
            bool Enabled = true;
            // TPA请求过期时间(单位:秒)
            uint ExpirationTime = 60;
            // 成功使用后的冷却时间(单位:秒)
            uint Cooling = 0;
            // 完成传送后消耗的经济
            uint ConsumeMoney = 0;
        } TPA;
        // 公共传送点模块设置
        struct {
            // 是否启用功能
            bool Enabled = true;
            // 传送到公共传送点所消耗的经济
            uint ConsumeMoney = 0;
        } WARP;
        // 返回死亡点模块设置
        struct {
            // 是否启用
            bool Enabled = true;
            // 是否启用持久化保存(写入数据文件)
            bool SaveToDB = true;
            // 最大保存的数据数量，当SaveToDB为false时，将会储存在缓存中
            uint SaveCount = 5;
            // 传送到目标点后的无敌时间
            uint InvincibleTime = 5;
            // 在玩家重生后显示上一次死亡的信息
            bool ShowDeathMsg = true;
            // 返回死亡位置时消耗的经济
            uint ConsumeMoney = 0;
        } Back;
        // 家园模块设置
        struct {
            // 是否启用
            bool Enabled = true;
            // 允许的最大传送点数量
            uint MaxHome = 5;
            // 保存传送点消耗的经济
            uint SaveRequiredMoney = 0;
            // 前往传送点消耗的经济
            uint GoHomeRequiredMoney = 0;
            // 删除传送点返还的经济
            uint DelHomeBackOffMoney = 0;
        } Home;
        // 经济模块设置
        struct {
            // 是否启用
            bool Enabled = true;
            // 将使用的计分板名称，留空则启用LLMoney模式
            std::string ScoreName = "";
            // 经济名称
            std::string MoneyName = "金币";
            // 是否显示余额变动信息
            bool MoneyChangeMsg = true;
            // 玩家转账时的手续费，为直接乘算
            double PayTaxRate = 0.1;
            // 最大保存的交易历史记录条数
            uint HistoryLength = 10;
            // 允许的最大排行榜显示条数
            uint MaxRankingQuantity = 10;
            // 玩家初始金币
            uint PlayerInitialMoney = 0;
        } Money;
        // 公告模块设置
        struct {
            // 是否启用
            bool Enabled = true;
            // 是否在未确认玩家加入时自动打开
            bool OpenOnPlayerJoin = true;
        } Notice;
        // 商店模块设置
        struct {
            // 是否启用
            bool Enabled = true;
        } Shop;
        // 动态Motd设置
        struct {
            // 是否启用
            bool Enabled = true;
            // 刷新间隔(单位:秒)
            uint Time = 10;
            // 动态Motd列表
            std::vector<std::string> MotdList = {
                "§d欢迎§e来到§6***§a服务器§g！",
                "§b当前服务器人数§6:§d%server_online%/%server_max_players%",
                "§d喵喵喵~"
            };
        } DynamicMotd;
        // 随机传送模块设置
        struct {
            // 是否启用
            bool Enabled = true;
            // 计算随机传送的范围时使用的最大值
            uint MaxPosRange = 100;
            // 计算随机传送的范围时使用的最小值
            uint MinPosRange = 10;
            // 成功使用后u的冷却时间
            uint Cooling = 0;
            // 成功使用后所消耗的经济的消耗经济
            uint ConsumeMoney = 0;
        } TPR;
        // 刷新模块设置
        struct {
            // 是否启用
            bool Enabled = true;
            // 使用所消耗经济
            uint ConsumeMoney = 0;
        } Refresh;
        // 耕地防破坏设置
        struct {
            // 是否启用
            bool Enabled = true;
            // 防护类型
            enum { all, none, notPlayer, player } Type = all;
        } FarmLandProtect;
        // 自动钓鱼模块设置
        struct {
            // 是否启用
            bool Enabled = true;
        } AutoFishing;
        // 防爆模块设置
        struct {
            // 是否启用
            bool Enabled = true;
            // 防爆设置
            std::unordered_map<std::string, BanExplosionMode> setting = {
                {"minecraft:tnt",                    BanExplosionMode::NoDestoryBlock}, // TNT
                {"minecraft:respawn_anchor",         BanExplosionMode::NoExplosion   }, // 重生锚
                {"minecraft:creeper",                BanExplosionMode::NoDestoryBlock}, // 苦力怕
                {"minecraft:end_crystal",            BanExplosionMode::NoDestoryBlock}, // 末地水晶
                {"minecraft:dragon_fireball",        BanExplosionMode::NoDestoryBlock}, // 龙火球
                {"minecraft:fireball",               BanExplosionMode::NoDestoryBlock}, // 火球
                {"minecraft:wither_skull",           BanExplosionMode::NoDestoryBlock}, // 凋零之首
                {"minecraft:tnt_minecart",           BanExplosionMode::NoDestoryBlock}, // TNT矿车
                {"minecraft:bed",                    BanExplosionMode::NoDestoryBlock}, // 床
                {"minecraft:wither_skull",           BanExplosionMode::NoDestoryBlock}, // 凋零之首
                {"minecraft:wither_skull_dangerous", BanExplosionMode::NoDestoryBlock}, // 蓝色凋零之首
                {"minecraft:wither",                 BanExplosionMode::NoExplosion   }, // 凋零
            };
        } BanExplosion;
        // 禁言模块设置
        struct {
            // 是否启用
            bool Enabled = true;
        } Mute;
    } Modules;
};

void loadConfig(const std::filesystem::path& path);

void saveConfig(const std::filesystem::path& path);

void initConfig(ll::mod::NativeMod& self);

} // namespace TSConfig

// 全局配置文件
extern TSConfig::Config config;
