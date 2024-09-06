#include "Event/WarpEvent/WarpAddEvent.h"

namespace TLEvent::inline WarpEvent {

std::string& WarpAddEvent::getName() { return mName; }

const Vec3& WarpAddEvent::getPos() { return mPos; }

Dimension& WarpAddEvent::getDimension() { return mDimension; }

} // namespace TLEvent::inline WarpEvent