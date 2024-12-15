#pragma once

#include "Tellurium/base/Macro.h"

#include <ll/api/data/KeyValueDB.h>
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Event.h>
#include <mc/deps/core/mce/UUID.h>
#include <mc/math/Vec3.h>
#include <optional>

namespace Tellurium {
class HomeSystem {
private:
    std::unique_ptr<ll::data::KeyValueDB> homeStorage;

public:
    struct HomeDate {
        mce::UUID            id;
        mce::UUID            owner;
        std::string          name;
        std::pair<Vec3, int> position;
    };

public:
    TUAPI static std::optional<HomeSystem>& getInstance();

    TUAPI std::unique_ptr<ll::data::KeyValueDB>& getHomeStorage();

public:
    TUAPI std::optional<HomeDate> addHome(mce::UUID player, std::string name, std::pair<Vec3, int> position);

    TUAPI bool deleteHome(mce::UUID homeId);

    TUAPI bool teleportHome(mce::UUID player, mce::UUID homeId);

    TUAPI std::vector<HomeDate> getHomes(mce::UUID player);

    TUAPI std::optional<HomeDate> getHome(mce::UUID homeId);

    TUAPI mce::UUID getNewHomeId();
};

}; // namespace Tellurium

namespace Tellurium::Event {

class AddHomeBeforeEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    HomeSystem::HomeDate& mHomeData;

public:
    constexpr explicit AddHomeBeforeEvent(HomeSystem::HomeDate& homeData) : Cancellable(), mHomeData(homeData) {}

    HomeSystem::HomeDate& getHomeData() const { return mHomeData; }
};

class AddHomeAfterEvent final : public ll::event::Event {
private:
    HomeSystem::HomeDate const& mHomeData;

public:
    constexpr explicit AddHomeAfterEvent(HomeSystem::HomeDate const& homeData) : mHomeData(homeData) {}

    HomeSystem::HomeDate const& getHomeData() const { return mHomeData; }
};


class DeleteHomeBeforeEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    mce::UUID& mHomeId;

public:
    constexpr explicit DeleteHomeBeforeEvent(mce::UUID& homeId) : Cancellable(), mHomeId(homeId) {}

    mce::UUID& getHomeId() const { return mHomeId; }
};

class DeleteHomeAfterEvent final : public ll::event::Event {
private:
    mce::UUID const& mHomeId;

public:
    constexpr explicit DeleteHomeAfterEvent(mce::UUID const& homeId) : mHomeId(homeId) {}

    mce::UUID const& getHomeId() const { return mHomeId; }
};


class TeleportHomeBeforeEvent final : public ll::event::Cancellable<ll::event::Event> {
protected:
    mce::UUID&            mPlayer;
    HomeSystem::HomeDate& mHomeData;

public:
    constexpr explicit TeleportHomeBeforeEvent(mce::UUID& player, HomeSystem::HomeDate& homeData)
    : Cancellable(),
      mPlayer(player),
      mHomeData(homeData) {}

    mce::UUID& getPlayer() const { return mPlayer; }

    HomeSystem::HomeDate& getHomeData() const { return mHomeData; }
};

class TeleportHomeAfterEvent final : public ll::event::Event {
private:
    mce::UUID const&            mPlayer;
    HomeSystem::HomeDate const& mHomeData;

public:
    constexpr explicit TeleportHomeAfterEvent(mce::UUID const& player, HomeSystem::HomeDate const& homeData)
    : mPlayer(player),
      mHomeData(homeData) {}

    mce::UUID const& getPlayer() const { return mPlayer; }

    HomeSystem::HomeDate const& getHomeData() const { return mHomeData; }
};

} // namespace Tellurium::Event