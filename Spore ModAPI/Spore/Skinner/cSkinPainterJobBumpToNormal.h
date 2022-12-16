#pragma once

#include <Spore\Skinner\cSkinPainterJob.h>

namespace Skinner
{
	/// Transforms a bump map in skinner texture 0 into a normal map in skinner texture 2.
	/// It does so using the material `0x9E74D163`
	/// Source code: @ref SourceCode-Skinner-cSkinPainterJobBumpToNormal
	class cSkinPainterJobBumpToNormal
		: public cSkinPainterJob
	{
	public:
		virtual bool Execute() override;
	};
	ASSERT_SIZE(cSkinPainterJobBumpToNormal, 0x10);

	namespace Addresses(cSkinPainterJobBumpToNormal)
	{
		DeclareAddress(Execute);  // 0x518E40 TODO
	}
}