#pragma once

#include <Spore\Anim\IAnimManager.h>
#include <Spore\Anim\SPAnimation.h>
#include <Spore\App\IMessageListener.h>

namespace Anim
{
	class cAnimManagerImpl
		: public IAnimManager
		, public App::IMessageListener
		, public DefaultRefCounted
	{
	public:
		/* 10h */	float field_10;  // 0.002
		/* 14h */	SPAnimationPtr mpDefaultFillerAnimation;
		/* 18h */	eastl::map<int, int> field_18;
		/* 34h */	eastl::map<uint32_t, SPAnimationPtr> mPendingAnimMap;
		/* 50h */	int field_50;
		/* 54h */	int field_54;
		/* 58h */	int field_58;
		/* 5Ch */	int field_5C;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	eastl::vector<IAnimWorldPtr> mWorlds;
		/* 7Ch */	int field_7C;
		/* 80h */	int field_80;
		/* 84h */	int field_84;
	};
	ASSERT_SIZE(cAnimManagerImpl, 0x88);
}