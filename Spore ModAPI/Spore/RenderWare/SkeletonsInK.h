#pragma once

#include <Spore\RenderWare\Skeleton.h>
#include <Spore\RenderWare\CompiledState.h>

namespace RenderWare
{
	struct SkeletonsInK
	{
		/* 00h */	void* field_0;
		/* 04h */	void* field_4;  // function
		/* 08h */	CompiledState* mpStates;
		/* 0Ch */	void* field_C;
		/* 10h */	Skeleton* mpSkeleton;
		/* 14h */	int mStatesCount;

		static const uint32_t TYPE = 0x7000B;
	};
}