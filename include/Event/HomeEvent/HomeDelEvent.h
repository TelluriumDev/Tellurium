#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"

#include "mc/world/actor/player/Player.h"

namespace TLEvent::inline HomeEvent {

class HomeDelEvent final : public ll::event::Cancellable<ll::event::Event> {
private:
    Player*      mPlayer;
    std::string& mName;

public:
    HomeDelEvent(Player* player, std::string& name) : Cancellable(), mPlayer(player), mName(name) {}

    Player*      getPlayer();
    std::string& getName();
};
}; // namespace TLEvent::inline HomeEvent