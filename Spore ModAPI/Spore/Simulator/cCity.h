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

#include <Spore\Simulator\cCommunity.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cBuilding.h>
#include <Spore\Simulator\cOrnament.h>
#include <Spore\Simulator\cCityTerritory.h>
#include <Spore\Simulator\cCityWalls.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\CommonIDs.h>

#define cCityPtr intrusive_ptr<Simulator::cCity>

namespace Simulator
{
	// Also used by Tribe
	class UnkCityClass
	{
		char padding[0x64];
	};

	class cVehicle;

	class cCity 
		: public cCommunity
		, public cSpatialObject
		, public cBehaviorList
		, public App::IMessageListener
	{
	public:
		static const uint32_t TYPE = 0xEE9B2232;
		static const uint32_t NOUN_ID = 0x18C43E8;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/// Returns true if the given position is over this city.
		bool IsAboveCity(const Vector3& position);
		Vector3 GetWallsPosition();

		cVehicle* SpawnVehicle(VehiclePurpose speciality, VehicleLocomotion locomotion, struct ResourceKey key, bool isSpaceStage);

	public:
		/* 210h */	string16 field_210;
		/* 220h */	float field_220;
		/* 224h */	int field_224;
		/* 228h */	int field_228;
		// alignment
		/* 230h */	cGonzagoTimer field_230;
		/* 250h */	cGonzagoTimer field_250;
		/* 270h */	cGonzagoTimer field_270;
		/* 290h */	int field_290;  // not initialized
		/* 290h */	int field_294;  // not initialized
		/* 298h */	int field_298;  // intrusive_ptr with release at C0h cSpatialObject/cPlanet
		/* 29Ch */	int field_29C;
		/* 2A0h */	int field_2A0;
		/* 2A4h */	vector<int> field_2A4;
		/* 2B8h */	vector<int> field_2B8;
		/* 2CCh */	int field_2CC;
		/* 2D0h */	int field_2D0;
		/* 2D4h */	char _padding_2D4[0xC];
		/* 2E0h */	bool field_2E0;
		/* 2E1h */	bool field_2E1;
		/* 2E2h */	bool field_2E2;
		/* 2E3h */	bool field_2E3;
		/* 2E4h */	bool field_2E4;
		/* 2E5h */	bool field_2E5;
		/* 2E6h */	bool field_2E6;
		/* 2E8h */	uint32_t mModificationHandleLevel;
		/* 2ECh */	uint32_t mModificationHandleTexture;
		/* 2F0h */	int field_2F0;
		/* 2F4h */	int field_2F4;
		/* 2F8h */	int field_2F8;
		/* 2FCh */	bool field_2FC;
		/* 300h */	int field_300;  // not initialized
		/* 304h */	int field_304;  // not initialized
		/* 308h */	vector<intrusive_ptr<cOrnament>> mCivicObjects;  // cOrnament
		/* 31Ch */	int mHousingAmount;  // not initialized
		/* 320h */	intrusive_ptr<cBuilding> mpCityHall;
		/* 324h */	intrusive_ptr<cCityWalls> mpCityWalls;
		/* 328h */	intrusive_ptr<cCityTerritory> mpCityTerritory;
		/* 32Ch */	Math::Vector3 field_32C;
		/* 338h */	float mFrameRate;  // 10.0
		/* 33Ch */	bool mbIsPlayerCity;  // not initialized
		/* 340h */	vector<intrusive_ptr<cBuilding>> mBuildings;
		/* 354h */	int mTurrets;  // points to _field_36C  // vector<cTurret>
		/* 358h */	int field_358;  // points to _field_36C
		/* 35Ch */	int field_35C;  // points to end of _field_36C
		/* 360h */	int field_360;  // not initialized
		/* 364h */	int field_364;  // points to _field_36C
		/* 368h */	int field_368;  // not initialized
		/* 36Ch */	char _field_36C[0x80];
		/* 3ECh */	UnkCityClass field_3EC;
		/* 450h */	UnkCityClass field_450;
		/* 4B4h */	UnkCityClass field_4B4;
		/* 518h */	bool mbSmallCity;  // true
		/* 519h */	bool field_519;
		/* 51Ch */	int field_51C;  // not initialized
		/* 520h */	int field_520;  // not initialized
		/* 524h */	int field_524;  // not initialized
		/* 528h */	vector<int> field_528;
		/* 53Ch */	float mWaterFraction;
		/* 540h */	int mVehicleSpecialty;  // -1
		/* 544h */	int field_544;  // not initialized
		/* 548h */	vector<int> field_548;
		/* 55Ch */	vector<intrusive_ptr<cCity>> mTradePartners;
		/* 570h */	map<int, int> field_570;
		/* 58Ch */	bool field_58C;
		/* 590h */	intrusive_ptr<Object> mpCivilization;  // PLACEHOLDER cCivilization
		/* 594h */	int mBuildingPlacementAngleDelta;  // 45
		/* 598h */	float mBuildingPlacementRadius;
		/* 59Ch */	int mAngle;
		/* 5A0h */	map<int, int> mAllegianceBucket;
		/* 5BCh */	map<int, int> mAllegianceConversionDeltas;
		/* 5D8h */	map<int, int> mAllegianceUnconversionDeltas;
		/* 5F8h */	cGonzagoTimer field_5F8;
		/* 618h */	vector<int> mCultureTargetInfo;  // tCultureTargetInfo
		/* 62Ch */	vector<int> mCulturalTargets;  // cCulturalTarget
		/* 640h */	int field_640;  // not initialized
		/* 644h */	int field_644;  // not initialized
		/* 648h */	int field_648;  // not initialized
		/* 64Ch */	int mRoboPopulation;
		/* 650h */	int field_650;
		/* 654h */	int field_654;
		/* 658h */	ResourceKey mSpeciesKey;
		/* 664h */	int mMoneyCount;
		/* 668h */	int mHappyCount;
		/* 66Ch */	int mUnhappyCount;
		/* 670h */	int mNewBuildings;
		/* 674h */	int mUnused2;
		/* 678h */	int mFinalIncome;
		/* 67Ch */	int mUnused3;
		/* 680h */	int mUnused4;
		/* 684h */	vector<int> field_684;
		/* 698h */	bool mbPartyOn;
		/* 6A0h */	cGonzagoTimer field_6A0;
		/* 6C0h */	bool mbRiotOn;
		/* 6C8h */	cGonzagoTimer field_6C8;
		/* 6E8h */	cGonzagoTimer field_6E8;
		/* 708h */	cGonzagoTimer field_708;
		/* 728h */	cGonzagoTimer field_728;
		/* 748h */	float mCapturePercent;
		/* 74Ch */	uint32_t mCaptureID;
		/* 750h */	float mConvertPercent;
		/* 754h */	uint32_t mConvertID;
		/* 758h */	float mBuyPercent;
		/* 75Ch */	uint32_t mBuyID;
		/* 760h */	bool mbFirstHarvester;
		/* 761h */	bool field_761;
		/* 762h */	bool mbSkipCaptureCinematic;
		/* 764h */	int field_764;
		/* 768h */	int field_768;
		/* 770h */	cGonzagoTimer mMessiahTimer;
		/* 790h */	cGonzagoTimer field_790;
		/* 7B0h */	int field_7B0;  // not initialized
		/* 7B4h */	int field_7B4;  // not initialized
		/* 7B8h */	map<int, int> field_7B8;
		/* 7D4h */	int field_7D4;
		/* 7D8h */	char _padding_7D8[0x18];
		/* 7F0h */	int field_7F0;
		/* 7F4h */	int mNpcBuildingAlignment;  // not initialized
		/* 7F8h */	vector<int> mDeferredEvents;  // tDeferredEvent
		/* 80Ch */	bool field_80C;
		/* 810h */	int field_810;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cCity) == 0x818, "sizeof(cCity) != 818h");
	static_assert(sizeof(UnkCityClass) == 0x64, "sizeof(UnkCityClass) != 64h");

	namespace Addresses(cCity) 
	{
		DeclareAddress(IsAboveCity);
		DeclareAddress(SpawnVehicle);
	}
}