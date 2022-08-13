#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>

#define cInterCityRoadPtr eastl::intrusive_ptr<Simulator::cInterCityRoad>

namespace Simulator
{
	class cCity;

	class cInterCityRoad
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0x2BCA14B;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 108h */	string16 field_108;  // IntercityRoadMesh
		/* 118h */	int field_118;
		/* 11Ch */	intrusive_ptr<cCity> mpCity1;
		/* 120h */	intrusive_ptr<cCity> mpCity2;
		/* 124h */	int mRoadType;
		/* 128h */	Vector3 mPathData;
		/* 134h */	int field_134;
		/* 138h */	int field_138;
		/* 13Ch */	float mWidth;  // 1.0
	};
	ASSERT_SIZE(cInterCityRoad, 0x140);
}