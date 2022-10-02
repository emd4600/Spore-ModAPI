#pragma once

#include <Spore\MathUtils.h>

namespace Swarm
{
	namespace Components
	{
		struct DistributeEffectMessageData
		{
			struct DistributedObject
			{
				/* 00h */	int field_0;
				/* 04h */	Math::Vector3 position;
				/* 10h */	char padding_10[0x4C - 0x10];
			};
			ASSERT_SIZE(DistributedObject, 0x4C);

			/* 00h */	int count;
			/* 04h */	int field_4;
			/* 08h */	DistributedObject* pObjects;
		};
	}
}