#pragma once

#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cSpaceInventoryItem.h>
#include <Spore\Simulator\cPlanetRecord.h>
#include <Spore\App\IMessageListener.h>
#include <EASTL\map.h>
#include <EASTL\vector.h>
#include <EASTL\fixed_vector.h>

// Check Simulator::cSpaceTrading
#define SpaceTrading (*Simulator::cSpaceTrading::Get())
#define cNPCStorePtr eastl::intrusive_ptr<Simulator::cNPCStore>

namespace Simulator
{
	class cNPCStore
		: public RefCountTemplate
		, public ISimulatorSerializable
	{
	public:
		static const uint32_t TYPE = 0x5B82EF9;
		static const uint32_t NOUN_ID = 0x5B82EFA;

	public:
		/* 0Ch */	uint32_t planetkey;  // -1
		/* 10h */	cGonzagoTimer lifetime;
		/* 30h */	int spiceBought;
		/* 34h */	eastl::vector<cSpaceInventoryItemPtr> mNPCInventory;
		/* 48h */	eastl::vector<cGonzagoTimer> mNPCInventoryAges;
		/// If true, this store is not valid anymore and must be refreshed
		/* 5Ch */	bool mbDirty;
		/* 60h */	eastl::fixed_vector<ResourceKey, 3> mSpiceID;
		/* 9Ch */	eastl::fixed_vector<int, 3> mSpiceCost;
	};
	ASSERT_SIZE(cNPCStore, 0xC0);

	/// Singleton class for everything related to space stage trading, such as obtaining tradable items
	/// or generating NPC stores. This class manages the objects in the GroupIDs::SpaceTrading_ folder.
	/// Example usage:
	/// ```cpp
	/// // Get 3 red spice
	/// SpaceTrading.ObtainTradingObject({ id("spice1"), TypeIDs::prop, GroupIDs::SpaceTrading_ }, 3);
	/// ```
	class cSpaceTrading
		/* 00h */	: public cStrategy
		/* 1Ch */	, public App::IMessageListener
	{
	public:
		static cSpaceTrading* Get();

		void ClearNPCStores();

		/// Returns true if the space trading item configuration in `spacetrading~` folder
		/// has its `spaceTradingType` set to `rare`.
		/// @param key Key of the trading item, only the instance ID is used
		/// @returns True if the item is rare
		static bool IsRare(const ResourceKey& key);

		/// Gives the specified trading object to the player, adding it to its inventory. 
		/// The key must be a `.prop` file in GroupIDs::SpaceTrading_ group.
		/// If the item is a rare, it will show an event log, give a badge if necessary, and emit the SimulatorMessages::kMsgSpaceRareFound message.
		/// @param key The key of the item
		/// @param amount Quantity to give
		void ObtainTradingObject(const ResourceKey& key, int amount = 1);

		/// Assigns the spice of a planet; if the planet already has a spice, it will only recalculate it if `forceReassign` is true.
		/// The function checks all the spices in cSpaceTrading::mSpices, and picks one based on the probabilities and the planet 
		/// type and difficulty (blue orbit on easy, red orbit on hard, etc.). It then sets the cPlanetRecord::mSpiceGen key.
		/// @param planetRecord
		/// @param forceReassign [Optional] If this is true, it will assign a new spice even if the planet already had one.
		void AssignPlanetSpice(cPlanetRecord* planetRecord, bool forceReassign = false);

		/// Returns whether the given rare has been discovered yet or not.
		/// @param key
		int GetRareHasBeenFound(const ResourceKey& key);

		/// Marks whether the given rare has been found or not. If found is true, it will emit a message.
		/// @param key
		/// @param found
		void SetRareAsFound(const ResourceKey& key, bool found);

		/// Generates what the NPC sells and buys from the player; called when the player enters the store communication screen.
		/// @param planetRecord Current planet where the player is trading
		/// @param[out] dstSpiceText
		void GenerateNPCStore(cPlanetRecord* planetRecord, LocalizedString& dstSpiceText);

	public:
		struct RareGroup {
			/* 00h */	uint32_t mGroupID;
			/* 04h */	int field_4;
			/* 08h */	int field_8;
			/* 0Ch */	int field_C;
			/* 10h */	eastl::vector<ResourceKey> mRares;
		};
		ASSERT_SIZE(RareGroup, 0x24);

		/// List of possible spices for planets
		/* 20h */	eastl::vector<ResourceKey> mSpices;
		/* 34h */	eastl::vector<ResourceKey> field_34;
		/* 48h */	eastl::fixed_vector<cNPCStorePtr, 5> mNPCStore;
		/* 74h */	eastl::vector<ObjectPtr> field_74;
		/* 88h */	eastl::vector<ObjectPtr> field_88;
		/* 9Ch */	int mLastNPCStoreIndex;  // not initalized
		/// When a rare is found, it's key is set to 1 in this map
		/* A0h */	eastl::map<ResourceKey, uint32_t> mRareMap;
		/* BCh */	eastl::vector<RareGroup> mRareGroups;
		/* D0h */	int field_D0[5];  //TODO
		/* E4h */	eastl::vector<uint32_t> mNewlyAvailableCommodities;
	};
	ASSERT_SIZE(cSpaceTrading, 0xF8);

	namespace Addresses(cSpaceTrading)
	{
		DeclareAddress(Get);  // 0xB3D330 0xB3D4D0
		DeclareAddress(ClearNPCStores);  // 0x103E9D0 0x103DCD0
		DeclareAddress(IsRare);  // 0x103B3B0 0x103A3D0
		DeclareAddress(ObtainTradingObject);  // 0x1040890 0x103FC20
		DeclareAddress(AssignPlanetSpice);  // 0x103D750 0x103CA50
		DeclareAddress(GetRareHasBeenFound);  // 0x103BC30 0x103AC50
		DeclareAddress(SetRareAsFound);  // 0x1040820 0x103FBB0
		DeclareAddress(GenerateNPCStore);  // 0x103F560 0x103E8F0
	}
}