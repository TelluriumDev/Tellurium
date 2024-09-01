#pragma once

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>

#include <mc/world/actor/player/Player.h>

#include <string>

namespace TEvent::inline MoneyEvent {

class MoneyTransEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    const mce::UUID   mPlayerUUID;
    const mce::UUID   mTargetPlayerUUID;
    int               mMoney;
    const std::string mNote;

public:
    MoneyTransEvent(Player* player, Player* target, int money, const std::string& note)
    : Cancellable(),
      mPlayerUUID(player->getUuid()),
      mTargetPlayerUUID(target->getUuid()),
      mMoney(money),
      mNote(note) {}
    MoneyTransEvent(const mce::UUID& playerUUID, const mce::UUID& target, int money, const std::string& note)
    : Cancellable(),
      mPlayerUUID(playerUUID),
      mTargetPlayerUUID(target),
      mMoney(money),
      mNote(note) {}

    Player*            tryGetPlayer();
    Player*            tryGetTarget();
    const mce::UUID&   getPlayerUUID();
    const mce::UUID&   getTargetUUID();
    int                getMoney();
    const std::string& getNote();
};
} // namespace TEvent::inline MoneyEvent