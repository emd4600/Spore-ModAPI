#pragma once

#include <Spore\MathUtils.h>

namespace Editors
{
	struct cEditorResourceProperties
	{
		/* 00h */	uint32_t mModelType;
		/* 04h */	int mZCorpScore;
		/* 08h */	uint32_t mSkinEffectID1;
		/* 0Ch */	uint32_t mSkinEffectID2;
		/* 10h */	uint32_t mSkinEffectID3;
		/* 14h */	unsigned int mSkinEffectSeed1;
		/* 18h */	unsigned int mSkinEffectSeed2;
		/* 1Ch */	unsigned int mSkinEffectSeed3;
		/* 20h */	Math::ColorRGB mSkinColor1;
		/* 2Ch */	Math::ColorRGB mSkinColor2;
		/* 38h */	Math::ColorRGB mSkinColor3;
		/* 44h */	char padding_48[0x80 - 0x44];
	};
	ASSERT_SIZE(cEditorResourceProperties, 0x80);
}