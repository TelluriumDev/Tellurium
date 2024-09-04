#pragma once

#include <filesystem>

#include <nlohmann/json.hpp>

#include <string>

using json = nlohmann::json;

namespace TLUtils {

class JsonHandler {
public:
    JsonHandler(const std::filesystem::path& path);

private:
    json mJson;

    std::filesystem::path mPath;

    void update();

public:
    
    template <typename T>
    T get(const std::string& key);

    template <typename T>
    void set(const std::string& key, const T& value);

    
    void reload();
    void clear();
    void write(json& json);
};
} // namespace TLUtils