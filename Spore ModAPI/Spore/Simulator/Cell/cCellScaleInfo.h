#pragma once

#include <Spore\Simulator\Cell\cCellObjectData.h>

namespace Simulator
{
	namespace Cell
	{
		struct cCellScaleInfo
		{
			/* 00h */	CellStageScale scale;
			/* 04h */	int requiredFood;
			/* 08h */	int field_8;
			/* 0Ch */	float field_C;
			/* 10h */	float field_10;
			/* 14h */	void* field_14;
			/* 18h */	float field_18;
		};
		ASSERT_SIZE(cCellScaleInfo, 0x1C);
	}
}