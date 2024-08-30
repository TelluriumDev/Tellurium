#include "Utils/SQLite/SQLite.h"
#include "Global.h"
#include "Utils/I18n/I18n.h"

SQLite::SQLite(std::string const& db_name_) : db_name(db_name_) {}

void SQLite::Open() {
    int rc = sqlite3_open(db_name.data(), &db);
    if (rc) {
        logger.error("Can't open database: {0}"_tr(sqlite3_errmsg(db)));
    } else {
        is_closed = false;
        logger.info("Opened database successfully"_tr());
    }
}

void SQLite::Close() {
    logger.info("Closing database..."_tr());
    sqlite3_close(db);
    is_closed = true;
}

bool SQLite::ExecSQLCommand(std::string const& updateSql) {
    char* zErrMsg = 0;
    int   rc      = sqlite3_exec(db, updateSql.data(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        logger.error("SQL error: {0}"_tr(zErrMsg));
        sqlite3_free(zErrMsg);
        return false;
    } else {
        logger.info("Operation done successfully"_tr());
        return true;
    }
}

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
        logger.error("SQL error: {0}"_tr(zErrMsg));
        sqlite3_free(zErrMsg);
    } else {
        logger.info("Operation done successfully"_tr());
    }
    return results;
}

// 添加增删改查的操作函数

bool SQLite::Insert(std::string const& table, std::map<std::string, std::string> const& values) {
    std::string columns;
    std::string values_str;
    for (auto const& [key, value] : values) {
        columns    += key + ",";
        values_str += "'" + value + "',";
    }
    columns.pop_back();
    values_str.pop_back();

    std::string sql = "INSERT INTO " + table + " (" + columns + ") VALUES (" + values_str + ")";
    return ExecSQLCommand(sql);
}

bool SQLite::Update(
    std::string const&                        table,
    std::string const&                        where,
    std::map<std::string, std::string> const& values
) {
    std::string update_str;
    for (auto const& [key, value] : values) {
        update_str += key + " = '" + value + "',";
    }
    update_str.pop_back();

    std::string sql = "UPDATE " + table + " SET " + update_str + " WHERE " + where;
    return ExecSQLCommand(sql);
}

bool SQLite::Delete(std::string const& table, std::string const& where) {
    std::string sql = "DELETE FROM " + table + " WHERE " + where;
    return ExecSQLCommand(sql);
}

ResultMap SQLite::Select(std::string const& table, std::string const& columns, std::string const& where) {
    std::string sql = "SELECT " + columns + " FROM " + table + " WHERE " + where;
    return Query(sql);
}

bool SQLite::isClosed() {
    return is_closed;
}

SQLite::~SQLite() {
    if (!is_closed) {
        logger.info("Closing database..."_tr());
        sqlite3_close(db);
    }
}