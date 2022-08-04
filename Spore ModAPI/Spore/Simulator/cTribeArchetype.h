#pragma once

#include <Spore\App\PropertyList.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

namespace Simulator
{
	/// Represents a type of tribe, with its configuration stored in folder `TribeArchetypes`.
	struct cTribeArchetype
	{
		/// Returns the archetype that corresponds to the given ID, which is equal to the archetype `ArcheType` property.
		/// Archetypes are stored in the `TribeArchetypes` folder. This function only considers valids `archetype` values
		/// less or equal to 30; otherwise, it returns a default archetype.
		/// @param archetype
		/// @returns
		static cTribeArchetype* GetTribeArchetype(uint32_t archetype);

		/* 00h */	int mInitialPopulation;
		/* 04h */	int mInitialFood;
		/* 08h */	int mMaxPopulation;
		/* 0Ch */	int mToolPrefs[16];
		/* 4Ch */	int mNumToolPrefs;
		/// ID of a file in folder `herdtypes~` (`0x02F98B67`)
		/* 50h */	uint32_t mCreatureArchetype;
		/* 54h */	float field_54;
		/// Property `0x80A52AC0`
		/* 58h */	float field_58;
		/// Property `0xD5291551`
		/* 5Ch */	float field_5C;
		/// Property `0x58A47B38`
		/* 60h */	float field_60;
		/// Property `0x27DF57BE`
		/* 64h */	float field_64;
		/// Property `0xAC245F82`
		/* 68h */	float field_68;
		/// Property `0x2DF9A743`
		/* 6Ch */	float field_6C;
		/// Property `0xF74C0EB9`
		/* 70h */	float field_70;
		/// Property `0xA3102906`
		/* 74h */	float field_74;
		/// Property `0x2B793112`
		/* 78h */	float field_78;
		/* 7Ch */	float field_7C;
		/* 80h */	float field_80;
		/* 84h */	float field_84;
		/* 88h */	float field_88;
		/// Property `0x982C7059`
		/* 8Ch */	int field_8C;
		/// Property `0xE0BE991F`
		/* 90h */	float field_90;
		/// Property `0x1570506E`
		/* 94h */	float field_94;
		/// Property `0xD164F429`
		/* 98h */	Math::Vector2 field_98;
		/// Property `0xA9A2D5E0`
		/* A0h */	eastl::vector<int> field_A0;
		/* B4h */	PropertyListPtr mpPropList;
	};
	ASSERT_SIZE(cTribeArchetype, 0xB8);

	namespace Addresses(cTribeArchetype)
	{
		DeclareAddress(GetTribeArchetype);  // 0xC8E060 0xC8EC00
	}
}
