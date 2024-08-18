// Private Headers
#include <Global.h>
#include "modules/TPA.h"

// LLAPI Headers
#include <ll/api/Logger.h>

void LoadModules() {
    if (config.Modules.TPA.enabled)
    {
        LoadTPA(config.Modules.TPA.allowTPASelf, config.Modules.TPA.ExpireTime);
        
    }
    
}