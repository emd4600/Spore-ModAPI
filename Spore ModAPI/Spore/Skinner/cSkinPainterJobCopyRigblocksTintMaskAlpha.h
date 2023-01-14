#pragma once

#include <Spore\Skinner\cSkinPainterJob.h>

namespace Skinner
{
	/// Copies the alpha channel of all rigblocks tint mask texture into the alpha channel texture 0.
	class cSkinPainterJobCopyRigblocksTintMaskAlpha
		: public cSkinPainterJob
	{
	public:
		virtual bool Execute() override;

	public:
		/* 10h */	int mRigblockIndex;
	};
	ASSERT_SIZE(cSkinPainterJobCopyRigblocksTintMaskAlpha, 0x14);

	namespace Addresses(cSkinPainterJobCopyRigblocksTintMaskAlpha)
	{
		DeclareAddress(Execute);  // 0x51A490 0x51A360
	}
}