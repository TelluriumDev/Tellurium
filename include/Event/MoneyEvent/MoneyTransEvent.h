#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"

#include "mc/world/actor/player/Player.h"

#include <string>

namespace TLEvent::inline MoneyEvent {

class MoneyTransEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    Player*           mPlayer;
    Player*           mTarget;
    long long         mMoney;
    const std::string mNote;

public:
    MoneyTransEvent(Player* player, Player* target, long long money, const std::string& note)
    : Cancellable(),
      mPlayer(player),
      mTarget(target),
      mMoney(money),
      mNote(note) {}

    Player*            getPlayer();
    Player*            getTarget();
    long long          getMoney();
    const std::string& getNote();
};
} // namespace TLEvent::inline MoneyEvent