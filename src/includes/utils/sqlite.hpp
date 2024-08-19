// 答应群里的要求,LL3 TMET使用数据库来储存数据

#include <sqlite3.h>

class SQlite {
public:
    void CloseAllDB();
    SQlite();

private:
    sqlite3* db;
};