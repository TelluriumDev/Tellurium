#pragma once
#include "Global.h"
#include <ll/api/Config.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace TSEssential {
void LoadConfig();
enum MoneyType { score, llmoney };
struct Config {
    bool        Enabled = true;
    int         version = 1;
    std::string Language;
    bool        AutoUpdate;
    struct {
        struct TPA {
            bool Enabled        = true;
            int  ExpirationTime = 60;
            int  ConsumeMoney   = 0;
        } TPA{};
        struct WARP {
            bool Enabled      = true;
            int  ConsumeMoney = 0;
        } WARP{};
        struct Back {
            bool Enabled        = true;
            int  MaxSave        = 5;
            bool SaveToFile     = true;
            int  InvincibleTime = 10;
            int  ConsumeMoney   = 0;
        } Back{};
        struct Home {
            bool Enabled             = true;
            int  MaxHome             = 5;
            int  SaveRequiredMoney   = 0;
            int  GoHomeRequiredMoney = 0;
            int  DelHomeBackOffMoney = 0;
        } Home{};
        struct Money {
            bool        Enabled            = true;
            MoneyType   MoneyType          = score;
            std::string MoneyName          = "score";
            bool        MoneyChangeMsg     = true;
            double      PayTaxRate         = 0.1;
            int         HistoryLength      = 10;
            uint32_t    MaxRankingQuantity = 10;
            uint32_t    PlayerInitialMoney = 0;
        } Money{};
        struct Notice {
            bool Enabled          = true;
            bool OpenOnPlayerJoin = true;
        } Notice{};
        struct Shop {
            bool Enabled = true;
        } Shop{};
        struct DynamicMotd {
            bool                     Enabled  = true;
            int                      Time     = 10;
            std::vector<std::string> MotdList = {"test1", "test2", "test3"};
        } DynamicMotd{};
        struct TPR {
            bool Enabled      = true;
            int  MaxPosRange  = 100;
            int  MinPosRange  = 10;
            int  ConsumeMoney = 0;
        } TPR{};
        struct RefreshChunk {
            bool Enabled      = true;
            int  ConsumeMoney = 0;
        } RefreshChunk{};
        struct FarmLandProtect {
            bool Enabled = true;
            int  Type    = 1;
        } FarmLandProtect{};
    } modules{};
};
} // namespace TSEssential