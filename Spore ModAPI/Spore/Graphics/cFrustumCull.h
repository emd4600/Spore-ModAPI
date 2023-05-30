#pragma once

#include <Spore\MathUtils.h>
#include <Spore\Internal.h>

namespace Graphics
{
	struct cPlane
		: public Math::Vector4
	{
		/* 10h */	float field_10;  // not initialized
		/* 14h */	float field_14;  // not initialized
		/* 18h */	float field_18;  // not initialized
		/* 1Ch */	float field_1C;  // not initialized
		/* 20h */	float field_20;  // not initialized
		/* 24h */	float field_24;  // not initialized
	};
	ASSERT_SIZE(cPlane, 0x28);

	class cFrustumCull 
	{
	public:
		void OffsetPlanes(float offset);

		int FrustumTestAABB(const Math::Vector3& lower, const Math::Vector3& upper, int flags);

		int FrustumTestSphere(const Math::Vector3& center, float radius);

		void UpdateFromProjectionMatrix(const Math::Matrix4& projectionMatrix);

	public:
		/* 00h */	cPlane mPlanes[6];
	};
	ASSERT_SIZE(cFrustumCull, 0xF0);

	namespace Addresses(cFrustumCull)
	{
		DeclareAddress(OffsetPlanes);  // 0x6FFFE0 0x6FFB10
		DeclareAddress(FrustumTestSphere);  // 0x700130 0x6FFC60
		DeclareAddress(FrustumTestAABB);  // 0x700680 0x07001B0
		DeclareAddress(UpdateFromProjectionMatrix);  // 0x700360 0x6FFE90
	}
}