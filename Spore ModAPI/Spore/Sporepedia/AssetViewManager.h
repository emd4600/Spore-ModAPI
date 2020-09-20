#pragma once

#include <Spore\Sporepedia\AssetData.h>

#define AssetViewManager (*Sporepedia::cAssetViewManager::Get())

namespace Sporepedia
{
	typedef cSPAssetDataOTDB* (*AssetDataFactory)();

	class class_B8 {
		// this is a PLACEHOLDER class
	public:
		void SetAssetDataFactory(uint32_t typeID, AssetDataFactory factory);
	};

	class cAssetViewManager
	{
	public:
		static cAssetViewManager* Get();

	public:
		char padding_0[0xB8];
		class_B8* field_B8;
		//TODO more things
	};

	namespace Addresses(cAssetViewManager)
	{
		DeclareAddress(Get);
	}

	namespace Addresses(class_B8) 
	{
		DeclareAddress(SetAssetDataFactory);
	}
}