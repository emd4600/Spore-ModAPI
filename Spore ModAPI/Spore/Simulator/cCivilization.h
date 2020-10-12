#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cIdentityColorable.h>
#include <Spore\Simulator\cCultureSet.h>
#include <Spore\Simulator\cCity.h>
#include <Spore\Simulator\cVehicle.h>
#include <Spore\Simulator\ICityMusic.h>
#include <Spore\Simulator\cCommodityNode.h>
#include <Spore\Editors\INameableEntity.h>
#include <Spore\App\IMessageListener.h>

#define cCivilizationPtr eastl::intrusive_ptr<Simulator::cCivilization>

namespace Simulator
{
	class cCivilization
		: public cGameData
		, public Editors::INameableEntity
		, public App::IMessageListener
		, public cIdentityColorable
	{
	public:
		static const uint32_t TYPE = 0x901F1362;

		/* 6Ch */	cCultureSet mCultureSet;
		/* 88h */	bool mInitialized;
		/* 89h */	bool mIsPlayerOwned;
		/* 8Ah */	bool mIsNeutral;
		/* 8Bh */	bool mCommNotifiedFirstCityCapture;
		/* 8Ch */	bool mCommNotifiedWarning;
		/* 8Dh */	bool mHasDeveloped;
		/* 8Eh */	bool mAttackedByMilitary;
		/* 8Fh */	bool mAttackedByReligion;
		/* 90h */	bool mSurrendered;
		/* 91h */	bool field_91;
		/* 92h */	bool mTargetMinerals;
		/* 93h */	bool mFirstMinerals;
		/* 94h */	bool mFirstBudget;
		/* 98h */	float mWealth;
		/* 9Ch */	vector<cCityPtr> mCities;
		/* B0h */	vector<cVehiclePtr> mVehicles;
		/* C4h */	ColorRGB mPrimaryColor;
		/* D0h */	uint32_t mCultureId;
		/* D4h */	vector<cSpatialObjectPtr> mSelectableObjectVector;
		/* E8h */	cGonzagoTimer mHumanAttackTimer;
		/* 108h */	cGonzagoTimer mHumanProposeTimer;
		/* 128h */	cGonzagoTimer mProposeRouteTimer;
		/* 148h */	cGonzagoTimer mBuildMilitaryUnitsTimer;
		/* 168h */	cGonzagoTimer mBuildReligionUnitsTimer;
		/* 188h */	cGonzagoTimer mBuildEconUnitsTimer;
		/* 1A8h */	cGonzagoTimer mExpansionMineralTimer;
		/* 1C8h */	cGonzagoTimer mClaimMineralTimer;
		/* 1E8h */	cGonzagoTimer mDemandTimer;
		/* 208h */	cGonzagoTimer mEmbargoTimer;
		/* 228h */	cGonzagoTimer mAllianceTimer;
		/* 248h */	cGonzagoTimer mNemesisTimer;
		/* 268h */	ResourceKey mSpeciesKey;
		/* 274h */	ICityMusicPtr mCityMusic;
		/* 278h */	string16 mName;
		/* 288h */	string16 mDescription;
		/* 298h */	int mVehicleTechLevel;
		/* 29Ch */	int mCommRelPanelSlot;
		/* 2A0h */	uint32_t mCurrentCommEventId;
		/* 2A4h */	cGameDataPtr mpCurrentCommSource;
		/* 2A8h */	cCityPtr mpCurrentCommTargetCity;
		/* 2ACh */	int field_2AC;
		/* 2B0h */	cGonzagoTimer field_2B0;
		/* 2D0h */	int field_2D0;
		/* 2D8h */	cGonzagoTimer field_2D4;
		/* 2F8h */	int field_2F8;
		/* 300h */	cGonzagoTimer field_300;
		/* 320h */	bool field_320;
		/* 328h */	cGonzagoTimer field_328;
		/* 348h */	bool field_348;
		/* 350h */	cGonzagoTimer field_350;
		/* 370h */	bool field_370;
		/* 378h */	cGonzagoTimer field_378;
		/* 398h */	bool field_398;
		/* 3A0h */	cGonzagoTimer field_3A0;
		/* 3C0h */	bool field_3C0;
		/* 3C8h */	cGonzagoTimer field_3C8;
		/* 3E8h */	bool field_3E8;
		/* 3F0h */	cGonzagoTimer field_3F0;
		/* 410h */	map<cCityPtr, float> mDistanceToCityMap;
		/* 42Ch */	int field_42C;
		/* 430h */	bool field_430;
		/* 431h */	bool field_431;
		/* 434h */	int field_434;  // -1
		/* 438h */	int field_438;
		/* 43Ch */	int field_43C;  // -1
		/* 440h */	int field_440;
		/* 444h */	int field_444;
		/* 448h */	float field_448;
		/* 44Ch */	int field_44C;
		/* 450h */	int field_450;  // -1
		/* 454h */	int field_454;
		/* 458h */	cCityPtr mMilitaryExpansionCity;
		/* 45Ch */	cCityPtr mReligiousExpansionCity;
		/* 460h */	cCityPtr mDiploAttackCity;
		/* 464h */	cCommodityNodePtr mExpansionMineral;
		/* 468h */	cCommodityNodePtr mClaimMineral;
		/* 46Ch */	cCivilizationPtr mNemesisCiv;
		/* 470h */	vector<DefaultRefCounted> field_470;
		/* 484h */	int field_484;
		/* 488h */	int field_488;
		/* 48Ch */	int field_48C;
		/* 490h */	vector<cGonzagoTimer> mSuperweaponCooldown;
		/* 4A4h */	ObjectPtr field_4A4;
		/* 4A8h */	int field_4A8;  // -1
		/* 4ACh */	float mDomesticBudget;
		/* 4B0h */	float mExpansionBudget;
		/* 4B4h */	int mUpdateMoneyCount;
		/* 4B8h */	int mForceMinDiploCount;
		/* 4BCh */	int field_4BC;  // not initialized
		/* 4C0h */	int mMilitaryCaptureCount;
		/* 4C4h */	int mReligiousCaptureCount;
		/* 4C8h */	int mEconomicCaptureCount;
		/* 4CCh */	bool mbLauncedIWinWeapon;
		/* 4D0h */	int mHighestCityCount;


		// /* 4Ch */	virtual uint32_t GetPoliticalID() const;

		// 0xBF16F0 float GetVehicleCost(VehiclePurpose speciality) const;
		// 0xBEEC50 float GetMoney() const;

		// related with comm events:
		// 0x901F1362 source civilization
		// 0xEE9B2232 source city
	};
	ASSERT_SIZE(cCivilization, 0x4D8);
}