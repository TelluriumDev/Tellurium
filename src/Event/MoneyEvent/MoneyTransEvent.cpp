#include "Event/MoneyEvent/MoneyTransEvent.h"

namespace TEvent::inline MoneyEvent {
Player& MoneyTransEvent::getPlayer() { return *mPlayer; }

Player& MoneyTransEvent::getTarget() { return *mTarget; }

int MoneyTransEvent::getMoney() { return mMoney; }

} // namespace TEvent::inline MoneyEvent