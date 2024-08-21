#include "utils/sqlite.hpp"

#include "TSEssential.h"

#include <string>
#include <vector>

static std::vector<SQLite*> AllSQLites;

/**
//  * @brief SQLite类的构造函数
//  * @param db_name_ 数据库名称
//  */ 
// SQLite::SQLite(std::string const& db_name_) : db_name(db_name_) {}

/**
 * @brief SQLite类的Get函数
 */
SQLite* Get(std::string& nameLike) {
    for (auto sqlite : AllSQLites) {
        auto sql_name = sqlite->GetName();
        if (sql_name.starts_with(nameLike)) {
            return sqlite;
        }
    }
    return nullptr;
}

inline std::string SQLite::GetName() { return db_name; }

/**
 * @brief 打开数据库
 */
void SQLite::Open() {
    int rc;
    /* Open database */
    rc = sqlite3_open(db_name.data(), &db);
    if (rc) {
        LOGGER.debug("Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        is_closed = false;
        LOGGER.debug("Opened database successfully");
    }
}

/**
 * @brief 关闭数据库
 */
void SQLite::Close() {
    LOGGER.info("Closing database{0}...", GetName());
    sqlite3_close(db);
    is_closed = true;
}

/**
 * @brief 执行SQL命令
 * @param updateSql SQL命令
 * @return 执行结果
 */
bool SQLite::ExecSQLCommand(std::string const& updateSql) {
    char* zErrMsg = 0;
    int   rc      = sqlite3_exec(db, updateSql.data(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        LOGGER.error("SQLite Error: \n{0}", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    } else {
        LOGGER.debug("Operation done successfully\n");
        return true;
    }
}

/**
 * @brief 创建表
 * @param tableName 表名
 * @param columns 列名和数据类型
 * @return 执行结果
 */
bool SQLite::CreateTable(const std::string& tableName, const std::string& columns) {
    std::string sql = "CREATE TABLE " + tableName + " (" + columns + ")";
    return ExecSQLCommand(sql);
}

/**
 * @brief 插入数据
 * @param tableName 表名
 * @param values 数据值
 * @return 执行结果
 */
bool SQLite::Insert(const std::string& tableName, const std::string& values) {
    std::string sql = "INSERT INTO " + tableName + " (" + values + ")";
    return ExecSQLCommand(sql);
}

/**
 * @brief 更新数据
 * @param tableName 表名
 * @param setColumns 要更新的列名和数据值
 * @param conditions 更新条件
 * @return 执行结果
 */
bool SQLite::Update(const std::string& tableName, const std::string& setColumns, const std::string& conditions) {
    std::string sql = "UPDATE " + tableName + " SET " + setColumns + " WHERE " + conditions;
    return ExecSQLCommand(sql);
}

/**
 * @brief 删除数据
 * @param tableName 表名
 * @param conditions 删除条件
 * @return 执行结果
 */
bool SQLite::Delete(const std::string& tableName, const std::string& conditions) {
    std::string sql = "DELETE FROM " + tableName + " WHERE " + conditions;
    return ExecSQLCommand(sql);
}

/**
 * @brief 查询数据
 * @param querySql 查询SQL语句
 * @return 查询结果
 */
ResultMap SQLite::Query(std::string const& querySql) {
    ResultMap results;
    char*     zErrMsg = 0;
    /* Execute SQL statement */
    int rc = sqlite3_exec(
        db,
        querySql.data(),
        [](void* data, int argc, char** argv, char** azColName) {
            int                                i;
            auto&                              results_ = *((ResultMap*)(data));
            std::map<std::string, std::string> result;
            for (i = 0; i < argc; i++) {
                if (argv[i]) {
                    result[azColName[i]] = argv[i];
                } else {
                    result[azColName[i]] = "NULL";
                }
            }
            results_.emplace_back(std::move(result));
            return 0;
        },
        (void*)&results,
        &zErrMsg
    );

    if (rc != SQLITE_OK) {
        LOGGER.debug("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        LOGGER.debug("Operation done successfully\n");
    }
    return results;
}

/**
 * @brief 析构函数
 */
SQLite::~SQLite() {
    if (!is_closed) {
        LOGGER.debug("Closing database...");
        sqlite3_close(db);
    }
}