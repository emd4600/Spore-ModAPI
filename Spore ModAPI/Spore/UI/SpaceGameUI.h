/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#pragma once

#include <Spore\Simulator\cPlayerInventory.h>

#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\UILayout.h>

#include <Spore\UI\GlobalUI.h>
#include <Spore\UI\TiledScrollPanel.h>
#include <Spore\UI\CivCommCursorAttachment.h>
#include <Spore\UI\Minimap.h>
#include <Spore\UI\SpaceToolPanelUI.h>

#include <Spore\App\IMessageListener.h>
#include <Spore\App\MessageListenerData.h>

#include <Spore\LocalizedString.h>
#include <Spore\Object.h>

#include <EASTL\vector.h>
#include <EASTL\hash_map.h>

#define SpaceGameUIPtr eastl::intrusive_ptr<UI::SpaceGameUI>

namespace UI
{
	class SpaceGameUI
		: public UTFWin::IWinProc
		, public DefaultRefCounted
		, public App::IMessageListener
	{
	public:
		using IWinProc::AddRef;
		using IWinProc::Release;

		void Load();

		void SetActivePalette(uint32_t paletteID);

	public:
		struct TerraformColors {
			/* 00h */	Color spaceUITerraformRingColorOff;
			/* 04h */	Color spaceUITerraformRingColorLocked;
			/* 08h */	Color spaceUITerraformRingColorEmpty;
			/* 0Ch */	Color spaceUITerraformRingColorPlants;
			/* 10h */	Color spaceUITerraformRingColorFull;
			/* 14h */	Color spaceUITerraformDotColorT0;
			/* 18h */	Color spaceUITerraformDotColorT1;
			/* 1Ch */	Color spaceUITerraformDotColorT2;
			/* 20h */	Color spaceUITerraformDotColorT3;
		};
		struct TerraformEcosystemSlot {
			/* 00h */	IWindowPtr mpButton;
			/* 04h */	int field_4;
			/* 08h */	int field_8;
			/* 0Ch */	int field_C;
			/* 10h */	int field_10;
			//TODO
			/* 14h */	uint32_t mGroup;
			/* 18h */	int field_18;
			/* 1Ch */	int field_1C;
			/* 20h */	int mTerraformScore;
			/* 24h */	int field_24;
		};
		ASSERT_SIZE(TerraformEcosystemSlot, 0x28);

		/* 10h */	int field_10;
		/* 14h */	int field_14;  // not initialized
		/* 18h */	int field_18;
		/* 1Ch */	LocalizedString mTextPlantScanned;
		/* 30h */	LocalizedString mTextPlantAlreadyScanned;
		/* 44h */	LocalizedString mTextCreatureScanned;
		/* 58h */	LocalizedString mTextCreatureAlreadyScanned;
		/* 6Ch */	LocalizedString mTextBuildingScanned;
		/* 80h */	LocalizedString mTextBuildingAlreadyScanned;
		/* 94h */	LocalizedString mTextVehicleScanned;
		/* A8h */	LocalizedString mTextVehicleAlreadyScanned;
		/* BCh */	LocalizedString mTextUFOScanned;
		/* D0h */	LocalizedString mTextUFOAlreadyScanned;
		/* E4h */	LocalizedString mTextPlanetSurrendered;
		/* F8h */	LocalizedString mTextPlanetNotSurrendered;
		/* 10Ch */	LocalizedString mTextTradeRouteProgress;
		/* 120h */	LocalizedString mTextCaptureProgress;
		/* 134h */	LocalizedString mTextRepairTurret;
		/* 148h */	LocalizedString mTextSellTurret;
		/* 15Ch */	LocalizedString mTextDemolish;
		/* 170h */	LocalizedString mTextSellBuilding;
		/* 184h */	LocalizedString mTextRepairBuilding;
		/* 198h */	LocalizedString mTextRepairSpaceship;
		/* 1ACh */	LocalizedString mTextBuyBuildings;
		/* 1C0h */	LocalizedString mTextAccessorizeCitizens;
		/* 1D4h */	LocalizedString mTextEditSpaceship;
		/* 1E8h */	LocalizedString mTextSellColony;
		/* 1FCh */	LocalizedString mTextShow;
		/* 210h */	LocalizedString mTextHide;
		/// The main UI of the space stage. It's `0x1E453B88.spui`
		/* 224h */	GlobalUI* mpGlobalUI;
		/* 228h */	int field_228;  // intrusive_ptr  Space UI
		/* 22Ch */	UILayoutPtr mpSpaceStarRolloverLayout;
		/* 230h */	UILayoutPtr mpSpaceStarTooltipLayout;
		/* 234h */	UILayoutPtr mpSpacePlanetTooltipLayout;
		/* 238h */	cPlayerInventoryPtr mpPlayerInventory;
		/* 23Ch */	uint32_t mActivePaletteID;
		/// A list of all available IDs of tool palettes (obtained from the `spaceToolPaletteID` property).
		/* 240h */	vector<uint32_t> mToolPaletteIDs;
		/// `0x46FED9C8.spui`, a layout that contains all space tools icons
		/* 254h */	UILayoutPtr mInventoryItemIcons;
		/* 258h */	UILayoutPtr mpCaptainDialogLayout;
		// paletteID to panel; I'm not sure about this, each palette can have more than one panel
		/* 25Ch */	hash_map<uint32_t, SpaceToolPanelUIPtr> mPalettePanels;
		//TODO Not exactly a vector, field_290 is also part of it
		/* 27Ch */	vector<uint32_t> mFoodwebPaletteIDs;
		/* 290h */	int field_290;  // not initialized
		/* 294h */	SpaceToolPanelUIPtr mpCargoPalettePanel;
		/// Shown over the spaceship thumbnail
		/* 298h */	SpaceToolPanelUIPtr mpCurrentToolPanel;
		// actually a subclass; uses spacetoolui~!0xFB82BCBA.prop
		/* 29Ch */	SpaceToolPanelUIPtr field_29C;
		// panelID -> ?
		/* 2A0h */	hash_map<uint32_t, int> field_2A0;
		/* 2C0h */	vector<int> field_2C0;
		/* 2D4h */	hash_map<int, int> field_2D4;
		/* 2F4h */	uint32_t field_2F4;  // 0x68E0210
		/* 2F8h */	int field_2F8;  // -1
		/* 2FCh */	ObjectPtr field_2FC;
		/* 300h */	ObjectPtr field_300;
		/* 304h */	ObjectPtr field_304;
		/* 308h */	vector<int> field_308;
		/* 31Ch */	MinimapPtr mpMinimap;
		/* 320h */	int field_320;  // not initialized
		/* 324h */	LocalizedString mTextSmallPlantSlot;
		/* 338h */	LocalizedString mTextMediumPlantSlot;
		/* 34Ch */	LocalizedString mTextLargePlantSlot;
		/* 360h */	LocalizedString mTextHerbivoreSlot;
		/* 374h */	LocalizedString mTextCarnivoreOmnivoreSlot;
		/* 388h */	LocalizedString mTextFillPlantsToUnlock;
		/* 39Ch */	LocalizedString mTextFillRowToUnlock;
		/* 3B0h */	LocalizedString mTextDominantSpecies;
		/* 3C4h */	LocalizedString mTextPlanetSpice;
		/* 3D8h */	LocalizedString mTextUnclaimed;
		/* 3ECh */	LocalizedString mTextClaimed;
		/* 400h */	LocalizedString mTextTravelCost;
		/* 414h */	LocalizedString mTextTravelDistance;
		/* 428h */	LocalizedString field_428;
		/* 43Ch */	LocalizedString mTextToolUseCost;
		/* 450h */	LocalizedString mTextFromItemPlanetName;
		/* 464h */	LocalizedString mTextSentient;
		/* 478h */	LocalizedString mTextItemAnimalType;
		/* 48Ch */	LocalizedString mTextItemPlantType;
		/* 4A0h */	LocalizedString mTextNotScanned;
		/* 4B4h */	LocalizedString field_4B4;
		/* 4C8h */	LocalizedString mTextTerraformLevel;
		/* 4DCh */	LocalizedString mTextImproveTerraformToUnlock;
		/* 4F0h */	LocalizedString mTextColonySlot;
		/* 504h */	vector<LocalizedString> field_504;
		/* 518h */	vector<LocalizedString> field_518;
		/* 52Ch */	float field_52C;  // 1.0
		/// The slots shown in the terraform panel (on the minimap) that represents the plants and animals
		/* 530h */	vector<TerraformEcosystemSlot> mTerraformEcosystemSlots;
		/* 544h */	TerraformColors mTerraformColors;
		/* 568h */	int field_568;  // UI Animator?
		/* 56Ch */	App::MessageListenerData mMessageListenerData;
		/* 580h */	ImagePtr mpFightButtonImage;
		/* 584h */	int field_584;  // intrusive_ptr C0h (cModelObject, cPlanet?)
		/* 588h */	ObjectPtr field_588;
		/* 58Ch */	ObjectPtr field_58C;
		/* 590h */	ObjectPtr field_590;
		/* 594h */	intrusive_ptr<Object> field_594;
		/* 598h */	IWindowPtr mpSpaceStarRollover;
		/* 59Ch */	IWindowPtr mpSpaceStarTooltip;
		/* 5A0h */	ObjectPtr mpSpacePlanetTooltip;
		/// Controls the mouse rollover that shows the relationships with other empires
		/* 5A4h */	CivCommCursorAttachmentPtr mpCivCommCursorAttachment;
		/* 5A8h */	int field_5A8;  // intrusive_ptr  cUITimedTooltip
		/* 5ACh */	ObjectPtr field_5AC;
		/* 5B0h */	ObjectPtr field_5B0;
		/* 5B4h */	ObjectPtr field_5B4;
		/* 5B8h */	int field_5B8;
		/* 5BCh */	int field_5BC;
		/* 5C0h */	ObjectPtr field_5C0;
		/* 5C4h */	ObjectPtr field_5C4;  // UIPosse
		/* 5C8h */	int field_5C8;
		/* 5CCh */	int field_5CC;  // 2
		/* 5D0h */	bool field_5D0;
		/* 5D1h */	bool field_5D1;
		/* 5D2h */	bool field_5D2;
		/* 5D3h */	bool field_5D3;
		/* 5D4h */	bool field_5D4;
		/* 5D5h */	bool field_5D5;  // true
		/* 5D8h */	vector<int> field_5D8;
		/* 5ECh */	char _padding_5EC[0x2C];  // map?
		/* 618h */	int field_618;
		/* 61Ch */	ObjectPtr mpFlashWindowManager;
		/* 620h */	TiledScrollPanel field_620;
		/* 690h */	int field_690;  // not initialized
		/* 694h	*/	ObjectPtr field_694;
		/* 698h	*/	vector<ObjectPtr> field_698;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(SpaceGameUI) == 0x6AC, "sizeof(SpaceGameUI) != 6ACh");

	namespace Addresses(SpaceGameUI)
	{
		DeclareAddress(Load);
		DeclareAddress(SetActivePalette);
	}
}