#pragma once

#include <Spore\Skinner\cSkinPainterJob.h>

namespace Skinner
{
	class cSkinPainterJobAmbientOcclusion
		: public cSkinPainterJob
	{
	public:
		virtual bool Execute() override;
	};
	ASSERT_SIZE(cSkinPainterJobAmbientOcclusion, 0x10);

	namespace Addresses(cSkinPainterJobAmbientOcclusion)
	{
		DeclareAddress(Execute);  // 0x519050 0x518F20
	}
}
