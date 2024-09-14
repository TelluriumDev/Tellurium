#include "Event/MoneyEvent/MoneyTransEvent.h"

#include "ll/api/service/Bedrock.h"

#include "mc/world/level/Level.h"

namespace TLEvent::inline MoneyEvent {

const mce::UUID& MoneyTransEvent::getPlayerUUID() { return mPlayerUUID; }

const mce::UUID& MoneyTransEvent::getTargetUUID() { return mTargetUUID; }

Player* MoneyTransEvent::getPlayer() {
    return static_cast<Player*>(ll::service::getLevel()->fetchEntity(ActorUniqueID::fromUUID(mPlayerUUID)));
}

Player* MoneyTransEvent::getTarget() {
    return static_cast<Player*>(ll::service::getLevel()->fetchEntity(ActorUniqueID::fromUUID(mTargetUUID)));
}

long long MoneyTransEvent::getMoney() { return mMoney; }

const std::string& MoneyTransEvent::getNote() { return mNote; }
} // namespace TLEvent::inline MoneyEvent