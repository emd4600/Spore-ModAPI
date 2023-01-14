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
		/// The pipeline is executed as follows (the numbers are the stage index):
		/// 0. Nothing
		/// 1. Nothing
		/// 2. Checks some values
		/// 3. cSkinPainterJobApplyBrushes
		/// 4. cSkinPainterJobPaintParts
		/// 5. Checks some values
		/// 6. cSkinPainterJobAmbientOcclusion
		/// 7. cSkinPainterJobColorDilateRepeat (field_10=0, field_14=8)
		/// 8. cSkinPainterJobColorDilateRepeat (field_10=1, field_14=8)
		/// 9. cSkinPainterJobCopyTex1AlphaToTex0
		/// 10. cSkinPainterJobCopyRigblocksTintMaskAlpha
		/// 11. cSkinPainterJobExtractTexture (with texture 0)
		/// 12. cSkinPainterJobBumpToNormal
		/// 13. cSkinPainterJobExtractTexture (with texture 2)
		void ExecutePipeline();

		void PreloadTextures(bool);

		void Initialize();

	public:
		/// A list of all textures used to render the skinpaint, including all rigblock diffuse, tintMask and specBump textures.
		/* 08h */	eastl::fixed_vector<TexturePtr, 192> mTextures;
		/* 320h */	uint32_t mTextureInstanceID;  // not initialized
		/* 324h */	uint32_t mTextureGroupID;  // not initialized
		/* 328h */	uint32_t field_328;  // not initialized
		/* 32Ch */	int field_32C;  // not initialized
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
		DeclareAddress(ExecutePipeline);  // 0x51B110 0x51AFE0
		DeclareAddress(PreloadTextures);  // 0x51AC90 0x51AB60
		DeclareAddress(Initialize);  // 0x51AAE0 0x51A9B0
	}
}