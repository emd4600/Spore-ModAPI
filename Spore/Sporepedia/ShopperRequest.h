#pragma once

#include <Spore\Object.h>
#include <Spore\Sporepedia\IShopperListener.h>

namespace Sporepedia
{
	struct ShopperRequest
	{
		ShopperRequest();
		ShopperRequest(IShopperListener* listener);

		static void Show(ShopperRequest& request);

		/// The ID of the file in `AssetBrowserConfig` that decides what the user can choose.
		/* 00h */	uint32_t shopperID;  // 0x578C04FA, GlobalTemplate
		/// The current game mode ID, it's not obligatory.
		/* 04h */	uint32_t gameModeID;
		/* 08h */	int field_8;
		/* 0Ch */	int field_C;
		/* 10h */	bool field_10;
		/* 11h */	bool field_11;
		/* 12h */	bool field_12;
		/* 13h */	bool field_13;  // true
		/* 14h */	bool field_14;
		/* 18h */	ResourceKey currentSelection;
		/* 24h */	bool field_24;  // true
		/* 28h */	int field_28;
		/* 2Ch */	bool field_2C;
		/* 30h */	uint32_t field_30;  // 0xAD0E52, also can be 0x54ACB9F1, 0x74174C59, 0x74D01473, 0x6135298, 0x53D6FE2A
		/* 34h */	int field_34;  // 1, number of selections expected?
		/* 38h */	IShopperListener* pListener;
		/* 3Ch */	int field_3C;
		/* 40h */	intrusive_ptr<DefaultRefCounted> field_40;  // EditorEntry
		/* 44h */	intrusive_ptr<DefaultRefCounted> field_44;
	};

	namespace InternalAddressList(ShopperRequest) {
		DefineAddress(Show, GetAddress(0x64A700, , PLACEHOLDER));
	}

	static_assert(sizeof(ShopperRequest) == 0x48, "sizeof(ShopperRequest)");
}