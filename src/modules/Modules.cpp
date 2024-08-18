#include <Global.h>
#include <map>
#include <ll/api/Logger.h>
#include "modules/TPA.h"


void LoadModules() {
    if (config.Modules.TPA.enabled)
    {
        LoadTPA(config.Modules.TPA.allowTPASelf, config.Modules.TPA.ExpireTime);
        
    }
    
}