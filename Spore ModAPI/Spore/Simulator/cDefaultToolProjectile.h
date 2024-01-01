#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cLocomotiveObject.h>
#include <Spore\Simulator\cProjectile.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cCity.h>
#include <EASTL\set.h>

#define cDefaultToolProjectilePtr eastl::intrusive_ptr<Simulator::cDefaultToolProjectile>

namespace Simulator
{
	enum class DamageType
	{
		Bribe = 4,

		Healing = 10,
		BlackCloud = 11,
		_543F8E29 = 12,
		Nuclear = 13,
		EMP = 14,
		IField = 15,
		Diplomatic = 16,
	};

	class cDefaultToolProjectile
		/* 00h */	: public cGameData
		/* 34h */	, public cLocomotiveObject
		/* 504h */	, public cProjectile
	{
	public:
		static const uint32_t TYPE = 0x24270C4;
		static const uint32_t NOUN_ID = 0x24270C5;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/* 54h */	virtual void ConfigureProjectile(cSpaceToolData* tool, int minDamage, int maxDamage, float explosionRadius, int damageType, float projectileRadius);
		/* 58h */	virtual void OnProjetileHit(int strikeType, Object* hitObject);

	public:
		/* 518h */	cSpaceToolDataPtr mTool;
		/* 51Ch */	int field_51C;
		/* 520h */	Math::Vector3 mPrevPosition;
		/* 52Ch */	int mMinDamage;
		/* 530h */	int mMaxDamage;
		/* 534h */	float mExplosionRadius;
		/// A value in DamageType
		/* 538h */	int mDamageType;
		/* 53Ch */	float mProjectileScale;  // 1.0
		/* 540h */	float mCurrentExplosionRadius;
		/* 544h */	int mBombPhase;
		/* 548h */	cGonzagoTimer mPhaseTimer;
		/* 568h */	uint64_t mTimeOfLastDamageCheck;
		/* 570h */	eastl::set<cSpatialObjectPtr> mDamagedObjects;
		/* 58Ch */	Math::Vector3 mExplosionPoint;
		/* 598h */	int mTargetDamagePointId;  // -1
		/* 59Ch */	Math::Vector3 mTargetPoint;
		/* 5A8h */	char padding_5A8[0x5CC - 0x5A8];
		/* 5CCh */	int field_5CC;
		/* 5D0h */	int mStrikeType;
		/* 5D4h */	cGameDataPtr mTargetStruck;
		/* 5D8h */	cSpatialObjectPtr mpTarget;
		/* 5DCh */	eastl::vector<cCityPtr> mWaveFrontTargetCities;
	};
	ASSERT_SIZE(cDefaultToolProjectile, 0x5F0);

	/// Launches a projectile using the configuration of the specified tool.
	/// Example code to shoot 50 meters in front of your UFO:
	/// ```cpp
	/// auto playerPosition = SimulatorPlayerUFO.GetUFO()->GetPosition();
	/// auto target = playerPosition + 50 * SimulatorPlayerUFO.GetUFO()->GetDirection();
	/// cSpaceToolDataPtr tool;
	/// if (ToolManager.LoadTool({ id("AllyMissile1"), TypeIDs::prop, GroupIDs::SpaceTools }, tool)) 
	/// {
	///		auto projectile = simulator_new<Simulator::cDefaultToolProjectile>();
	///		Simulator::LaunchDefaultToolProjectile(tool.get, projectile, playerPosition, target);
	/// }
	/// ```
	/// @param tool Tool used to configure the projectile trajectory, damage, effect, etc
	/// @param projectile Projectile object
	/// @param origin Starting point of the projectile
	/// @param target Target point of the projectile
	void LaunchDefaultToolProjectile(cSpaceToolData* tool, cDefaultToolProjectile* projectile, const Math::Vector3& origin, const Math::Vector3& target);
}

namespace Addresses(Simulator)
{
	DeclareAddress(LaunchDefaultToolProjectile);  // 0x1054F40 0x1054390
}