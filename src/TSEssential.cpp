#include "TSEssential.h"
#include "Config.h"

namespace TSEssential
{

    bool Load()
    {
        return true;
    }
    bool Unload()
    {
        return true;
    }
    bool Enable()
    {
        Load();
        return true;
    }
    bool Disable()
    {
        return true;
    }
} // namespace TSEssential
