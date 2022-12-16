#pragma once

#include <Spore\Skinner\cSkinPainterJob.h>

namespace Skinner
{
	/// Applies the diffuse, bumpSpec and tintMask maps of all rigblocks.
	/// This is separated into multiple stages:
	///  - Stage 0: Loads all the rigblocks diffuse and tintMask textures. Paints the diffuse maps into the
	/// skinner texture 0, blending the current color with the diffuse texture, using the tintMask as the mask.
	///  - Stage 1: Paints the tintMask alpha channel into the skinner texture 0 alpha channel.
	///  - Stage 2: Loads all the rigblocks bumpSpec textures. Paints the skinner texture 1 red channel 
	///  with the specBump textures, using the `0x3815422` material
	///  - Stage 3: Paints the skinner texture 1 blue channel with the specBump textures, using the `0x968E3FFF` material.
	/// Source code: @ref SourceCode-Skinner-cSkinPainterJobApplyPartsTextures
	class cSkinPainterJobApplyPartsTextures
		: public cSkinPainterJob
	{
	public:
		virtual bool Execute() override;
	};
	ASSERT_SIZE(cSkinPainterJobApplyPartsTextures, 0x10);

	namespace Addresses(cSkinPainterJobApplyPartsTextures)
	{
		DeclareAddress(Execute);  // 0x51A490 TODO
	}
}