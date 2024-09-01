#include "Utils/PlayerData/PlayerData.h"
#include "Config/Config.h"
#include "Utils/SQLite/SQLite.h"

#include <filesystem>
#include <memory>


namespace TLUtils::PlayerData {

std::unique_ptr<SQLite> playerData = nullptr;

void initPlayerData() {
        auto path = TLConfig::getDataDir() / "playerData.db";
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path.parent_path());
            playerData = std::make_unique<SQLite>(path.string() );
            playerData->Open();
            playerData->ExecSQLCommand(
                "CREATE TABLE IF NOT EXISTS lang (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, value TEXT);"
            );
        } // ai 
    }
    void createPlayerData(std::string name){
        playerData->Open();
        playerData->ExecSQLCommand("INSERT INTO lang (name, value) VALUES ('" + name + "', 'zh_CN');");
    }

}