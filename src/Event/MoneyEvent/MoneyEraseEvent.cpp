#include "Event/MoneyEvent/MoneyEraseEvent.h"

namespace TEvent::inline MoneyEvent {
Player& MoneyEraseEvent::getPlayer() { return *mPlayer; }

int MoneyEraseEvent::getMoney() { return mMoney; }
} // namespace TEvent::inline MoneyEvent