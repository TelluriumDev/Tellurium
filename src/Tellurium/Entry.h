#pragma once

#include <span> // temporary repair workflow

#include <ll/api/mod/NativeMod.h>

namespace Tellurium {

class Entry {

public:
    static std::unique_ptr<Entry>& getInstance();

    Entry(ll::mod::NativeMod& self) : mSelf(self) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();

    bool unload();

private:
    ll::mod::NativeMod& mSelf;
};

} // namespace Tellurium