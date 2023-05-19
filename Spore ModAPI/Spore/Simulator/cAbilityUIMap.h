#pragma once

#include <Spore\Internal.h>

namespace Simulator
{
	struct cAbilityUIMap
	{
		struct Entry
		{
			/// Index of the ability within the player cCreatureBase (the avatar, or the tribe chieftain in tribe stage)
			int mIndexInPlayerCreature;  // -1
			bool field_4;
		};
		ASSERT_SIZE(Entry, 8);

		static cAbilityUIMap* Get();

		/* 00h */	Entry mEntries[25];
		/* C8h */	int field_C8;
		/* CCh */	int mMaxNumAbilitiesPerCategory;
		/* D0h */	uint32_t mFirstSocialButtonID;
		/* D4h */	uint32_t mFirstAttackButtonID;
	};
	ASSERT_SIZE(cAbilityUIMap, 0xD8);

	namespace Addresses(cAbilityUIMap)
	{
		DeclareAddress(ptr);  // 0x16A266C TODO
		DeclareAddress(Create);  // 0xD47EA0 TODO
	}
}