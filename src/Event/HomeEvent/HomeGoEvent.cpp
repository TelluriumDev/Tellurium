#include "Event/HomeEvent/HomeGoEvent.h"

namespace TLEvent::inline HomeEvent {

Player* HomeGoEvent::getPlayer() { return mPlayer; };

std::string& HomeGoEvent::getName() { return mName; };

const Vec3& HomeGoEvent::getPos() { return mPos; };

Dimension& HomeGoEvent::getDimension() { return mDimension; };

} // namespace TLEvent::inline HomeEvent