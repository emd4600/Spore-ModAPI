#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\Texture.h>

namespace Graphics
{
	class cShaderDataTextureSet
	{
		struct Entry
		{
			Texture* mpTexture;
			char field_4[12];  // related with sampler states
		};
		ASSERT_SIZE(Entry, 0x10);

		/* 00h */	int mEntryCount;
		/* 04h */	Entry mEntries[6];
	};

	class cMITextureSet
	{
	public:

		virtual ~cMITextureSet();

		/* 04h */	uint16_t mShaderDataIndex;  // 0x20D, maybe shader data index
		/* 06h */	uint16_t mShaderDataSize;  // 0x64
		/* 08h */	cShaderDataTextureSet* mShaderData;  // &mEntryCount
		/* 0Ch */	cShaderDataTextureSet mData;
	};

	ASSERT_SIZE(cMITextureSet, 0x70);
}