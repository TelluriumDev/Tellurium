#include "Event/MoneyEvent/MoneyReduceEvent.h"

#include <mc/world/level/Level.h>

#include <ll/api/service/Bedrock.h>

namespace TLEvent::inline MoneyEvent {
Player* MoneyReduceEvent::tryGetPlayer() { return ll::service::getLevel()->getPlayer(mPlayerUUID); }

mce::UUID& MoneyReduceEvent::getPlayerUUID() { return mPlayerUUID; }

int MoneyReduceEvent::getMoney() { return mMoney; }

std::string& MoneyReduceEvent::getNote() { return mNote; }
} // namespace TEvent::inline MoneyEvent