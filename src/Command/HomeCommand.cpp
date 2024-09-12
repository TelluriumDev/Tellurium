#include "Command/HomeCommand.h"
#include "Config/Config.h"
#include "Modules/Modules.h"
#include "Utils/I18n.h"
#include "Utils/PlayerData.h"

#include "ll/api/command/CommandHandle.h"
#include "ll/api/command/CommandRegistrar.h"
#include "ll/api/service/PlayerInfo.h"

#include "mc/deps/core/mce/UUID.h"
#include "mc/server/commands/CommandOrigin.h"
#include "mc/server/commands/CommandOutput.h"
#include "mc/server/commands/CommandPermissionLevel.h"
#include "mc/world/actor/Actor.h"
#include "mc/world/actor/player/Player.h"

#include <memory>


namespace TLCommand::HomeCommand {

void RegHomeCommand() {
    auto& cmd = ll::command::CommandRegistrar::getInstance()
                    .getOrCreateCommand("home", "home to a location"_tr(), CommandPermissionLevel::Any);
    cmd.overload<Param>()

        .text("add")
        .required("name")
        .execute([](CommandOrigin const& origin, CommandOutput& output, Param const& param) {
            auto* entity = origin.getEntity();
            if (entity == nullptr || !entity->isType(ActorType::Player)) {
                output.error("Only players can run this command"_tr());
                return;
            }
            auto* player = static_cast<Player*>(entity);
            auto  res    = TLModule::getInstance()->mHome->addHome(*player, param.name);
            if (res) {
                output.success(
                    TLUtil::I18n::translate("command.home.add.success", TLUtil::PlayerData::getPlayerLang(*player))
                );
                TLModule::getInstance()->mMoney->reduceMoney(*player, config.Modules.Home.SaveRequiredMoney, "HomeAdd");
            } else {
                output.error(
                    TLUtil::I18n::translate("command.home.add.error", TLUtil::PlayerData::getPlayerLang(*player))
                );
            }
        });
    cmd.overload<Param>()

        .text("del")
        .required("name")
        .execute([](CommandOrigin const& origin, CommandOutput& output, Param const& param) {
            auto* entity = origin.getEntity();
            if (entity == nullptr || !entity->isType(ActorType::Player)) {
                output.error("Only players can run this command"_tr());
                return;
            }
            auto* player = static_cast<Player*>(entity);
            auto  res    = TLModule::getInstance()->mHome->delHome(*player, param.name);
            if (res) {
                output.success(
                    TLUtil::I18n::translate("command.home.del.success", TLUtil::PlayerData::getPlayerLang(*player))
                );
                TLModule::getInstance()->mMoney->addMoney(*player, config.Modules.Home.DelHomeBackOffMoney, "HomeDel");
            } else {
                output.error(
                    TLUtil::I18n::translate("command.home.del.error", TLUtil::PlayerData::getPlayerLang(*player))
                );
            }
        });
    cmd.overload<Param>()

        .text("go")
        .required("name")
        .execute([](CommandOrigin const& origin, CommandOutput& output, Param const& param) {
            auto* entity = origin.getEntity();
            if (entity == nullptr || !entity->isType(ActorType::Player)) {
                output.error("Only players can run this command"_tr());
                return;
            }
            auto* player = static_cast<Player*>(entity);
            auto  res    = TLModule::getInstance()->mHome->teleportHome(*player, param.name);
            if (res) {
                output.success(
                    TLUtil::I18n::translate("command.home.go.success", TLUtil::PlayerData::getPlayerLang(*player))
                );
                TLModule::getInstance()
                    ->mMoney->reduceMoney(*player, config.Modules.Home.GoHomeRequiredMoney, "HomeGo");
            } else {
                output.error(
                    TLUtil::I18n::translate("command.home.go.error", TLUtil::PlayerData::getPlayerLang(*player))
                );
            }
        });

    cmd.overload()

        .text("myhome")
        .execute([](CommandOrigin const& origin, CommandOutput& output) {
            auto* entity = origin.getEntity();
            if (entity == nullptr || !entity->isType(ActorType::Player)) {
                output.error("Only players can run this command"_tr());
                return;
            }
            auto*       player = static_cast<Player*>(entity);
            auto        res    = TLModule::getInstance()->mHome->listPlayerHome(*player);
            std::string list   = "";
            for (auto const& data_ : res) {
                auto& name = data_.name;
                auto& pos  = data_.position;
                auto  temp =
                    fmt::v10::format("Name: {0},Pos: {1} {2} {3},Dim: {4}\n", name, pos[0], pos[1], pos[2], pos[3]);
                list += temp;
            }
            auto lang = TLUtil::PlayerData::getPlayerLang(*player);
            output.success((TLUtil::I18n::translate("command.home.list.success", lang)) + "\n" + list);
        });


    cmd.overload()

        .text("list")
        .execute([](CommandOrigin const& origin, CommandOutput& output) {
            auto*       entity = origin.getEntity();
            auto        res    = TLModule::getInstance()->mHome->listAllHome();
            std::string list   = "";
            for (auto const& data : res) {
                auto playername  = ll::service::PlayerInfo::getInstance().fromUuid(data.first)->name;
                list            += (playername + ":\n");
                for (auto const& data_ : data.second) {
                    auto& name = data_.name;
                    auto& pos  = data_.position;
                    auto  temp =
                        fmt::v10::format("Name: {0},Pos: {1} {2} {3},Dim: {4}\n", name, pos[0], pos[1], pos[2], pos[3]);
                    list += temp;
                }
            }
            if (entity == nullptr || !entity->isType(ActorType::Player)) {
                output.success(list);
                return;
            }
            auto* player = static_cast<Player*>(entity);
            auto  lang   = TLUtil::PlayerData::getPlayerLang(*player);
            output.success((TLUtil::I18n::translate("command.home.list.success", lang)) + "\n" + list);
        });
};

}; // namespace TLCommand::HomeCommand
