#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\Texture.h>

namespace Graphics
{
	class cMITextureSet
	{
	public:
		struct Entry
		{
			Texture* mpTexture;
			char field_4[12];  // related with sampler states
		};

		virtual ~cMITextureSet();

		/* 04h */	uint16_t field_4;  // 0x20D, maybe shader data index
		/* 06h */	uint16_t field_6;  // 0x64
		/* 08h */	void* field_8;  // &mEntryCount
		/* 0Ch */	int mEntryCount;
		/* 10h */	Entry mEntries[6];
	};

	ASSERT_SIZE(cMITextureSet::Entry, 0x10);
	ASSERT_SIZE(cMITextureSet, 0x70);
}