#include "Utils/Data/JsonHandler.h"
#include "Global.h"

#include <fstream>

namespace TLUtils {

JsonHandler::JsonHandler(const std::filesystem::path& path) {
    this->mPath = path;
    if (!std::filesystem::exists(this->mPath.parent_path())) {
        std::filesystem::create_directories(this->mPath.parent_path());
    }
    if (std::filesystem::exists(this->mPath)) {
        std::ifstream file(mPath);
        if (!file.is_open()) {
            logger.error("Failed to open file: {0}"_tr(mPath.string()));
        }
        file >> mJson;
    }
    std::ofstream file(mPath);
    if (!file.is_open()) {
        logger.error("Failed to open file: {0}"_tr(mPath.string()));
    }
    file << mJson.dump(4); // 4 spaces indentation
    file.close();
}

void JsonHandler::update() {
    std::ofstream file(mPath);
    if (!file.is_open()) {
        logger.error("Failed to open file: {0}"_tr(mPath.string()));
    }
    file << mJson.dump(4); // 4 spaces indentation
    file.close();
}

template <typename T>
T JsonHandler::get(const std::string& key) {
    return mJson[key].get<T>();
}

template int JsonHandler::get<int>(const std::string& key);
template bool JsonHandler::get<bool>(const std::string& key);
template std::string JsonHandler::get<std::string>(const std::string& key);
template double      JsonHandler::get<double>(const std::string& key);
template json        JsonHandler::get<json>(const std::string& key);
template std::vector<int> JsonHandler::get<std::vector<int>>(const std::string& key);

template <typename T>
void JsonHandler::set(const std::string& key, const T& value) {
    mJson[key] = value;
    update();
}

template void JsonHandler::set<int>(const std::string& key, const int& value);
template void JsonHandler::set<bool>(const std::string& key, const bool& value);
template void JsonHandler::set<std::string>(const std::string& key, const std::string& value);
template void JsonHandler::set<double>(const std::string& key, const double& value);
template void JsonHandler::set<json>(const std::string& key, const json& value);
template void JsonHandler::set<std::vector<int>>(const std::string& key, const std::vector<int>& value);


void JsonHandler::reload() {
    std::ifstream file(mPath);
    update();
}

void JsonHandler::clear() {
    mJson.clear();
    update();
}

void JsonHandler::write(json& j) {
    mJson = j;
    update();
}

} // namespace TLUtils