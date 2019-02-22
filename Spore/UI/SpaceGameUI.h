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

#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\UILayout.h>

#include <Spore\UI\TiledScrollPanel.h>

#include <Spore\App\IMessageListener.h>

#include <Spore\LocalizedString.h>
#include <Spore\Object.h>

#include <EASTL\vector.h>
#include <EASTL\hash_map.h>

namespace UI
{
	using namespace UTFWin;
	// using namespace Simulator;

	class SpaceGameUI
		: public IWinProc
		, public DefaultRefCounted
		, public App::IMessageListener
	{
	public:
		void Load();

	protected:
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
		/* 224h */	int field_224;  // GlobalUI
		/* 228h */	int field_228;  // intrusive_ptr  Space UI
		/* 22Ch */	intrusive_ptr<UILayout> mpSpaceStarRolloverLayout;
		/* 230h */	intrusive_ptr<UILayout> mpSpaceStarTooltipLayout;
		/* 234h */	intrusive_ptr<UILayout> mpSpacePlanetTooltipLayout;
		/* 238h */	intrusive_ptr<Object> field_238;
		/* 23Ch */	int field_23C;
		/* 240h */	vector<int> field_240;
		/* 254h */	int field_254;  // intrusive_ptr
		/* 258h */	intrusive_ptr<UILayout> mpCaptainDialogLayout;
		/* 25Ch */	hash_map<int, intrusive_ptr<Object>> field_25C;
		/* 27Ch */	vector<int> field_27C;
		/* 290h */	int field_290;  // not initialized
		/* 294h */	intrusive_ptr<Object> field_294;
		/* 298h */	intrusive_ptr<Object> field_298;
		/* 29Ch */	intrusive_ptr<Object> field_29C;
		// panelID -> ?
		/* 2A0h */	hash_map<uint32_t, int> field_2A0;
		/* 2C0h */	vector<int> field_2C0;
		/* 2D4h */	hash_map<int, int> field_2D4;
		/* 2F4h */	uint32_t field_2F4;  // 0x68E0210
		/* 2F8h */	int field_2F8;  // -1
		/* 2FCh */	intrusive_ptr<Object> field_2FC;
		/* 300h */	intrusive_ptr<Object> field_300;
		/* 304h */	intrusive_ptr<Object> field_304;
		/* 308h */	vector<int> field_308;
		/* 31Ch */	int field_31C;  // UI SpaceMinimap
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
		/* 530h */	vector<intrusive_ptr<Object>> field_530;
		/* 544h */	char _padding_544[0x24];
		/* 568h */	int field_568;  // UI Animator?
		/* 56Ch */	int field_56C;
		/* 570h */	int field_570;
		/* 574h */	int field_574;
		/* 578h */	int field_578;
		/* 57Ch */	int field_57C;
		/* 580h */	intrusive_ptr<Object> field_580;
		/* 584h */	int field_584;  // intrusive_ptr C0h (cModelObject, cPlanet?)
		/* 588h */	intrusive_ptr<Object> field_588;
		/* 58Ch */	intrusive_ptr<Object> field_58C;
		/* 590h */	intrusive_ptr<Object> field_590;
		/* 594h */	intrusive_ptr<Object> field_594;
		/* 598h */	intrusive_ptr<IWindow> mpSpaceStarRollover;
		/* 59Ch */	intrusive_ptr<IWindow> mpSpaceStarTooltip;
		/* 5A0h */	intrusive_ptr<IWindow> mpSpacePlanetTooltip;
		/* 5A4h */	intrusive_ptr<Object> field_5A4;  // cursor attachment
		/* 5A8h */	int field_5A8;  // intrusive_ptr  cUITimedTooltip
		/* 5ACh */	intrusive_ptr<Object> field_5AC;
		/* 5B0h */	intrusive_ptr<Object> field_5B0;
		/* 5B4h */	intrusive_ptr<Object> field_5B4;
		/* 5B8h */	int field_5B8;
		/* 5BCh */	int field_5BC;
		/* 5C0h */	intrusive_ptr<Object> field_5C0;
		/* 5C4h */	intrusive_ptr<Object> field_5C4;  // UIPosse
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
		/* 61Ch */	intrusive_ptr<Object> field_61C;
		/* 620h */	TiledScrollPanel field_620;
		/* 690h */	int field_690;  // not initialized
		/* 694h	*/	intrusive_ptr<Object> field_694;
		/* 698h	*/	vector<intrusive_ptr<Object>> field_698;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(SpaceGameUI) == 0x6AC, "sizeof(SpaceGameUI) != 6ACh");

	namespace InternalAddressList(SpaceGameUI)
	{
		DefineAddress(Load, GetAddress(0x10743F0, 0x1073730, 0x1073730));
	}
}