#include "Event/TPAEvent/TPARequestEvent.h"
#include <mc/world/actor/player/Player.h>

namespace TSETEvent::inline TPAEvent {

Player& TPARequestEvent::getSender() { return *mSender; };

Player& TPARequestEvent::getTarget() { return *mTarget; };

}