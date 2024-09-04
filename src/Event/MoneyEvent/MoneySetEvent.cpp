#include "Event/MoneyEvent/MoneySetEvent.h"


#include "mc/world/level/Level.h"

namespace TLEvent::inline MoneyEvent {
Player* MoneySetEvent::getPlayer() { return mPlayer; }

long long MoneySetEvent::getMoney() { return mMoney; }

const std::string& MoneySetEvent::getNote() { return mNote; }

} // namespace TLEvent::inline MoneyEvent