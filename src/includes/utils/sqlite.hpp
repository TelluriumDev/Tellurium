// 答应群里的要求,LL3 TMET使用数据库来储存数据

#include <string>
#include <map>
#include <vector>
#include "sqlite3.h"

using ResultMap = std::vector<std::map<std::string, std::string>>;

struct SQLite {
public:
    SQLite(std::string const& db_name_);
    ~SQLite();
    SQLite(sqlite3* db) : db(db) {}
    SQLite* Get(std::string& name);
    void Open();
    void Close();
    bool ExecSQLCommand(std::string const& updateSql);
    bool CreateTable(const std::string& tableName, const std::string& columns);
    bool Insert(const std::string& tableName, const std::string& values);
    bool Update(const std::string& tableName, const std::string& setColumns, const std::string& conditions);
    bool Delete(const std::string& tableName, const std::string& conditions);

    ResultMap Query(std::string const& querySql);
private:
    std::string db_name;
    sqlite3 *db;
    bool is_closed {true};
};