#pragma once


#include <nlohmann/json.hpp>

#include <filesystem>
#include <memory>
#include <string>

using json = nlohmann::json;

namespace TLUtil {

class JsonHandler {
public:
    JsonHandler(const std::filesystem::path& path);

private:
    std::unique_ptr<json> mJson;

    std::filesystem::path mPath;

    void update();

public:
    template <typename T>
    T get(const std::string& key);
    template <typename T>
    void           set(const std::string& key, const T& value);
    void           del(const std::string& key);
    void           reload();
    void           clear();
    void           write(json& json);
    json::iterator begin();
    json::iterator end();
};
} // namespace TLUtil