#pragma once

#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cProjectile.h>
#include <Spore\App\IMessageListener.h>

namespace Simulator
{
	class cCombatSimulator
		/* 00h */	: public cGonzagoSimulator
		/* 10h */	, public App::IMessageListener
	{
	public:
		static const uint32_t TYPE = 0x23BA451;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 14h */	eastl::vector<cProjectilePtr> mProjectiles;
		/* 28h */	eastl::vector<cProjectilePtr> field_28;
		/* 3Ch */	bool mIsUpdatingProjectiles;
		/// If true, it collects all cProjectile instances and adds listener for SimulatorMessages::kMsgGameNounStatusChanged
		/* 3Dh */	bool field_3D;
	};
	ASSERT_SIZE(cCombatSimulator, 0x40);

	namespace Addresses(cCombatSimulator)
	{
		DeclareAddress(ptr);  // 0x167E910
	}
}