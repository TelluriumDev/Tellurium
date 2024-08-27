#include "Event/TPAEvent/TPAAcceptEvent.h"

namespace TSETEvent::inline TPAEvent {
Player& TPAAcceptEvent::getSender() { return *mSender; }
Player& TPAAcceptEvent::getTarget() { return *mTarget; }
} // namespace TSETEvent::inline TPAEvent