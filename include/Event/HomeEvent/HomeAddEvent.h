#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"

#include "mc/math/Vec3.h"
#include "mc/world/actor/player/Player.h"

namespace TLEvent::inline HomeEvent {

class HomeAddEvent final : public ll::event::Cancellable<ll::event::Event> {
private:
    Player*      mPlayer;
    std::string& mName;
    const Vec3&  mPos;
    Dimension&   mDimension;

public:
    HomeAddEvent(Player* player, std::string& name, const Vec3& pos, Dimension& dim)
    : Cancellable(),
      mPlayer(player),
      mName(name),
      mPos(pos),
      mDimension(dim) {}

    Player*      getPlayer();
    std::string& getName();
    const Vec3&  getPos();
    Dimension&   getDimension();
};
}; // namespace TLEvent::inline HomeEvent