#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>
#include <mc/world/actor/player/Player.h>

namespace TSETEvent::inline TPAEvent {
class TPAAcceptEvent final : public ll::event::Cancellable<ll::event::Event> {
private:
    Player* mSender;
    Player* mTarget;

public:
    constexpr explicit TPAAcceptEvent(Player* sender, Player* target)
    : Cancellable(),
      mSender(sender),
      mTarget(target){};

    Player& getSender();
    Player& getTarget();
};
} // namespace TSETEvent::inline TPAEvent