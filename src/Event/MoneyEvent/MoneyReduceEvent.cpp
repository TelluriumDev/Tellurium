#include "Event/MoneyEvent/MoneyReduceEvent.h"

#include "ll/api/service/Bedrock.h"

#include "mc/world/level/Level.h"

namespace TLEvent::inline MoneyEvent {

const mce::UUID& MoneyReduceEvent::getUUID() { return mUUID; }


Player* MoneyReduceEvent::getPlayer() {
    return static_cast<Player*>(ll::service::getLevel()->fetchEntity(ActorUniqueID::fromUUID(mUUID)));
}

long long MoneyReduceEvent::getMoney() { return mMoney; }

const std::string& MoneyReduceEvent::getNote() { return mNote; }
} // namespace TLEvent::inline MoneyEvent