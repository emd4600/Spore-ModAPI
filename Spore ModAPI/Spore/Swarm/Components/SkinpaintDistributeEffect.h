#pragma once

#include <Spore\Swarm\Components\cDescription.h>
#include <Spore\Swarm\IComponent.h>
#include <Spore\MathUtils.h>
#include <Spore\resourceID.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

namespace Swarm
{
	class cSkinpaintDistributeDescription
		: public cDescription
	{
	public:
		/* 08h */	eastl::string field_8;
		/* 18h */	int particleIndex;
		/* 1Ch */	float spacing;
		/* 20h */	int distributeLimit;
		/* 24h */	int region;
		/* 28h */	float regionBack;
		/* 2Ch */	float regionBelly;
		/* 30h */	float regionBodyRange[2];
		/* 38h */	bool regionInverse;
		/* 39h */	bool regionCenterOnly;
		/* 3Ah */	bool cover;
		/* 3Bh */	bool ordered;
		/* 3Ch */	eastl::vector<int> particleSelect;
		/* 50h */	bool selectAll;
	};
	ASSERT_SIZE(cSkinpaintDistributeDescription, 0x54);

	class cSkinpaintDistributeEffect
		: public cComponentBase
	{
	public:
		/* 0Ch */	cSkinpaintDistributeDescription* mpDescription;
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	eastl::vector<int> field_18;
		/* 2Ch */	bool mIsStarted;  // not initialized
	};
	ASSERT_SIZE(cSkinpaintDistributeEffect, 0x30);
}