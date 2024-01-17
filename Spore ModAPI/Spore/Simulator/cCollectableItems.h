#pragma once

#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\ResourceKey.h>
#include <EASTL\vector.h>
#include <EASTL\hash_map.h>
#include <EASTL\list.h>
#include <EASTL\fixed_hash_set.h>
#include <EASTL\fixed_hash_map.h>


#define cCollectableItemsPtr eastl::intrusive_ptr<Simulator::cCollectableItems>

namespace Simulator
{
	enum class CollectableItemStatusFlags : uint8_t
	{
		Unlocked = 1,

		// NotUnlockable = 4 ???
	};

	struct alignas(8) cCollectableItemID {
		uint32_t instanceID;
		uint32_t groupID;
	};
}

#ifndef SDK_TO_GHIDRA
namespace eastl
{
	/// A necessary structure to be able to use cCollectableItemID on containers such as hash_map.
	template <> struct hash<Simulator::cCollectableItemID>
	{
		size_t operator()(const Simulator::cCollectableItemID& val) const { return static_cast<size_t>(val.instanceID); }
	};
}
#endif

namespace Simulator
{
	class cCollectableItems
		: public ISimulatorSerializable
		, public DefaultRefCounted
	{
	public:
		void LoadConfig(uint32_t configGroupID, uint32_t configInstanceID, uint32_t itemsGroupID);

		void AddUnlockableItem(uint32_t instanceID, uint32_t groupID, int itemUnlockLevel, uint32_t categoryID, int row, int column, int pageIndex, float itemUnlockFindPercentage, uint32_t itemUnlockEffect);

		/// Reads the prop file, checks the `itemUnlockLevel`, `itemUnlockEffect` and `itemUnlockFindPercentage` properties, and calls AddUnlockableItem().
		/// If itemUnlockFindPercentage is greater or equal than 1, it unlocks the item.
		/// @param key
		/// @param categoryID
		/// @param row
		/// @param column
		/// @param pageIndex
		bool AddUnlockableItemFromProp(struct ResourceKey key, uint32_t categoryID, int row, int column, int pageIndex);

	public:
		struct UnlockableItem
		{
			/* 00h */	int itemUnlockLevel;
			/* 04h */	float itemUnlockFindPercentage;
			/* 08h */	uint32_t categoryID;
			/* 0Ch */	int row;
			/* 10h */	int column;
			/* 14h */	int pageIndex;
			/* 18h */	uint32_t itemUnlockEffect;
		};
		ASSERT_SIZE(UnlockableItem, 0x1C);
		
#ifndef SDK_TO_GHIDRA
		/* 0Ch */	bool field_C;  // true
		/* 10h */	char field_10[0x147C];  // some fixed_ structure of vector<pair<int, int>>?
		/* 148Ch */	eastl::sp_fixed_hash_map<cCollectableItemID, UnlockableItem, 256> mUnlockableItems;
		/// Some flags
		/* 4D00h */	eastl::sp_fixed_hash_map<cCollectableItemID, uint8_t, 256> mItemStatusInfos;
		/* 6D5Ch */	eastl::vector<int> mUnlocksPerLevel;
		/* 6D70h */	int mUnlockPoints;
		/* 6D74h */	uint32_t mItemsGroupID;
		/* 6D78h */	float mFindPercentageLevelMultiplier;  // 1.0
		/* 6D7Ch */	float mGlobalFindPercentageMultiplier;  // 1.0
		/* 6D80h */	eastl::list<cCollectableItemID> mUnlockedItems;
		/* 6D8Ch */	eastl::hash_map<int, int> field_6D8C;
#else
		// SDKtoGHIDRA does not support sp_fixed_ structures with alignment 8
		/* 0Ch */	bool field_C;  // true
		/* 10h */	char field_10[0x147C];  // some fixed_ structure of vector<pair<int, int>>?
		/* 148Ch */	eastl::hash_map<cCollectableItemID, UnlockableItem> mUnlockableItems;
		/* 14ACh */	char _mUnlockableItems__fixed_pool[0x4D00 - 0x14AC];
		/* 4D00h */	eastl::hash_map<cCollectableItemID, uint8_t> mItemStatusInfos;
		/* 4D20h */	char _mItemStatusInfos__fixed_pool[0x6D5C - 0x4D20];
		/* 6D5Ch */	eastl::vector<int> mUnlocksPerLevel;
		/* 6D70h */	int mUnlockPoints;
		/* 6D74h */	uint32_t mItemsGroupID;
		/* 6D78h */	float mFindPercentageLevelMultiplier;  // 1.0
		/* 6D7Ch */	float mGlobalFindPercentageMultiplier;  // 1.0
		/* 6D80h */	eastl::list<cCollectableItemID> mUnlockedItems;
		/* 6D8Ch */	eastl::hash_map<int, int> field_6D8C;
#endif
	};
	ASSERT_SIZE(cCollectableItems, 0x6DAC);

	namespace Addresses(cCollectableItems)
	{
		DeclareAddress(LoadConfig);  // 0x599100 0x599440
		DeclareAddress(AddUnlockableItem);  // 0x598A70 0x598DB0
		DeclareAddress(AddUnlockableItemFromProp);  // 0x598B50 0x598E90
	}



	// eastl::fixed_vector<eastl::pair<>
}
