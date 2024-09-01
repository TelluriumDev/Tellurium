#include "Event/MoneyEvent/MoneySetEvent.h"

#include <ll/api/service/Bedrock.h>

#include <mc/world/level/Level.h>

namespace TEvent::inline MoneyEvent {
Player* MoneySetEvent::tryGetPlayer() { return ll::service::getLevel()->getPlayer(mPlayerUUID); }

const mce::UUID& MoneySetEvent::getPlayerUUID() { return mPlayerUUID; }

int MoneySetEvent::getMoney() { return mMoney; }

const std::string& MoneySetEvent::getNote() { return mNote; }

MoneySetOptions MoneySetEvent::getOption() { return mOption; }
} // namespace TEvent::inline MoneyEvent