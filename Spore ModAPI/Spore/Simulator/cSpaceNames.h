#pragma once

#include <Spore\Internal.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <EASTL\map.h>

#define SpaceNames (*Simulator::cSpaceNames::Get())

namespace Simulator
{
	using namespace eastl;

	/// Class to generate names (for creatures, planets, etc.), for example:
	/// `auto name = SpaceNames.GenerateRandomName(Simulator::SpaceNamesType::kPlanet);`
	class cSpaceNames
	{
	public:
		static cSpaceNames* Get();

		string16 GenerateRandomName(SpaceNamesType type);

	public:
		/* 00h */	vector<string16> mPlanetNames;
		/* 14h */	vector<string16> mStarNames;
		/* 28h */	vector<string16> mBlackHoleNames;
		/* 3Ch */	vector<string16> mCreatureNames;
		/* 50h */	vector<string16> mTribeNames;
		/* 64h */	vector<string16> mCityNames;
		/* 78h */	vector<string16> mVehicleNames;
		/* 8Ch */	vector<string16> mBuildingNames;
		/* A0h */	vector<int> field_A0;
		/* B4h */	vector<int> field_B4;
		/* C8h */	vector<int> field_C8;
		/* DCh */	vector<int> field_DC;
		/* F0h */	vector<int> field_F0;
		/* 104h */	vector<int> field_104;
		/* 118h */	vector<int> field_118;
		/* 12Ch */	vector<int> field_12C;
		/* 140h */	vector<int> field_140;
		/* 154h */	vector<int> field_154;
		/* 168h */	vector<int> field_168;
		/* 17Ch */	vector<int> field_17C;
		/* 190h */	vector<int> field_190;
		/* 1A4h */	vector<int> field_1A4;
		/* 1B8h */	vector<int> field_1B8;
		/* 1CCh */	vector<int> field_1CC;
		/* 1E0h */	vector<int> field_1E0;
		/* 1F4h */	vector<int> field_1F4;
		/* 208h */	vector<int> field_208;
		/* 21Ch */	vector<int> field_21C;
		/* 230h */	vector<int> field_230;
		/* 244h */	bool mCreateRandomNames;  // not initialized
		/* 248h */	int field_248;  // 5
		/* 24Ch */	int field_24C;  // 10
		/* 250h */	int field_250;  // not initialized
		/* 254h */	int field_254;  // not initialized
		/* 258h */	int field_258;
		/* 25Ch */	int field_25C;
		/* 260h */	char padding_260[0x3B8 - 0x260];
		/* 3B8h */	bool mHasPlanetNames;
		/* 3B9h */	bool mHasStarNames;
		/* 3BAh */	bool mHasBlackHoleNames;
		/* 3BBh */	bool mHasCreatureNames;
		/* 3BCh */	bool mHasTribeNames;
		/* 3BDh */	bool mHasCityNames;
		/* 3BEh */	bool mHasVehicleNames;
		/* 3BFh */	bool mHasBuildingNames;
		/* 3C0h */	char padding_3C0[0x3DC - 0x3C0];
		/* 3DCh */	map<char16_t, int> mExactlyOneOf;
		/* 3F8h */	vector<string16> mDuplicateSuffixes;
	};
	ASSERT_SIZE(cSpaceNames, 0x40C);

	namespace Addresses(cSpaceNames)
	{
		DeclareAddress(Get);  // 0x4010A0, 0x4010A0
		DeclareAddress(GenerateRandomName);  // 0x5ECD40, 0x5ED000
	}
}
