#pragma once

#include <Spore\Simulator\ISimulatorSerializable.h>
#include <Spore\Simulator\cCity.h>
#include <Spore\Simulator\cCivilization.h>
#include <Spore\Simulator\StarID.h>
#include <Spore\Simulator\SimulatorEnums.h>

#define cCommEventPtr eastl::intrusive_ptr<Simulator::cCommEvent>

namespace Simulator
{
	class cMission;

	class cCommEvent
		: public ISimulatorSerializable
		, public IVirtual
	{
	public:

		/* 08h */	int mnRefCount;
		/* 0Ch */	cCommEventType mEventType;  // -1
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	uint32_t mSource;  // -1
		/* 1Ch */	uint32_t mTarget;  // -1
		/* 20h */	cCityPtr mpSourceCity;
		/* 24h */	cCityPtr mpTargetCity;
		/* 28h */	cCivilizationPtr mpSourceCivilization;
		/* 2Ch */	cCivilizationPtr mpTargetCivilization;
		/* 30h */	bool mbVisibleInGalaxy;
		/* 34h */	PlanetID mPlanetKey;  // -1
		/* 38h */	uint32_t mFileID;  // -1
		/* 3Ch */	uint32_t mDialogID;  // -1
		/* 40h */	intrusive_ptr<cMission> mpMission;
		/* 44h */	int mPriority;  // -1
		/* 48h */	unsigned int mDuration;
		/* 4Ch */	unsigned int mElapsedTime;
		/* 50h */	vector<int> mDynamicResponses;  //PLACEHOLDER struct
		/* 64h */	vector<int> field_64;
		/* 78h */	vector<int> field_78;
		/* 8Ch */	vector<int> field_8C;
	};
	ASSERT_SIZE(cCommEvent, 0xA0);
}
