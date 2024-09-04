#include "Event/MoneyEvent/MoneyAddEvent.h"

#include "ll/api/service/Bedrock.h"

#include "mc/world/level/Level.h"

namespace TLEvent::inline MoneyEvent {
Player* MoneyAddEvent::getPlayer() { return mPlayer; }

long long MoneyAddEvent::getMoney() { return mMoney; }

const std::string& MoneyAddEvent::getNote() { return mNote; }
} // namespace TLEvent::inline MoneyEvent