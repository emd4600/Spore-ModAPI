#pragma once

#include <Spore\Skinner\cSkinPainterJob.h>
#include <Spore\Graphics\Texture.h>
#include <EASTL\fixed_vector.h>

namespace Skinner
{
	class cSkinPainterPipeline
		: public RefCountTemplate
	{
	public:
		/// A list of all textures used to render the skinpaint, including all rigblock diffuse, tintMask and specBump textures.
		/* 08h */	eastl::fixed_vector<TexturePtr, 192> mTextures;
		/* 320h */	char padding_320[0x330 - 0x320];
		/* 330h */	cSkinPainterJobPtr mpCurrentJob;
		/* 334h */	int field_334;
		/* 338h */	int field_338;  // not initialized
		/* 33Ch */	int mCurrentStage;  // not initialized
		/* 340h */	int field_340;  // not initialized
		/* 344h */	int field_344;  // not initialized
		/* 348h */	bool field_348;  // not initialized
		/* 349h */	bool field_349;  // not initialized
		/* 34Ah */	bool field_34A;  // not initialized
		/* 34Ch */	int field_34C;  // not initialized
	};
	ASSERT_SIZE(cSkinPainterPipeline, 0x350);

	namespace Addresses(cSkinPainterPipeline)
	{
		DeclareAddress(ExecutePipeline);  // 0x51B110 TODO
		DeclareAddress(PreloadTextures);  // 0x51AC90 TODO
		DeclareAddress(Initialize);  // 0x51AAE0 TODO
	}
}