#include "Event/MoneyEvent/MoneyAddEvent.h"

namespace TEvent::inline MoneyEvent {
Player& MoneyAddEvent::getPlayer() { return *mPlayer; }

int MoneyAddEvent::getMoney() { return mMoney; }
} // namespace TEvent::inline MoneyEvent