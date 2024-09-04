#include "Event/MoneyEvent/MoneyReduceEvent.h"

#include "mc/world/level/Level.h"

#include "ll/api/service/Bedrock.h"

namespace TLEvent::inline MoneyEvent {
Player* MoneyReduceEvent::getPlayer() { return mPlayer; }

long long MoneyReduceEvent::getMoney() { return mMoney; }

const std::string& MoneyReduceEvent::getNote() { return mNote; }
} // namespace TLEvent::inline MoneyEvent