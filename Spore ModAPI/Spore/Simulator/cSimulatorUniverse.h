#pragma once

#include <Spore\App\PropertyList.h>
#include <Spore\Simulator\cGonzagoSimulator.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <EASTL\map.h>
#include <EASTL\vector_map.h>

#define SimulatorUniverse (*Simulator::cSimulatorUniverse::Get())

namespace Simulator
{
	struct tGrobShockData
	{
		/* 00h */	uint32_t mEmpire;
		/* 04h */	uint32_t mPlanetKey;
		/* 08h */	cGonzagoTimer mTimeSinceStart;
	};
	ASSERT_SIZE(tGrobShockData, 0x28);

	struct tPlayerDeathData
	{
		/* 00h */	uint32_t mKillerPoliticalID;
		/* 04h */	unsigned int mRemainingTime;
	};

	/// Universe Event Simulator
	class cSimulatorUniverse
		: public cGonzagoSimulator
	{
	public:
		static cSimulatorUniverse* Get();

		class IUniverseRoutine
		{
		public:
			/* 00h */	virtual ~IUniverseRoutine() = 0;
			/// Returns the probability that this routine must execute.
			/* 04h */	virtual float GetProbability(int deltaTimeMS, int) = 0;
			/* 08h */	virtual void Execute(int, eastl::vector<int>&) = 0;
			/* 0Ch */	virtual uint32_t GetID() = 0;
		};

	public:
		/// `gametuning~/UniverseSimulatorTuning.prop`
		/* 10h */	PropertyListPtr mpTuningPropList;
		/* 14h */	unsigned int mTimeSinceLastEvent;
		/* 18h */	eastl::map<int, int> field_18;
		/* 34h */	void* field_34;
		/* 38h */	char padding_38[0xF8 - 0x38];  //TODO
		/* F8h */	eastl::vector_map<int, int> field_F8;
		/* 110h */	tPlayerDeathData mPlayerDeath;
		/* 118h */	int mUniverseSimulatorMinTimeAfterColonyPlacement;
		/// In milliseconds
		/* 11Ch */	int mGrobShockDuration;
		/* 120h */	int field_120;  // 2
		/// In milliseconds
		/* 124h */	int mUniverseSimulatorMinTimeBetweenDisasters;
		/* 128h */	eastl::vector<tGrobShockData> mGrobShockList;
		/* 13Ch */	float mGrobThresholdNotAware;
		/* 140h */	float mGrobThresholdAware;
		/* 144h */	float mGrobThresholdVeryAware;
		/* 148h */	float mGrobThresholdExtremelyAware;
		/* 14Ch */	float mGrobAwarenessCap;
		/* 150h */	float mGrobDetectionRadius;
		/* 154h */	float mGrobAwarenessDecayRate;
		/* 158h */	int field_158;
		/// In milliseconds
		/* 15Ch */	int mGrobDelayBetweenHighAwarenessUpdates;
		/* 160h */	float mEmpireThresholdNotAware;
		/* 164h */	float mEmpireThresholdAware;
		/* 168h */	float mEmpireThresholdVeryAware;
		/* 16Ch */	float mEmpireThresholdExtremelyAware;
		/* 170h */	float mEmpireAwarenessCap;
		/* 174h */	float mEmpireDetectionRadius;
		/* 178h */	float mEmpireAwarenessDecayRate;
		/* 17Ch */	eastl::map<int, float> mAwarenessValue;
		/* 198h */	eastl::map<int, int> field_198;
		/* 1B4h */	int field_1B4;
	};
	ASSERT_SIZE(cSimulatorUniverse, 0x1B8);

	namespace Addresses(cSimulatorUniverse)
	{
		DeclareAddress(_ptr);  // 0x16E0A18 0x16DC798
	}

#ifdef SDK_TO_GHIDRA
	cSimulatorUniverse* sSimulatorUniverse;
#endif
}