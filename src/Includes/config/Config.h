#pragma once

namespace TSEssential::Config {
struct EnableFAT {
	bool Enable;
};
struct AutoUpdateConfig : EnableFAT {
	bool AutoReload;
};
struct TPAConfig : EnableFAT {
	
};
class Config {
public:
    Config &GetInstance();
    Config();
    void _Init();
};
} // namespace TSEssential::Config