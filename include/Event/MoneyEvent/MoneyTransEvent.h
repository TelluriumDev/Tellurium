#pragma once

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>


#include <mc/world/actor/player/Player.h>

namespace TEvent::inline MoneyEvent {

class MoneyTransEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    Player* mPlayer;
    Player* mTarget;
    int     mMoney;

public:
    MoneyTransEvent(Player* player, Player* target, int money)
    : Cancellable(),
      mPlayer(player),
      mTarget(target),
      mMoney(money) {}

    Player& getPlayer();
    Player& getTarget();
    int     getMoney();
};
} // namespace TEvent::inline MoneyEvent