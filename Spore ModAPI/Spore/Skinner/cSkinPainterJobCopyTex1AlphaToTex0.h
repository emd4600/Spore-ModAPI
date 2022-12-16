#pragma once

#include <Spore\Skinner\cSkinPainterJob.h>

namespace Skinner
{
	/// Copies the alpha channel of skinner texture 1 into the alpha channel of skinner texture 0.
	/// Source code: @ref SourceCode-Skinner-cSkinPainterJobCopyTex1AlphaToTex0
	class cSkinPainterJobCopyTex1AlphaToTex0
		: public cSkinPainterJob
	{
	public:
		virtual bool Execute() override;
	};
	ASSERT_SIZE(cSkinPainterJobCopyTex1AlphaToTex0, 0x10);

	namespace Addresses(cSkinPainterJobCopyTex1AlphaToTex0)
	{
		DeclareAddress(Execute);  // 0x518D40 TODO
	}
}