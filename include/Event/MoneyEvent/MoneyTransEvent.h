#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"

#include "mc/world/actor/player/Player.h"

#include <string>

namespace TLEvent::inline MoneyEvent {

class MoneyTransEvent final : public ll::event::Cancellable<ll::event::Event> {

private:
    const mce::UUID&  mPlayerUUID;
    const mce::UUID&  mTargetUUID;
    long long         mMoney;
    const std::string mNote;

public:
    MoneyTransEvent(const mce::UUID& uuid, const mce::UUID& uuid2, long long money, const std::string& note)
    : Cancellable(),
      mPlayerUUID(uuid),
      mTargetUUID(uuid2),
      mMoney(money),
      mNote(note) {}

    const mce::UUID&   getPlayerUUID();
    const mce::UUID&   getTargetUUID();
    Player*            getPlayer();
    Player*            getTarget();
    long long          getMoney();
    const std::string& getNote();
};
} // namespace TLEvent::inline MoneyEvent