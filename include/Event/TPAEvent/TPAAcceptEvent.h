#pragma once

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>
#include <mc/world/actor/player/Player.h>

namespace TLEvent::inline TPAEvent {
class TPAAccepTLEvent final : public ll::event::Cancellable<ll::event::Event> {
private:
    Player* mSender;
    Player* mTarget;

public:
    constexpr explicit TPAAccepTLEvent(Player* sender, Player* target)
    : Cancellable(),
      mSender(sender),
      mTarget(target){};

    Player& getSender();
    Player& getTarget();
};
} // namespace TLEvent::inline TPAEvent