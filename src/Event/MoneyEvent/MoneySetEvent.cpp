#include "Event/MoneyEvent/MoneySetEvent.h"

#include "ll/api/service/Bedrock.h"

#include "mc/world/level/Level.h"

namespace TLEvent::inline MoneyEvent {

const mce::UUID& MoneySetEvent::getUUID() { return mUUID; }

Player* MoneySetEvent::getPlayer() {
    return static_cast<Player*>(ll::service::getLevel()->fetchEntity(ActorUniqueID::fromUUID(mUUID)));
}

long long MoneySetEvent::getMoney() { return mMoney; }

const std::string& MoneySetEvent::getNote() { return mNote; }

} // namespace TLEvent::inline MoneyEvent