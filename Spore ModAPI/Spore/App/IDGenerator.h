#pragma once

#include <Spore\ResourceKey.h>
#include <EASTL\map.h>

#define IDGenerator (*App::cIDGenerator::Get())

namespace App
{
	class cIDGenerator
	{
	public:
		static cIDGenerator* Get();

		/* 00h */	virtual ~cIDGenerator();

		/// Generates a ResourceKey that uses the given type ID, autogenerating an instance ID
		/// that does not conflict with any existing file. The group ID is calculated from all the other parameters like this:
		/// `highBits|0x40 poolID lowBits8 lowBits0`, from highest to lowest bits.
		/// `poolID` determines the "generation pool" where instance IDs are generated (there is one for creatures, one for planets, etc).
		/// @param typeID
		/// @param poolID
		/// @param highBits
		/// @param lowBits8
		/// @param lowBits0
		/// @returns
		/* 04h */	virtual void Generate(ResourceKey& dst, uint32_t typeID, uint8_t poolID, uint8_t highBits, uint8_t lowBits8, uint8_t lowBits0);

		/// Generates a ResourceKey that uses the given type and group IDs, autogenerating an instance ID
		/// that does not conflict with any existing file. The group ID masked with `0x00ff0000` determines
		/// the "generation pool" where instance IDs are generated (there is one for creatures, one for planets, etc).
		/// @param typeID
		/// @param groupID
		/// @returns
		/* 08h */	virtual void GenerateForGroup(ResourceKey& dst, uint32_t typeID, uint32_t groupID);

	public:
		/* 04h */	int field_4;  // time?
		/* 08h */	eastl::map<int, int> field_8;
		/* 28h */	eastl::map<int, int> field_24;
	};
	ASSERT_SIZE(cIDGenerator, 0x40);

	namespace Addresses(cResourceKeyGenerator)
	{
		DeclareAddress(Get);  // 0x67DF80, 0x67DE20
	}
	namespace Addresses(cIDGenerator)
	{
		DeclareAddress(Get);  // 0x67DF80, 0x67DE20
	}
}