#include <string>
#include <map>
#include <memory>
#include <mutex>

namespace Muelsyse {
    namespace Tools {
        typedef std::map<std::string, std::string> UuidMap;

        std::unique_ptr<UuidMap> createMap(const std::string& uuid);

        void addToMap(std::unique_ptr<UuidMap> uuid_map, const std::string& key, const std::string& value);

        std::string getFromMap(const std::unique_ptr<UuidMap> uuid_map, const std::string& key);

        void deleteFromMap(std::unique_ptr<UuidMap> uuid_map, const std::string& key);

        void deleteMap(std::unique_ptr<UuidMap> uuid_map);
    }
}
