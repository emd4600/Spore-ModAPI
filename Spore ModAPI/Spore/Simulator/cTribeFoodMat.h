#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>

#define cTribeFoodMatPtr intrusive_ptr<Simulator::cTribeFoodMat>

namespace Simulator
{
	class cTribe;

	/// The food mat of a tribe. Default model is `TribalTools!trg_sacrifice_altar1`, default `mMaterialType` is 2.
	class cTribeFoodMat
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0x629BAEC;
		static const uint32_t NOUN_ID = 0x629BAFE;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/// Default value is true
		/* 108h */	bool field_108;
		/* 10Ch */	intrusive_ptr<cTribe> mpTribe;
	};
	ASSERT_SIZE(cTribeFoodMat, 0x110);
}