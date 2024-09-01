#include "Event/TPAEvent/TPARequestEvent.h"
#include <mc/world/actor/player/Player.h>

namespace TLEvent::inline TPAEvent {

Player& TPARequestEvent::getSender() { return *mSender; };

Player& TPARequestEvent::getTarget() { return *mTarget; };

} // namespace TEvent::inline TPAEvent