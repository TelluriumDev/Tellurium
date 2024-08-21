// 答应群里的要求,LL3 TMET使用数据库来储存数据
#pragma once
#include <string>
#include <map>
#include <vector>
#include "sqlite3.h"

using ResultMap = std::vector<std::map<std::string, std::string>>;

// 定义SQLite结构体
struct SQLite {
public:
    // 获取SQLite实例
    static SQLite* Get(std::string& nameLike);

    // 构造函数
    SQLite(std::string const& db_name_);
    // 析构函数
    ~SQLite();
    // 构造函数初始化sqlite3指针
    SQLite(sqlite3* db) : db(db) {}
    inline std::string GetName();
    // 打开数据库
    void Open();
    // 关闭数据库
    void Close();
    // 执行SQL命令
    bool ExecSQLCommand(std::string const& updateSql);
    // 创建表
    bool CreateTable(const std::string& tableName, const std::string& columns);
    // 插入数据
    bool Insert(const std::string& tableName, const std::string& values);
    // 更新数据
    bool Update(const std::string& tableName, const std::string& setColumns, const std::string& conditions);
    // 删除数据
    bool Delete(const std::string& tableName, const std::string& conditions);

    // 查询数据
    ResultMap Query(std::string const& querySql);
private:
    // 数据库名称
    std::string db_name;
    // sqlite3指针
    sqlite3 *db;
    // 是否关闭数据库
    bool is_closed {true};
};