#include "Event/MoneyEvent/MoneyAddEvent.h"

#include "ll/api/service/Bedrock.h"

#include "mc/world/level/Level.h"

namespace TLEvent::inline MoneyEvent {

const mce::UUID& MoneyAddEvent::getUUID() { return mUUID; }


Player* MoneyAddEvent::getPlayer() {
    return static_cast<Player*>(ll::service::getLevel()->fetchEntity(ActorUniqueID::fromUUID(mUUID)));
}

long long MoneyAddEvent::getMoney() { return mMoney; }

const std::string& MoneyAddEvent::getNote() { return mNote; }
} // namespace TLEvent::inline MoneyEvent