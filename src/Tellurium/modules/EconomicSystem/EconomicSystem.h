#pragma once

#include "Tellurium/base/Macro.h"

#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>
#include <mc/deps/core/mce/UUID.h>
#include <optional>

namespace Tellurium {

class EconomicSystem {
public:
    TUAPI static std::optional<EconomicSystem>& getInstance();

    TUAPI static bool isValid();

public:
    TUAPI bool addMoney(mce::UUID target, int value);

    TUAPI bool reduceMoney(mce::UUID target, int value);

    TUAPI bool setMoney(mce::UUID target, int value);

    TUAPI int getMoney(mce::UUID target) const;
};

} // namespace Tellurium
 
namespace Tellurium::Event {

#define ECONOMIC_EVENT_MACRO(TYPE)                                                                                     \
    class TYPE##EconomicBeforeEvent final : public ll::event::Cancellable<ll::event::Event> {                          \
    protected:                                                                                                         \
        mce::UUID& mTarget;                                                                                            \
        int&       mValue;                                                                                             \
                                                                                                                       \
    public:                                                                                                            \
        constexpr explicit TYPE##EconomicBeforeEvent(mce::UUID& target, int& value)                                    \
        : Cancellable(),                                                                                               \
          mTarget(target),                                                                                             \
          mValue(value) {}                                                                                             \
                                                                                                                       \
        mce::UUID& getTarget() const { return mTarget; }                                                               \
        int&       getValue() const { return mValue; }                                                                 \
    };                                                                                                                 \
                                                                                                                       \
    class TYPE##EconomicAfterEvent final : public ll::event::Event {                                                   \
    private:                                                                                                           \
        mce::UUID const& mTarget;                                                                                      \
        int const&       mValue;                                                                                       \
                                                                                                                       \
    public:                                                                                                            \
        constexpr explicit TYPE##EconomicAfterEvent(mce::UUID const& target, int const& value)                         \
        : mTarget(target),                                                                                             \
          mValue(value) {}                                                                                             \
                                                                                                                       \
        mce::UUID const& getTarget() const { return mTarget; }                                                         \
        int const&       getValue() const { return mValue; }                                                           \
    };

ECONOMIC_EVENT_MACRO(Add);
ECONOMIC_EVENT_MACRO(Reduce);
ECONOMIC_EVENT_MACRO(Set);

} // namespace Tellurium::Event