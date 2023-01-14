#pragma once

#include <Spore\Skinner\cSkinPainterJob.h>

namespace Skinner
{
	class cSkinPainterJobApplyBrushes
		: public cSkinPainterJob
	{
	public:
		virtual bool Execute() override;

	public:
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
		/* 2Ch */	bool field_2C;
	};
	ASSERT_SIZE(cSkinPainterJobApplyBrushes, 0x30);

	namespace Addresses(cSkinPainterJobApplyBrushes)
	{
		DeclareAddress(Execute);  // 0x518440 0x518310
	}
}