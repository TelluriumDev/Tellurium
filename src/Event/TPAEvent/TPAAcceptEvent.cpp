#include "Event/TPAEvent/TPAAcceptEvent.h"

namespace TEvent::inline TPAEvent {

Player& TPAAcceptEvent::getSender() { return *mSender; }

Player& TPAAcceptEvent::getTarget() { return *mTarget; }

} // namespace TEvent::inline TPAEvent