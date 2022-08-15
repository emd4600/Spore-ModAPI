#pragma once

#include <Spore\Simulator\cOrnament.h>

#define cHitSpherePtr eastl::intrusive_ptr<Simulator::cHitSphere>

namespace Simulator
{
	class cHitSphere
		: public cOrnament
	{
	public:
		static const uint32_t TYPE = 0x2E71A5A;
		static const uint32_t NOUN_ID = 0x2E72CAE;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		void SetParameters(const Vector3& origin, float radius);

	public:
		/* 238h */	float mRadius;
		/* 23Ch */	float mMinScreenSize;
		/* 240h */	float mMaxScreenSize;
		/* 244h */	float mMinDistance;
		/* 248h */	float mMaxDistance;
		/* 24Ch */	cGameDataPtr mpDelegate;
	};
	ASSERT_SIZE(cHitSphere, 0x250);
}