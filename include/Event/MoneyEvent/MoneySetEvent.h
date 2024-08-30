#pragma once

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>

#include <mc/world/actor/player/Player.h>

#include "Modules/Money/Money.h"


namespace TEvent::inline MoneyEvent {

class MoneySetEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    mce::UUID       mPlayerUUID;
    int             mMoney;
    std::string     mNote;
    MoneySetOptions mOption;

public:
    MoneySetEvent(Player* player, int money, std::string& note, MoneySetOptions opion)
    : Cancellable(),
      mPlayerUUID(player->getUuid()),
      mMoney(money),
      mNote(note),
      mOption(opion) {}
    MoneySetEvent(mce::UUID& playerUUID, int money, std::string& note, MoneySetOptions opion):
    : Cancellable(),
      mPlayerUUID(playerUUID),
      mMoney(money),
      mNote(note),
      mOption(opion) {}

    Player*         tryGetPlayer();
    mce::UUID&      getPlayerUUID();
    int             getMoney();
    std::string&    getNote();
    MoneySetOptions getOption();
};
} // namespace TEvent::inline MoneyEvent