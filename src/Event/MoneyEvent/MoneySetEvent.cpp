#include "Event/MoneyEvent/MoneySetEvent.h"

namespace TEvent::inline MoneyEvent {
Player& MoneySetEvent::getPlayer() { return *mPlayer; }

int MoneySetEvent::getMoney() { return mMoney; }
} // namespace TEvent::inline MoneyEvent