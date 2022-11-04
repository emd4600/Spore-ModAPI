#pragma once

#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

namespace Swarm
{
	struct cSurfaceInfo
	{
		enum Flags
		{
			kFlagPin = 2,
			kFlagPinMove = 4,
			kFlagPinEmit = 8,
			kFlagAlign = 0x20,
			kFlagSourceSpace = 0x40,
			kFlagWorldSpace = 0x80
		};

		cSurfaceInfo();

		/* 00h */	int flags;  // & 0x3FFF
		/* 04h */	int field_4;
		/* 08h */	ResourceID surfaceMapID;
		/* 10h */	float bounce;
		/* 14h */	float slide;
		/* 18h */	float collisionRadius;
		/* 1Ch */	float deathProbabilty;
		/* 20h */	float pinOffset;
		/* 24h */	float field_24;
		/* 28h */	float field_28;
		/* 2Ch */	float field_2C;
		/* 30h */	float field_30;
		/* 34h */	float field_34;
		/* 38h */	int collideEffectIndex;
		/* 3Ch */	int deathEffectIndex;
		/* 40h */	eastl::vector<Math::Vector3> surfacePoints;
		/* 54h */	int field_54;
	};
	ASSERT_SIZE(cSurfaceInfo, 0x58);

	inline cSurfaceInfo::cSurfaceInfo()
		:
		flags(0), collideEffectIndex(-1), deathEffectIndex(-1), surfaceMapID(-1, -1),
		collisionRadius(0), deathProbabilty(0), pinOffset(0), field_28(0), field_2C(0), field_30(0),
		bounce(1.0f), slide(1.0f), field_24(-1.0E9), field_34(-1.0E9)
	{
	}
}