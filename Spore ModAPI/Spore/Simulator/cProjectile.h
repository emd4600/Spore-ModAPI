#pragma once

#include <Spore\Simulator\cLocomotiveObject.h>

#define cProjectilePtr eastl::intrusive_ptr<Simulator::cProjectile>

namespace Simulator
{
	class cCombatant;

	class cProjectile
	{
	public:
		static const uint32_t TYPE = 0x142DB2A;

		/* 00h */	virtual ~cProjectile() {};
		/* 04h */	virtual void* Cast(uint32_t type) = 0;
		/* 08h */	virtual int Release() = 0;
		/* 0Ch */	virtual int AddRef() = 0;

		/// Returns a reference to the locomotive object of this projectile (so just returns `this` as a cLocomotiveObject).
		/* 10h */	virtual cLocomotiveObject* GetLocomotiveObject() = 0;

		/// Called every frame by the CombatSimulator. Must return true if the projectile instance is still alive,
		/// or false if it has finished and must be destroyed.
		/* 14h */	virtual bool Update() = 0;

		/* 18h */	virtual cCombatant* GetOwnerCombatant();  // returns 0 most of the time
		/* 1Ch */	virtual float GetProjectileScale();  // returns 1.0 most of the time
		/* 20h */	virtual void SetProjectileScale(float);  // does nothing most of the time
		/* 24h */	virtual bool PreventsPlanetExit();  // returns false most of the time

	public:
		/* 04h */	Vector3 mTargetOffset;
		/* 10h */	bool projectile_field_10;
	};
	ASSERT_SIZE(cProjectile, 0x14);
}