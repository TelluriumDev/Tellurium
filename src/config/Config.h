#pragma once

<<<<<<< HEAD
namespace TSEssential::Config {
// struct TPAConfig {

// }
class Config {
public:
  Config *GetInstance();
  Config();
  void _Init();
=======
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
>>>>>>> de92f11e1cc3f2ee7c1abc7bb0e065c8204913a1
};
} // namespace TSEssential::Config