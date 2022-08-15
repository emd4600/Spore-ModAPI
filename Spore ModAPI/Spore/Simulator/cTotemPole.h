#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>

#define cTotemPolePtr eastl::intrusive_ptr<Simulator::cTotemPole>

namespace Simulator
{
	/// The totem pole of a tribe. Default model is `TribalTools!0x93256BA`, default `mMaterialType` is 2.
	class cTotemPole
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0x55CF8E3;
		static const uint32_t NOUN_ID = 0x55CF865;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 108h */	vector<int> field_108;
		/* 11Ch */	vector<int> mSegments;
		/* 130h */	vector<Math::ColorRGB> mSegmentColors;
		/// Default value is 5
		/* 144h */	int mTotalPossibleSegments;
		/// Default value is true
		/* 148h */	bool field_148;
	};
	ASSERT_SIZE(cTotemPole, 0x14C);
}
