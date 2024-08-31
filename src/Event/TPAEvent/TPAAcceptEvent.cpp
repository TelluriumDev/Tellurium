#include "Event/TPAEvent/TPAAcceptEvent.h"

namespace TLEvent::inline TPAEvent {

Player& TPAAcceptEvent::getSender() { return *mSender; }

Player& TPAAcceptEvent::getTarget() { return *mTarget; }

} // namespace TEvent::inline TPAEvent