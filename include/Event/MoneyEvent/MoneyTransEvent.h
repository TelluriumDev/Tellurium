#pragma once

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>

#include <mc/world/actor/player/Player.h>

#include <string>

namespace TLEvent::inline MoneyEvent {

class MoneyTransEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    mce::UUID   mPlayerUUID;
    mce::UUID   mTargetPlayerUUID;
    int         mMoney;
    std::string mNote;

public:
    MoneyTransEvent(Player* player, Player* target, int money, std::string& note)
    : Cancellable(),
      mPlayerUUID(player->getUuid()),
      mTargetPlayerUUID(target->getUuid()),
      mMoney(money),
      mNote(note) {}
    MoneyTransEvent(mce::UUID& playerUUID, mce::UUID& target, int money, std::string& note)
    : Cancellable(),
      mPlayerUUID(playerUUID),
      mTargetPlayerUUID(target),
      mMoney(money),
      mNote(note) {}

    Player*      tryGetPlayer();
    Player*      tryGetTarget();
    mce::UUID&   getPlayerUUID();
    mce::UUID&   getTargetUUID();
    int          getMoney();
    std::string& getNote();
};
} // namespace TEvent::inline MoneyEvent