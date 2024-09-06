#include "Event/WarpEvent/WarpGoEvent.h"

namespace TLEvent::inline WarpEvent {

Player* WarpGoEvent::getPlayer() { return mPlayer; }

std::string& WarpGoEvent::getName() { return mName; }

const Vec3& WarpGoEvent::getPos() { return mPos; }

DimensionType& WarpGoEvent::getDimensionType() { return mDimensionType; }

} // namespace TLEvent::inline WarpEvent