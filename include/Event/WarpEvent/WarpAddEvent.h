#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"

#include "mc/math/Vec3.h"

namespace TLEvent::inline WarpEvent {

class WarpAddEvent final : public ll::event::Cancellable<ll::event::Event> {
private:
    std::string& mName;
    const Vec3&  mPos;
    Dimension&   mDimension;

public:
    WarpAddEvent(std::string& name, const Vec3& pos, Dimension& dim)
    : Cancellable(),
      mName(name),
      mPos(pos),
      mDimension(dim) {}

    std::string& getName();
    const Vec3&        getPos();
    Dimension&         getDimension();
};
}; // namespace TLEvent::inline WarpEvent