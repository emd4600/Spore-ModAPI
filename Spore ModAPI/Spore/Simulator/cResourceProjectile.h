#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cCommodityNode.h>
#include <Spore\Simulator\cProjectile.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cCivilization.h>

#define cResourceProjectilePtr eastl::intrusive_ptr<Simulator::cResourceProjectile>

namespace Simulator
{
	/// Projectile used in civilization stage to capture spice geysers. Might be used for other things too.
	class cResourceProjectile
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 504h */	, public cProjectile
	{
	public:
		static const uint32_t TYPE = 0x5776A28;
		static const uint32_t NOUN_ID = 0x5776A2C;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		void LaunchProjectile(cCivilization* civilization, cCommodityNode* commodityNode, const Math::Vector3&, float speed, bool);

	public:
		/* 514h */	bool field_514;
		/* 518h */	int field_518;
		/* 51Ch */	cCommodityNodePtr mpNode;
		/* 520h */	Vector3 mTargetPos;
		/// The projectile will be destroyed after 1000 ticks of this timer.
		/* 530h */	cGonzagoTimer mLifeTimer;
		/// Political ID of the civilization that owns this projectile.
		/* 550h */	uint32_t mOwner;  // -1
		/* 554h */	bool field_554;
	};
	ASSERT_SIZE(cResourceProjectile, 0x558);

	namespace Addresses(cResourceProjectile)
	{
		DeclareAddress(LaunchProjectile);  // 0xCBDCD0 0xCBE7C0
	}
}