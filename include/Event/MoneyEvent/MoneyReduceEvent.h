
#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"

#include "mc/deps/core/mce/UUID.h"
#include "mc/world/actor/player/Player.h"

namespace TLEvent::inline MoneyEvent {

class MoneyReduceEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    const mce::UUID&  mUUID;
    long long         mMoney;
    const std::string mNote;

public:
    MoneyReduceEvent(const mce::UUID& uuid, long long money, const std::string& note)
    : Cancellable(),
      mUUID(uuid),
      mMoney(money),
      mNote(note) {}

    const mce::UUID&   getUUID();
    Player*            getPlayer();
    long long          getMoney();
    const std::string& getNote();
};
} // namespace TLEvent::inline MoneyEvent