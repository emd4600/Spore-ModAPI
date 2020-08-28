#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Sporepedia\ShopperRequest.h>
#include <Spore\Sporepedia\AssetBrowserQuery.h>
#include <Spore\Sporepedia\ObjectTemplateDB.h>


namespace Sporepedia
{
	namespace Addresses(ShopperRequest) 
	{
		DefineAddress(Show, SelectAddress(0x64A700, , 0x64A900));
	}

	namespace Addresses(cObjectTemplateDB)
	{
		DefineAddress(Get, SelectAddress(0x67CC90, , 0x67CB00));
	}
}

namespace Addresses(Sporepedia)
{
	DefineAddress(ProcessAssetFilter, SelectAddress(0x661970, , 0x6618B0));
}
#endif
