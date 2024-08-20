#include "utils/sqlite.hpp"
#include "TSEssential.h"
#include <map>
#include <string>

static std::map<std::string, SQLite*> DBList{};

SQLite* SQLite::Get(std::string& name) { return DBList[name]; }
void SQLite::CloseAllDB() {
    
}

SQLite::SQLite(std::string filename) {
    auto path = SELF.getDataDir() / filename;
    LOGGER.debug("Create SQLite3 Data {0}", path.string());
}

void SQLite::Close() {
    sqlite3_close(db);
    DBList.erase(name);
}