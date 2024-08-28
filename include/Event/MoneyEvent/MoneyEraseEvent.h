
#pragma once

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>


#include <mc/world/actor/player/Player.h>

namespace TEvent::inline MoneyEvent {

class MoneyEraseEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    Player* mPlayer;
    int     mMoney;

public:
    MoneyEraseEvent(Player* player, int money) : Cancellable(), mPlayer(player), mMoney(money) {}

    Player& getPlayer();
    int     getMoney();
};
} // namespace TEvent::inline MoneyEvent