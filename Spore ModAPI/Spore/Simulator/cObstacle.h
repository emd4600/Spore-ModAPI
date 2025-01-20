#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Graphics\Model.h>

#define cObstaclePtr eastl::intrusive_ptr<Simulator::cObstacle>

namespace Simulator
{
	class cObstacle
		: public cGameData
	{
	public:
		static const uint32_t TYPE = 0x3ED590D;
		static const uint32_t NOUN_ID = 0x3ED8573;

	public:
		/* 34h */	int field_34;
		/* 38h */	Math::Vector3 field_38;
		/* 44h */	float field_44;
		/* 48h */	float mObstacleCanopyCollisionRadius;
		/* 4Ch */	float mObstacleCollisionHeight;
		/* 50h */	int field_50;  // -1
		/* 54h */	int field_54;
		/* 58h */	int field_58;
		/* 5Ch */	int field_5C;  // -1
		/* 60h */	int field_60;  // not initialized
		/* 64h */	int field_64;  // -1
		/* 68h */	int field_68;  // 1.0
		/* 6Ch */	int field_6C;  // not initialized
		/* 70h */	ModelPtr mModel;
		/* 74h */	int field_74;
		/* 78h */	int field_78;
		/* 7Ch */	ResourceKey field_7C;
		/* 88h */	int field_88;
	};
	ASSERT_SIZE(cObstacle, 0x8C);
}