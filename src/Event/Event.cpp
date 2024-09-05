#include "Event/Event.h"
#include "Utils/PlayerData/PlayerData.h"

#include "ll/api/event/EventBus.h"
#include "ll/api/event/player/PlayerJoinEvent.h"

namespace TLEvent {

auto& eventBus = ll::event::EventBus::getInstance();
void  initTLEvent() { RegListener(); };

void RegListener() {
    eventBus.emplaceListener<ll::event::PlayerJoinEvent>([](ll::event::PlayerJoinEvent& ev) {
        auto& player = ev.self();
        json  j;
        j["lang"] = "zh_CN";
        TLUtil::PlayerData::getInstance().set(player.getUuid().asString(), j);
    });
}
} // namespace TLEvent