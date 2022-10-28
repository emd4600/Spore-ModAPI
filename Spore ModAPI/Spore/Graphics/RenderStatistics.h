#pragma once

#include <Spore\Internal.h>

namespace Graphics
{
	struct RenderStatistics
	{
		// related with total render time
		/* 00h */	float field_0;
		/* 04h */	float field_4;
		/* 08h */	float field_8;
		/* 0Ch */	float field_C;
		/* 10h */	float field_10;
		/* 14h */	int numLayersRendered;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	int numVerticesRendered;
		/* 24h */	int numIndicesRendered;
		/* 28h */	int numDrawCalls;
	};
	ASSERT_SIZE(RenderStatistics, 0x2C);
}