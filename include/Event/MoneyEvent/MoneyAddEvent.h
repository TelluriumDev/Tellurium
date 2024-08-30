#pragma once

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>

#include <mc/world/actor/player/Player.h>

namespace TEvent::inline MoneyEvent {

class MoneyAddEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    mce::UUID   mPlayerUUID;
    int         mMoney;
    std::string mNote;

public:
    MoneyAddEvent(Player* player, int money, std::string& note)
    : Cancellable(),
      mPlayerUUID(player->getUuid()),
      mMoney(money),
      mNote(note) {}
    MoneyAddEvent(mce::UUID playerUUID, int money, std::string& note)
    : Cancellable(),
      mPlayerUUID(playerUUID),
      mMoney(money),
      mNote(note) {}

    Player*      tryGetPlayer();
    mce::UUID&   getPlayerUUID();
    int          getMoney();
    std::string& getNote();
};
} // namespace TEvent::inline MoneyEvent