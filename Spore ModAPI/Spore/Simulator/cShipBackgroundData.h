#pragma once

#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\MathUtils.h>

namespace Simulator
{
	class cShipBackgroundData
		: public ISimulatorSerializable
	{
	public:
		/* 04h */	UfoType mUfoType;
		/* 08h */	Math::Vector3 mPosition;
		/* 14h */	float mHealth;
		/* 18h */	float mMaxHealth;
		/* 1Ch */	int mBomberIndex;
	};
	ASSERT_SIZE(cShipBackgroundData, 0x20);
}