
#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"

#include "mc/world/actor/player/Player.h"

namespace TLEvent::inline MoneyEvent {

class MoneyReduceEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    Player*           mPlayer;
    long long         mMoney;
    const std::string mNote;

public:
    MoneyReduceEvent(Player* player, long long money, const std::string& note)
    : Cancellable(),
      mPlayer(player),
      mMoney(money),
      mNote(note) {}

    Player*            getPlayer();
    long long          getMoney();
    const std::string& getNote();
};
} // namespace TLEvent::inline MoneyEvent