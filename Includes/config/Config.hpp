#pragma once

#include <string>

namespace TSEssential::Config {
struct BaseEnable {
    // 开关
	bool Enable;
};
struct AutoUpdateConfig : BaseEnable {
    // 自动重载
    bool AutoReload;
};
struct SelectFormConfig : BaseEnable {
    // 分页数量
    int Subsection;
};
struct Language {
    // 默认语言包
    std::string Default;
    // 切换语言命令(此项可能与其他语言切换冲突)
    std::string Cmd;
};
struct TPAConfig : BaseEnable {
    // 过期时间(s)
    int ExpirationTime;
    // 消耗经济
    int Consume;
};
struct WarpConfig : BaseEnable {};



class PluginConfig {
public:
    static PluginConfig &GetInstance();

public:
    PluginConfig();

    AutoUpdateConfig AutoUpdate;
    SelectFormConfig SelectFormConfig;
};
} // namespace TSEssential::Config