
#pragma once

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>

#include <mc/world/actor/player/Player.h>

#include <string>

namespace TEvent::inline MoneyEvent {

class MoneyReduceEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    mce::UUID   mPlayerUUID;
    int         mMoney;
    std::string mNote;

public:
    MoneyReduceEvent(Player* player, int money, std::string& note)
    : Cancellable(),
      mPlayerUUID(player->getUuid()),
      mMoney(money),
      mNote(note) {}

    Player*      tryGetPlayer();
    mce::UUID&   getPlayerUUID();
    int          getMoney();
    std::string& getNote();
};
} // namespace TEvent::inline MoneyEvent