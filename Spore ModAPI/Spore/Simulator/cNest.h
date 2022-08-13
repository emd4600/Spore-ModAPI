#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cBehaviorList.h>

#define cNestPtr eastl::intrusive_ptr<Simulator::cNest>

namespace Simulator
{
	class cHerd;

	class cNest
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
		/* 108h */	, public cBehaviorList
	{
	public:
		static const uint32_t TYPE = 0x1B92B27;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 120h */	bool mbResetNestEffects;
		/* 124h */	int mFlags;
		/* 128h */	intrusive_ptr<cHerd> mpHerd;
		/* 12Ch */	int mhFootprint;
	};
	ASSERT_SIZE(cNest, 0x130);
}