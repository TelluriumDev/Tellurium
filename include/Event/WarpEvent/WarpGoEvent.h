#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"

#include "mc/_HeaderOutputPredefine.h"
#include "mc/math/Vec3.h"
#include "mc/world/actor/player/Player.h"

namespace TLEvent::inline WarpEvent {

class WarpGoEvent final : public ll::event::Cancellable<ll::event::Event> {
private:
    Player*      mPlayer;
    std::string const& mName;
    const Vec3&        mPos;
    DimensionType   mDimensionType;

public:
    WarpGoEvent(Player* player, std::string const& name, const Vec3& pos, DimensionType dim)
    : Cancellable(),
      mPlayer(player),
      mName(name),
      mPos(pos),
      mDimensionType(dim) {}

    Player*      getPlayer();
    std::string const& getName();
    const Vec3&        getPos();
    DimensionType&   getDimensionType();
};
}; // namespace TLEvent::inline WarpEvent