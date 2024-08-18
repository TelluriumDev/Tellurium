#include "./../utils/stringTool.hpp"

std::vector<std::string>& str_split(const std::string& str, const std::string& delim, std::vector<std::string>& res) {
    if (str == "") return res;
    std::string strs = str + delim;
    size_t      pos  = strs.find(delim);
    while (pos != strs.npos) {
        std::string temp = strs.substr(0, pos);
        res.push_back(temp);
        strs = strs.substr(pos + 1, strs.size());
        pos  = strs.find(delim);
    }
    return res;
}

std::string& str_join(std::vector<std::string>& val, const std::string& cent, std::string& input) {
    for (auto v : val) {
        if (input == "") {
            input += v;
            continue;
        }
        input += cent + v;
    }
    return input;
}

std::string& str_replace_all(std::string& str, const std::string& old_value, const std::string& new_value) {
    for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length()) {
        if ((pos = str.find(old_value, pos)) != std::string::npos) str.replace(pos, old_value.length(), new_value);
        else break;
    }
    return str;
}