#ifdef MODAPI_DLL_EXPORT
#include "stdafx.h"
#include <Spore\Sporepedia\ShopperRequest.h>
#include <Spore\Sporepedia\AssetBrowserQuery.h>
#include <Spore\Sporepedia\AssetData.h>
#include <Spore\Sporepedia\ObjectTemplateDB.h>
#include <Spore\Sporepedia\AssetViewManager.h>

namespace Sporepedia
{
	namespace Addresses(ShopperRequest) 
	{
		DefineAddress(Show, SelectAddress(0x64A700, 0x64A900));
	}

	namespace Addresses(cSPAssetDataOTDB)
	{
		DefineAddress(SetKey, SelectAddress(0x641020, 0x641330));
		
		DefineAddress(GetName, SelectAddress(0x6414F0, 0x641800));
		DefineAddress(GetAuthorName, SelectAddress(0x641500, 0x641810));
		DefineAddress(GetDescription, SelectAddress(0x641530, 0x641840));
		DefineAddress(GetImageKey, SelectAddress(0x6411C0, 0x6414D0));
		DefineAddress(GetBackgroundImageKey, SelectAddress(0x6411E0, 0x6414F0));
		DefineAddress(GetTags, SelectAddress(0x641540, 0x641850));
		
		DefineAddress(GetTimeCreated, SelectAddress(0x641550, 0x641860));
		DefineAddress(HasName, SelectAddress(0x641460, 0x641770));

		DefineAddress(func38h, SelectAddress(0x641490, 0x6417A0));
		DefineAddress(func3Ch, SelectAddress(0x6414A0, 0x6417B0));

		DefineAddress(AsyncSetKey, SelectAddress(0x641040, 0x641350));
		DefineAddress(func48h, SelectAddress(0x6417D0, 0x641AE0));
		DefineAddress(func4Ch, SelectAddress(0x6418D0, 0x641BE0));
		DefineAddress(LoadData, SelectAddress(0x6410B0, 0x6413C0));
		DefineAddress(GetAuthorID, SelectAddress(0x641510, 0x641820));

		DefineAddress(IsEditable, SelectAddress(0x6410F0, 0x641400));
		DefineAddress(func64h, SelectAddress(0x6410E0, 0x6413F0));
		DefineAddress(IsShareable, SelectAddress(0x641590, 0x6418A0));

		DefineAddress(IsShared, SelectAddress(0x641C80, 0x641F90));
		DefineAddress(func74h, SelectAddress(0xDD4D00, 0x5C0EC0));
		DefineAddress(func78h, SelectAddress(0x641140, 0x641450));
		DefineAddress(func7Ch, SelectAddress(0x641150, 0x641460));
		DefineAddress(func80h, SelectAddress(0x641170, 0x641480));

		DefineAddress(GetConsequenceTraits, SelectAddress(0x6424E0, 0x6426C0));
		DefineAddress(GetAssetID, SelectAddress(0x6414B0, 0x6417C0));
		DefineAddress(GetTimeDownloaded, SelectAddress(0x641570, 0x641880));

		DefineAddress(func9Ch, SelectAddress(0x641CB0, 0x641FC0));
		DefineAddress(SetKeyInternal, SelectAddress(0x641060, 0x641370));
		DefineAddress(SetAssetMetadata, SelectAddress(0x6419B0, 0x641CC0));
		DefineAddress(funcA8h, SelectAddress(0x641AF0, 0x641E00));
		DefineAddress(SetSummary, SelectAddress(0x641B20, 0x641E30));
		DefineAddress(ProcessSummary, SelectAddress(0x642010, 0x6421F0));
		DefineAddress(SetParameter, SelectAddress(0x642310, 0x6424F0));
	}

	namespace Addresses(cAssetViewManager)
	{
		DefineAddress(Get, SelectAddress(0x401030, 0x401030));
	}

	namespace Addresses(class_B8)
	{
		DefineAddress(SetAssetDataFactory, SelectAddress(0x6442C0, 0x6444D0));
	}

	namespace OTDB
	{
		namespace Addresses(cObjectTemplateDB)
		{
			DefineAddress(Get, SelectAddress(0x67CC90, 0x67CB00));
		}
	}
}

namespace Addresses(Sporepedia)
{
	DefineAddress(ProcessAssetFilter, SelectAddress(0x661970, 0x6618B0));
}
#endif
