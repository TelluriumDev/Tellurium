#pragma once

#include <sqlite3.h>
#include <map>
#include <string>
#include <vector>

using ResultMap = std::vector<std::map<std::string, std::string>>;

struct SQLite {
public:
    SQLite(std::string const& db_name_);
    ~SQLite();
    void      Open();
    void      Close();
    bool      ExecSQLCommand(std::string const& updateSql);
    ResultMap Query(std::string const& querySql);
    ResultMap Select(std::string const& table, std::string const& columns, std::string const& where);
    bool      Insert(std::string const& table, std::map<std::string, std::string> const& values);
    bool Update(std::string const& table, std::string const& where, std::map<std::string, std::string> const& values);
    bool Delete(std::string const& table, std::string const& where);
    bool      isClosed();

    std::string db_name;
private:
    sqlite3*    db;
    bool        is_closed{true};
};