// #include "Modules/Modules.h"
// #include "ll/api/command/CommandHandle.h"
// #include "ll/api/command/CommandRegistrar.h"
// 
// #include "mc/server/commands/CommandOrigin.h"
// #include "mc/server/commands/CommandOutput.h"
// #include "mc/server/commands/CommandPermissionLevel.h"
// #include "mc/world/actor/Actor.h"
// #include "mc/world/actor/player/Player.h"
// 
// void RegTPRCmd() {
//     auto& cmd = ll::command::CommandRegistrar::getInstance()
//                     .getOrCreateCommand("tpr", "testcommand", CommandPermissionLevel::Any);
// 
//     cmd.overload().execute([](CommandOrigin const& origin, CommandOutput&) {
//         auto* entity = origin.getEntity();
//         if (entity == nullptr || !entity->isType(ActorType::Player)) {
//             // output.error("Only players can run this command");
//             return;
//         }
//         auto* player = static_cast<Player*>(entity);
//         bool  a;
//         TLModule::getModulesInstance()->mTPR->TPRPlayer(*player, a);
//         player->sendMessage("test command");
//     });
// }