#pragma once

#include <Spore\Skinner\cSkinnerTexture.h>

namespace Skinner
{
	class cSkinPainter
	{
	public:
		void CreateTextures(int textureSize);

	public:

		/* 10h */	cSkinnerTexture* mpDiffuse;
		/* 14h */	cSkinnerTexture* mpSpecBump;
		/* 18h */	cSkinnerTexture* field_18;
		/* 1Ch */	int mTextureSize;
		/* 20h */	float mGloss;
		/* 24h */	float mPhong;
		/* 28h */	float mSpecExp;
		/* 2Ch */	float mPartBumpScale;
		/* 30h */	float mPartSpecScale;
	};

	namespace Addresses(cSkinPainter)
	{
		DeclareAddress(CreateTextures);  // 0x5061D0
	}
}