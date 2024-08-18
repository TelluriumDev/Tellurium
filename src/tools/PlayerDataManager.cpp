#include "PlayerDataManager.h"
#include <mutex>

namespace Muelsyse {
    namespace Tools {
        typedef std::map<std::string, std::string> UuidMap;
        std::mutex uuid_map_mutex;
        std::unique_ptr<UuidMap> createMap(const std::string& uuid)
        {
            std::unique_ptr<UuidMap> uuid_map(new UuidMap);
            uuid_map->insert({uuid, ""});
            return uuid_map;
        }

        void addToMap(std::unique_ptr<UuidMap> uuid_map, const std::string& key, const std::string& value)
        {
            std::lock_guard<std::mutex> lock(uuid_map_mutex);
            uuid_map->insert({key, value});
        }

        std::string getFromMap(const std::unique_ptr<UuidMap> uuid_map, const std::string& key)
        {
            std::lock_guard<std::mutex> lock(uuid_map_mutex);
            return uuid_map->at(key);
        }

        void deleteFromMap(std::unique_ptr<UuidMap> uuid_map, const std::string& key)
        {
            std::lock_guard<std::mutex> lock(uuid_map_mutex);
            uuid_map->erase(key);
        }

        void deleteMap(std::unique_ptr<UuidMap> uuid_map)
        {
            std::lock_guard<std::mutex> lock(uuid_map_mutex);
            uuid_map.reset();
        }
    }
}
