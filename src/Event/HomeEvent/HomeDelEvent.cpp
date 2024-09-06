#include "Event/HomeEvent/HomeDelEvent.h"

namespace TLEvent::inline HomeEvent {

Player* HomeDelEvent::getPlayer() { return mPlayer; };

std::string& HomeDelEvent::getName() { return mName; };

} // namespace TLEvent::inline HomeEvent