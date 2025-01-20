#pragma once

#include <Spore\Simulator\cCreatureAbility.h>
#include <Spore\LocalizedString.h>
#include <Spore\ResourceKey.h>
#include <EASTL\array.h>

namespace Simulator
{
	class cTribeToolData
	{
	public:
		/* 00h */	ResourceKey mFileKey;
		/// One in TribeToolType
		/* 0Ch */	int mToolType;
		/// One in TribeToolClass
		/* 10h */	int mToolClass;
		/* 14h */	ResourceKey mRackModelKey;
		/* 20h */	uint32_t mToolIconID;
		/* 24h */	cCreatureAbilityPtr mToolAbility;
		/* 28h */	uint32_t mDefaultToolIdleAnim;
		/* 2Ch */	uint32_t mLookaroundToolIdleAnim;
		/* 30h */	uint32_t mGrasperOverlay;
		/* 34h */	uint32_t mEnRouteAnim;
		/* 38h */	int mPrice;
		/* 3Ch */	int mMaxNumSlots;
		/* 40h */	float mToolHealth;
		/* 44h */	ResourceKey mToolDamageHiKey;
		/* 50h */	ResourceKey mToolDamageMdKey;
		/* 5Ch */	ResourceKey mToolDamageLoKey;
		/* 68h */	LocalizedString mName;
	};
	ASSERT_SIZE(cTribeToolData, 0x7C);

	/// Reads the .prop files in `tribe_tools~` and creates the cTribeToolData instances for them,
	/// adding them to the GetTribeToolDataArray() array.
	void LoadTribeToolsData();

	/// Returns the array with the base game tribe tools data. The index for each tool is its tool type,
	/// e.g. index 0 is kTribeToolTypeNone, index 1 is kTribeToolTypeAttack1, etc
	eastl::array<cTribeToolData*, 12> GetTribeToolDataArray();

	/// Returns the cTribeToolData for the given tool type (TribeToolType)
	/// @param toolType
	/// @returns
	cTribeToolData* GetTribeToolData(int toolType);

	/// Called on cSimulatorSystem::Dispose(), deletes the objects in the tribe tool data array.
	void DisposeTribeToolsData();
}

namespace Addresses(Simulator) {
	DeclareAddress(LoadTribeToolsData);  // 0xC9D7F0 0xC9DFE0
	DeclareAddress(sTribeToolDataArray_ptr);  // 0x169DC94 0x1699A14
	DeclareAddress(GetTribeToolData);  // 0xC9C860 0xC9D050
	DeclareAddress(DisposeTribeToolsData);  // 0xC9DED0 0xC9E6C0
}