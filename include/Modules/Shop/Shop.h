#pragma once
#include <string>
#include <vector>

#include <unordered_map>

enum ShopType { item, group };
struct ShopData {
    // 名称
    std::string name;
    // 数据类型 item -> ShopItem, group -> ShopGroup
    // 请自行转换
    ShopType type;
};
struct ShopItem : ShopData {
    // 物品备注
    std::string remake;
    // 一次购买的物品数量
    int count;
    // 物品价格
    int price;
};
struct ShopGroup : ShopData {
    // 物品列表
    // 显示名称/物品类
    std::vector<std::pair<std::string, ShopItem>> items;
    // plugins/Tellurium/config/shop/{0} paths
    // 另一些文件paths
    // 显示名称/文件path
    std::vector<std::pair<std::string, std::string>> shopData;
};

namespace TSModules {

class Shop {
public:
    Shop();
    ~Shop();

    ::ShopData* getShopData(const std::string& shopName);

private:
    std::unordered_map<std::string, ::ShopData*> ShopCache;
};
} // namespace TSModules