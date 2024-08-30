#include "Utils/PlayerData/PlayerData.h"
#include "Config/Config.h"
#include <filesystem>


namespace TLUtils::PlayerData {

    SQLite* db = new SQLite("");

    void initPlayerData(){
        auto path = TLConfig::getDataDir() / "playerdata.db";
        if(!std::filesystem::exists(path)){
            db->db_name = path.string();
            db->Open();
            db->ExecSQLCommand(
                "CREATE TABLE IF NOT EXISTS lang (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, value TEXT);"
            );
        } // ai 
    }
    void createPlayerData(std::string name){
        db->Open();
        db->ExecSQLCommand("INSERT INTO lang (name, value) VALUES ('" + name + "', 'zh_CN');");
    }

    SQLite* getPlayerDataInstance() {
        db->Open();
        return db;
    }

    void destroyPlayerDataInstance() { 
        db->Close();
        delete db;
        db = nullptr;
    }
}