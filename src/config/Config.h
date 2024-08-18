#pragma once

namespace TSEssential::Config {
// struct TPAConfig {

// }
class Config {
public:
  Config *GetInstance();
  Config();
  void _Init();
};
} // namespace TSEssential::Config