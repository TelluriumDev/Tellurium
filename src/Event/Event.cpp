#include "Event/Event.h"
#include "Utils/PlayerData/PlayerData.h"

#include "ll/api/event/EventBus.h"
#include "ll/api/event/player/PlayerJoinEvent.h"

namespace ll::event::inline TLEvent {

auto& eventBus = ll::event::EventBus::getInstance();
void  initTLEvent() { RegListener(); };

void RegListener() {
    eventBus.emplaceListener<ll::event::PlayerJoinEvent>([](ll::event::PlayerJoinEvent&) {

    });
}
} // namespace ll::event::inline TLEvent