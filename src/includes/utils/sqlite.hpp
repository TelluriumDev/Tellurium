// 答应群里的要求,LL3 TMET使用数据库来储存数据
#pragma once
#include "sqlite3.h"
#include <map>
#include <string>
#include <vector>

using ResultMap = std::vector<std::map<std::string, std::string>>;

struct SQLite {
public:
    static SQLite* Get(std::string& nameLike);
    ~SQLite();
    SQLite(sqlite3* db) : db(db) {}
    inline std::string GetName();
    void               Open();
    void               Close();
    bool               ExecSQLCommand(std::string const& updateSql);
    bool               CreateTable(const std::string& tableName, const std::string& columns);
    bool               Insert(const std::string& tableName, const std::string& values);
    bool      Update(const std::string& tableName, const std::string& setColumns, const std::string& conditions);
    bool      Delete(const std::string& tableName, const std::string& conditions);
    ResultMap Query(std::string const& querySql);

private:
    std::string db_name;
    sqlite3*    db;
    bool        is_closed{true};
};