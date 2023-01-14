#pragma once

#include <Spore\Skinner\cSkinPainterJob.h>

namespace Skinner
{
	class cSkinPainterJobColorDilateRepeat
		: public cSkinPainterJob
	{
	public:
		virtual bool Execute() override;

	public:
		/* 10h */	int field_10;
		/* 14h */	int mNumSteps;  // 8
		/* 18h */	int field_18;
	};
	ASSERT_SIZE(cSkinPainterJobColorDilateRepeat, 0x1C);

	namespace Addresses(cSkinPainterJobColorDilateRepeat)
	{
		DeclareAddress(Execute);  // 0x518510 0x5183E0
	}
}