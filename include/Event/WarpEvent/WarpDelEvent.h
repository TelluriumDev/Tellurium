
#pragma once

#include "ll/api/event/Cancellable.h"
#include "ll/api/event/Event.h"


namespace TLEvent::inline WarpEvent {

class WarpDelEvent final : public ll::event::Cancellable<ll::event::Event> {
private:
    std::string const& mName;

public:
    WarpDelEvent(std::string const& name) : Cancellable(), mName(name) {}

    std::string const& getName();
};
}; // namespace TLEvent::inline WarpEvent