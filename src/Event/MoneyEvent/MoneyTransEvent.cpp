#include "Event/MoneyEvent/MoneyTransEvent.h"

#include "mc/world/level/Level.h"

namespace TLEvent::inline MoneyEvent {
Player* MoneyTransEvent::getPlayer() { return mPlayer; }

Player* MoneyTransEvent::getTarget() { return mTarget; }

long long  MoneyTransEvent::getMoney() { return mMoney; }

const std::string& MoneyTransEvent::getNote() { return mNote; }
} // namespace TLEvent::inline MoneyEvent