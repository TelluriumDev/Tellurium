#pragma once

#include <string>
namespace TSEssential::Config {
struct BaseEnable {
  bool Enable;
};
struct AutoUpdateConfig : BaseEnable {
  bool AutoReload;
};
struct SelectFormConfig : BaseEnable {
  int Subsection = 10;
};
struct Language {
  std::string Default = "zh_CN";
};
struct TPAConfig : BaseEnable {};
class Config {
public:
  static Config &GetInstance();
  Config() {
    AutoUpdate.Enable = true;
    AutoUpdate.AutoReload = true;
  };

  AutoUpdateConfig AutoUpdate;
};
} // namespace TSEssential::Config