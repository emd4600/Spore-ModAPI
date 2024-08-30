#pragma once

#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\ResourceKey.h>
#include <EASTL\vector.h>
#include <EASTL\hash_map.h>
#include <EASTL\list.h>
#include <EASTL\fixed_map.h>
#include <EASTL\fixed_vector.h>
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

	constexpr cCollectableItemID COLLECTABLE_ITEM_NULL_ID = { -1, -1 };
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
	typedef eastl::fixed_vector<cCollectableItemID, 4> cCollectableItemsRowVector;
	ASSERT_SIZE(cCollectableItemsRowVector, 56);

	typedef uint64_t cCollectableItemsRowID;

	typedef eastl::map<cCollectableItemsRowID, cCollectableItemsRowVector>::node_type NodeType;
	static_assert(sizeof(NodeType) == 0x50, "");

	inline cCollectableItemsRowID GetCollectableItemsRowID(uint32_t categoryID, int pageIndex, int row) {
		return ((uint64_t)categoryID) << 32 | (pageIndex << 16) | row;
	}

	struct UnkHashtableItem {
		int field_0;
		int field_4;
	};
	ASSERT_SIZE(UnkHashtableItem, 8);
	typedef eastl::sp_fixed_hash_map<Simulator::cCollectableItemID, UnkHashtableItem, 4> UnkHastable;
	ASSERT_SIZE(UnkHastable, 0xDC);

	typedef eastl::sp_fixed_hash_map<int, UnkHastable, 8> UnkHashMap;
	ASSERT_SIZE(UnkHashMap, 0x888);

	class cCollectableItems
		: public ISimulatorSerializable
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x3A3AA3A;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

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

		// called at the start of creature stage with an int of "1" and a nullptr speciesKey
		void sub_597BC0(UnkHashMap& dst, int, const ResourceKey& speciesKey);

		void sub_597390(eastl::vector<int>& dst, struct cCollectableItemID itemID, int);

	public:
		struct UnlockableItem
		{
			/* 00h */	int itemUnlockLevel;
			/* 04h */	float itemUnlockFindPercentage;
			/* 08h */	uint32_t categoryID;
			/* 0Ch */	int column;
			/* 10h */	int row;
			/* 14h */	int pageIndex;
			/* 18h */	uint32_t itemUnlockEffect;
		};
		ASSERT_SIZE(UnlockableItem, 0x1C);
		
#ifndef SDK_TO_GHIDRA
		/* 0Ch */	bool field_C;  // true
		/// Stores a progression of unlockable items (for instance, all the mouths in the same row)
		/* 10h */	eastl::sp_fixed_map<cCollectableItemsRowID, cCollectableItemsRowVector, 64> mUnlockableRows;
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

		DeclareAddress(sub_597BC0);  // 0x597BC0 0x597F00
		DeclareAddress(sub_597390);  // 0x597390 0x5976D0
	}


	class CreatureGamePartUnlocking
	{
	public:
		// Given an (unknown) hashmap (the creature parts one always is size 56),
		// return a valid new part ID to unlock, or call this func again until it returns a valid part.
		// 
		// firstCall is always true ONLY on the first call of this function
		// unlockLevel will be either a .prop unlockLevel value or -1
		// 
		// the cCollectableItemID return value is formatted as such:
		// groupID: category name (eg: ce_category_mouths)
		// instanceID: part placement in category by page index and part row (eg: a part on page 4 and row 5 would have a hex of 0x30004)
		struct cCollectableItemID sub_D3B460(UnkHashMap& unk0, bool firstCall, int unk1, int unlockLevel);
	};

	namespace Addresses(CreatureGamePartUnlocking)
	{
		DeclareAddress(sub_D3B460);  // 0xD3B460 0xD3BF50
	}


	eastl::fixed_vector<eastl::pair<uint32_t, int>, 16>& GetCreatureGameUnlockCategoriesCount();
}

namespace Addresses(Simulator)
{
	DeclareAddress(sCreatureGameUnlockCategoriesCount);  // 0x1587278 0x1583298
}
