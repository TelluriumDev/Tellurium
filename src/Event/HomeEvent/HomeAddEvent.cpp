#include "Event/HomeEvent/HomeAddEvent.h"

#include "mc/world/level/dimension/Dimension.h"

namespace TLEvent::inline HomeEvent {

Player* HomeAddEvent::getPlayer() { return mPlayer; };

std::string& HomeAddEvent::getName() { return mName; };

const Vec3& HomeAddEvent::getPos() { return mPos; };

Dimension& HomeAddEvent::getDimension() { return mDimension; };

} // namespace TLEvent::inline HomeEvent