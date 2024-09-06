#include "Command/WarpCommand/WarpCommand.h"
#include "Modules/Modules.h"
#include "Utils/I18n/I18n.h"
#include "Utils/PlayerData/PlayerData.h"

#include "ll/api/command/CommandHandle.h"
#include "ll/api/command/CommandRegistrar.h"

#include "mc/server/commands/CommandOrigin.h"
#include "mc/server/commands/CommandOutput.h"
#include "mc/server/commands/CommandPermissionLevel.h"
#include "mc/world/actor/Actor.h"
#include "mc/world/actor/player/Player.h"


namespace TLCommand::WarpCommand {

void RegWarpCommand() {
    auto& cmd = ll::command::CommandRegistrar::getInstance()
                    .getOrCreateCommand("warp", "Warp to a location"_tr(), CommandPermissionLevel::Any);
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
            if (player->getPlayerPermissionLevel() == PlayerPermissionLevel::Operator) {
                auto res =
                    TLModule::getInstance()->mWarp->addWarp(param.name, player->getPosition(), player->getDimension());
                if (res) {
                    output.success(
                        TLUtil::I18n::translate("command.warp.add.success", TLUtil::PlayerData::getPlayerLang(*player))
                    );
                } else {
                    output.error(
                        TLUtil::I18n::translate("command.warp.add.error", TLUtil::PlayerData::getPlayerLang(*player))
                    );
                }
            } else {
                output.error(TLUtil::I18n::translate("permission.denied", TLUtil::PlayerData::getPlayerLang(*player)));
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
            if (player->getPlayerPermissionLevel() == PlayerPermissionLevel::Operator) {
                auto res = TLModule::getInstance()->mWarp->removeWarp(param.name);
                if (res) {
                    output.success(
                        TLUtil::I18n::translate("command.warp.del.success", TLUtil::PlayerData::getPlayerLang(*player))
                    );
                } else {
                    output.error(
                        TLUtil::I18n::translate("command.warp.del.error", TLUtil::PlayerData::getPlayerLang(*player))
                    );
                }
            } else {
                output.error(TLUtil::I18n::translate("permission.denied", TLUtil::PlayerData::getPlayerLang(*player)));
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
            auto  res    = TLModule::getInstance()->mWarp->warpTo(*player, param.name);
            if (res) {
                output.success(
                    TLUtil::I18n::translate("command.warp.go.success", TLUtil::PlayerData::getPlayerLang(*player))
                );
            } else {
                output.error(
                    TLUtil::I18n::translate("command.warp.go.error", TLUtil::PlayerData::getPlayerLang(*player))
                );
            }
        });
    cmd.overload()

        .text("list")
        .execute([](CommandOrigin const& origin, CommandOutput& output) {
            auto*       entity = origin.getEntity();
            auto        res    = TLModule::getInstance()->mWarp->listWarps();
            std::string list   = "";
            for (auto const& warp : res) {
                list += (warp + "\n");
            }
            if (entity == nullptr || !entity->isType(ActorType::Player)) {
                output.success(list);
                return;
            }
            auto* player = static_cast<Player*>(entity);
            auto  lang   = TLUtil::PlayerData::getPlayerLang(*player);
            output.success((TLUtil::I18n::translate("command.warp.list.success", lang)) + "\n" + list);
        });
}
} // namespace TLCommand::WarpCommand