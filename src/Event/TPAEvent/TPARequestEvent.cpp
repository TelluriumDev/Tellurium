#include "Event/TPAEvent/TPARequestEvent.h"

namespace TLEvent::inline TPAEvent {

Player* TPARequestEvent::getSender() { return mSender; };

Player* TPARequestEvent::getTarget() { return mTarget; };

} // namespace TLEvent::inline TPAEvent