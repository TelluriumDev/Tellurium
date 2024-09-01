
#pragma once

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>

#include <mc/world/actor/player/Player.h>

#include <string>

namespace TLEvent::inline MoneyEvent {

class MoneyReduceEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    const mce::UUID   mPlayerUUID;
    int               mMoney;
    const std::string mNote;

public:
    MoneyReduceEvent(Player* player, int money, const std::string& note)
    : Cancellable(),
      mPlayerUUID(player->getUuid()),
      mMoney(money),
      mNote(note) {}
    MoneyReduceEvent(const mce::UUID playerUUID, int money, const std::string& note)
    : Cancellable(),
      mPlayerUUID(playerUUID),
      mMoney(money),
      mNote(note) {}

    Player*            tryGetPlayer();
    const mce::UUID&   getPlayerUUID();
    int                getMoney();
    const std::string& getNote();
};
} // namespace TEvent::inline MoneyEvent