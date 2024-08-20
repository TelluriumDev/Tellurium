// 答应群里的要求,LL3 TMET使用数据库来储存数据

#include <sqlite3.h>
#include <string>

class SQLite {
public:
    // maybe nullptr
    static SQLite* Get(std::string& name);
    static void    CloseAllDB();
    SQLite(std::string filename);
    ~SQLite();

    void Close();

private:
    std::string name;
    sqlite3* db;
};