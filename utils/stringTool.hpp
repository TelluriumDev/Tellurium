#pragma once

#include <string>
#include <vector>

std::vector<std::string>& str_split(const std::string& str, const std::string& delim, std::vector<std::string>& res);

std::string& str_join(std::vector<std::string>& val, const std::string& cent, std::string& input);

std::string& str_replace_all(std::string& str, const std::string& old_value, const std::string& new_value);