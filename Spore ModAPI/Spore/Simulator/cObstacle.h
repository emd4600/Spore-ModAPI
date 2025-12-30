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

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		enum PlantType
		{
			kLargeSpecies = 0,
			kMediumSpecies = 1,
			kSmallSpecies = 2,
		};

	public:
		/* 34h */	int field_34;
		/* 38h */	Math::Vector3 mPosition;
		/* 44h */	float mObstacleBaseCollisionRadius;
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
		/* 7Ch */	ResourceKey mSpeciesKey;
		/* 88h */	PlantType mPlantType;
	};
	ASSERT_SIZE(cObstacle, 0x8C);
}