#pragma once

#include "Tellurium/base/Macro.h"

#include <ll/api/data/KeyValueDB.h>
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>
#include <ll/api/reflection/DESerialization.h>
#include <ll/api/reflection/Reflection.h>
#include <ll/api/reflection/Serialization.h>
#include <mc/deps/core/mce/UUID.h>
#include <mc/math/Vec3.h>
#include <mc/world/actor/player/Player.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>


namespace Tellurium {
class HomeSystem {
private:
    std::unique_ptr<ll::data::KeyValueDB> homeDb;

public:
    struct HomeDate {
        std::string name;
        Vec3        position;
        int         dimensionId;
    };


    HomeSystem();

    TUAPI static std::optional<HomeSystem>& getInstance();

public:
    TUAPI bool addHome(Player& player, std::string name);

    TUAPI bool deleteHome(Player& player, std::string name);

    TUAPI bool teleportHome(Player& player, std::string name);

    TUAPI std::vector<HomeDate> getHome(mce::UUID target);
};

}; // namespace Tellurium

namespace Tellurium::Event {

#define HOME_EVENT_MACRO(TYPE)                                                                                         \
    class TYPE##HomeBeforeEvent final : public ll::event::Cancellable<ll::event::Event> {                              \
    protected:                                                                                                         \
        Player&               mPlayer;                                                                                 \
        HomeSystem::HomeDate& mHome;                                                                                   \
                                                                                                                       \
    public:                                                                                                            \
        constexpr explicit TYPE##HomeBeforeEvent(Player& mPlayer, HomeSystem::HomeDate& mHome)                         \
        : Cancellable(),                                                                                               \
          mPlayer(mPlayer),                                                                                            \
          mHome(mHome) {}                                                                                              \
                                                                                                                       \
        Player&               getPlayer() const { return mPlayer; }                                                    \
        HomeSystem::HomeDate& getHome() const { return mHome; }                                                        \
    };                                                                                                                 \
                                                                                                                       \
    class TYPE##HomeAfterEvent final : public ll::event::Event {                                                       \
    private:                                                                                                           \
        Player&                     mPlayer;                                                                           \
        HomeSystem::HomeDate const& mHome;                                                                             \
                                                                                                                       \
    public:                                                                                                            \
        constexpr explicit TYPE##HomeAfterEvent(Player& mPlayer, HomeSystem::HomeDate const& mHome)                    \
        : mPlayer(mPlayer),                                                                                            \
          mHome(mHome) {}                                                                                              \
                                                                                                                       \
        Player&                     getPlayer() { return mPlayer; }                                                    \
        HomeSystem::HomeDate const& getHome() const { return mHome; }                                                  \
    };

HOME_EVENT_MACRO(Add);
HOME_EVENT_MACRO(Delete);
HOME_EVENT_MACRO(Teleport);

} // namespace Tellurium::Event