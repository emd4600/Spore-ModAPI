#pragma once

#include <Spore\Simulator\cObjectPool.h>
#include <Spore\MathUtils.h>

namespace Simulator
{
	namespace Cell
	{
		struct cCellQueryEntry
		{
			/* 00h */	Math::Vector3 mPosition;
			/* 0Ch */	float mCellSize;
			/* 10h */	int field_10;
			/* 14h */	cCellQueryEntry* mpNext;
			/* 18h */	cObjectPoolIndex mCellIndex;
		};
		ASSERT_SIZE(cCellQueryEntry, 0x1C);

		struct cCellQueryLinkedPoolData
		{
			/* 00h */	int mNumObjects;
			/* 04h */	int field_4;
			/* 08h */	int field_8;
			/* 0Ch */	cCellQueryEntry* mpData;
			/* 10h */	int mObjectSize;
			/* 14h */	int mMaxObjects;
		};
		ASSERT_SIZE(cCellQueryLinkedPoolData, 0x18);

		/// Class used to quickly query cell positions.
		struct cCellQueryLinkedPool
			: public cObjectPoolClass
		{
			// E873E0 is update function that moves from mpToAddNextNode to mpNextNode?
			/* 04h */	cCellQueryLinkedPoolData* mpData;
			/* 08h */	cCellQueryEntry* mpNextNode;
			/* 0Ch */	cCellQueryEntry* mpToAddNextNode;
		};
		ASSERT_SIZE(cCellQueryLinkedPool, 16);
	}
}