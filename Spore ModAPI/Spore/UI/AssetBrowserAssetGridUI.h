#pragma once

#include <Spore\Sporepedia\AssetData.h>
#include <Spore\UI\cSPAssetView.h>
#include <EASTL\vector.h>

namespace UI
{
	class AssetBrowserAssetGridUI
	{
		struct Entry
		{
			/* 00h */	ResourceKey mAssetKey;
			/* 0Ch */	cSPAssetDataOTDBPtr mAssetData;
			/* 10h */	cSPAssetViewPtr mAssetView;
			/* 14h */	int field_14;
			/* 18h */	int field_18;
			/* 1Ch */	bool field_1C;
			/* 1Dh */	bool field_1D;
		};
		ASSERT_SIZE(Entry, 0x20);
		//TODO ctor at sub_651750
		// sub_6526B0 updates text related with num assets
		// sub_6608E0 checks if filter applies for a creation

		// AssetViewManager.field_CC is vector of selected

		// sub_6435F0 is the ctor of an object that has a map<ResourceKey, cSPAssetDataOTDBPtr> at 48h
		// sub_643C20 adds to that map

		/* 00h */	char padding_0[0xE8];
		/* E8h */	eastl::vector_map<ResourceKey, cSPAssetDataOTDBPtr> mAssets;
		/* 100h	*/	char padding_100[0x1AC - 0x100];
		/// How many creations in the current tab
		/* 1ACh */	int mNumCreations;
		/// How many creations in the current tab after filtering
		/* 1B0h */	int mNumFilteredCreations;
		/* 1B4h */	int field_1B4;
		/* 1B8h */	bool field_1B8;
		/* 1B9h */	bool mFilterByPlayable;
		/* 1BAh */	bool mFilterByEditable;
		/* 1BBh */	bool mFilterByViewableLarge;
		/* 1BCh */	char padding_1BC[0x1F0 - 0x1BC];
	};
	ASSERT_SIZE(AssetBrowserAssetGridUI, 0x1F0);
}