#include "Event/Event.h"
#include "Config/Config.h"
#include "Utils/PlayerData.h"


#include "ll/api/event/EventBus.h"
#include "ll/api/event/player/PlayerJoinEvent.h"

namespace TLEvent {

auto& eventBus = ll::event::EventBus::getInstance();
void  initTLEvent() { RegListener(); };

void RegListener() {
    eventBus.emplaceListener<ll::event::PlayerJoinEvent>([](ll::event::PlayerJoinEvent& ev) {
        auto& player = ev.self();
        TLUtil::PlayerData::setPlayerLang(player, config.Language);
    });
}
} // namespace TLEvent