#pragma once

#include <Spore\Simulator\ISimulatorSerializable.h>
#include <EASTL\map.h>

namespace Simulator
{
	class cSavedGameHeader
		: public ISimulatorSerializable
		, public DefaultRefCounted
	{
	public:
		/* 0Ch */	uint32_t mFileVersionMajor;
		/* 10h */	uint32_t mFileVersionMinor;
		/* 14h */	eastl::map<uint32_t, int> mObjectCountMap;
		/* 30h */	int mTimeStamp[9];
		/* 54h */	uint32_t mGameMode;
		/* 58h */	bool mbSnapshot;
		/* 5Ch */	ResourceKey mCurrentPlanetKey;
	};

	ASSERT_SIZE(cSavedGameHeader, 0x68);
}