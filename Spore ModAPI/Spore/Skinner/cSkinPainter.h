#pragma once

#include <Spore\Skinner\cSkinnerTexturePainter.h>
#include <Spore\RenderWare\VertexDescription.h>
#include <Spore\RenderWare\VertexBuffer.h>
#include <Spore\Object.h>

namespace Skinner
{
	class cSkinPainter
		: public RefCountTemplate
	{
	public:
		void CreateTextures(int textureSize);

	public:
		/* 08h */	void* field_8;
		/* 0Ch */	void* field_C;
		/* 10h */	cSkinnerTexturePainter* mpTexture0;
		/* 14h */	cSkinnerTexturePainter* mpTexture1;
		/* 18h */	cSkinnerTexturePainter* mpTexture2;  // normal map?
		/* 1Ch */	int mTextureSize;
		/* 20h */	float mGloss;  // 0.5
		/* 24h */	float mPhong;  // 1.0
		/* 28h */	float mSpecExp;  // 20.0
		/* 2Ch */	float mPartBumpScale;  // 1.0
		/* 30h */	float mPartSpecScale;  // 1.0
		/* 34h */	RenderWare::VertexDescriptionBase* mpVertexDesc;  // V2FC4BC4BT2FT1F
		/* 38h */	RenderWare::VertexBuffer* mpVertexBuffer;
		/* 3Ch */	char padding_3C[0x414 - 0x3C];
	};
	ASSERT_SIZE(cSkinPainter, 0x414);

	namespace Addresses(cSkinPainter)
	{
		DeclareAddress(CreateTextures);  // 0x5061D0 0x506630
	}
}