// Private Headers
#include "TSEssential.h"
#include "Global.h"

// LLAPI Headers
#include <ll/api/Config.h>
#include <ll/api/Versions.h>

namespace TSEssential {

/**
 * @brief 检查网络协议版本
 */

void CheckProtocolVersion() {
  auto NetworkVersion = ll::getNetworkProtocolVersion();
  if (NetworkVersion != TARGET_NETWORK_VERSION) {
    logger.warn("Unsupported Network Version: " +
                std::to_string(NetworkVersion));
    logger.warn("The mod probably won't work correctly");
    logger.warn("Target Network Version: " +
                std::to_string(TARGET_NETWORK_VERSION));
  }
}
/**
 * @brief 加载配置文件
 * @return 成功加载配置文件返回true，否则返回false
 */

bool LoadConfig() {
  auto path = ll::mod::getModsRoot() / "Muelsyse/config/config.json";
  try {
    if (!ll::config::loadConfig(config, path)) {
      logger.debug("config.json not found, will create new one");
      ll::config::saveConfig(config, path);
    } else if (config.version < CURRENT_CONFIG_VERSION) {
      logger.debug("outdated config.json, will update it");
      // ToDo: Update config
      // ToDo: 1 -> 2, 2 -> 3, 3 -> 4, etc...
    }
  } catch (...) {
    // ?
    ll::config::saveConfig(config, path);
  }
  return true;
}
} // namespace TSEssential
