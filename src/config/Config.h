#pragma once

namespace TSEssential {
struct Config {
  int version = 1;     // 配置文件版本
  bool enabled = true; // 插件是否启用
  struct {
    struct {
      bool enabled = true;       // 是否启用
      int ExpireTime = 60;       // TPA过期时间
      bool allowTPASelf = false; // 是否允许TPA自己
    } TPA{};

  } Modules{};
};
} // namespace TSEssential