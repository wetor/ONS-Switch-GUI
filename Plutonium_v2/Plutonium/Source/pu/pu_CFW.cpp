#include <pu/pu_CFW.hpp>

namespace pu
{
    bool IsAtmosphere()
    {
        //if(splInitialize() != 0) return false;
        //u64 tmpc = 0;
        //bool isatmos = R_SUCCEEDED(splGetConfig((SplConfigItem)65000, &tmpc));
        //splExit();
        //return isatmos;
	return true;
    }

    bool IsReiNX()
    {
        //Handle tmph = 0;
        //Result rc = smRegisterService(&tmph, "rnx", false, 1);
        //if(R_FAILED(rc)) return true;
        //smUnregisterService("rnx");
        return false;
    }
}
