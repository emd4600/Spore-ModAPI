#pragma once

#include <Spore\Object.h>
#include <Spore\Sporepedia\IShopperListener.h>
#include <Spore\Editors\EditorRequest.h>

namespace Sporepedia
{
	/// A class used to show the Sporepedia to the user, asking him to select a creation.
	/// A shopper request uses a configuration file in the AssetBrowserConfig folder
	/// to know what text it will show to the player, what are the available creation types, etc.
	/// 
	/// To know when the user selects a creature, you must create a class that inherits from IShopperListener
	///
	/// Example usage:
	/// @code
	/// // `this` can also be whatever object that inherits from IShopperListener
	/// Sporepedia::ShopperRequest request(this);
	/// request.SetShopperID(id("MilitaryAirShopper"));
	/// @endcode
	struct ShopperRequest
	{
		ShopperRequest(IShopperListener* listener = nullptr);

		/// Executes this request, showing the Sporepedia to the user. 
		/// This method returns immediately; when the user clicks the Accept button,
		/// the function specified at the constructor or at \c pListener (if any) will be executed.
		static void Show(ShopperRequest& request);

		/// The ID of the file in the \c AssetBrowserConfig folder that decides what the user can choose.
		/* 00h */	uint32_t shopperID;  // 0x578C04FA, GlobalTemplate
		/// The current game mode ID, it's set automatically.
		/* 04h */	uint32_t gameModeID;
		/* 08h */	int field_8;
		/* 0Ch */	int field_C;
		/* 10h */	bool field_10;
		/* 11h */	bool field_11;
		/* 12h */	bool field_12;
		/* 13h */	bool field_13;  // true
		/* 14h */	bool field_14;
		/// Key to the creation that is currently selected. If not specified, nothing is selected.
		/* 18h */	ResourceKey currentSelection;
		/* 24h */	bool field_24;  // true
		/* 28h */	int field_28;
		/* 2Ch */	bool field_2C;
		/* 30h */	uint32_t field_30;  // 0xAD0E52, also can be 0x54ACB9F1, 0x74174C59, 0x74D01473, 0x6135298, 0x53D6FE2A
		/* 34h */	int field_34;  // 1, number of selections expected?
		/// Pointer to an object that will be called when the user accepts the selection.
		/* 38h */	IShopperListener* pListener;
		/* 3Ch */	int field_3C;
		/* 40h */	intrusive_ptr<Editors::EditorRequest> pEditorRequest;
		/* 44h */	intrusive_ptr<DefaultRefCounted> field_44;
	};

	namespace Addresses(ShopperRequest) {
		DeclareAddress(Show, SelectAddress(0x64A700, , 0x64A900));
	}

	static_assert(sizeof(ShopperRequest) == 0x48, "sizeof(ShopperRequest)");
}