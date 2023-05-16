#pragma once

#include <Spore\Simulator\ISimulatorSerializable.h>

#define cCellSerializableDataPtr eastl::intrusive_ptr<Simulator::Cell::cCellSerializableData>
#define CellSerializableData (*Simulator::Cell::cCellSerializableData::Get())

namespace Simulator
{
	namespace Cell
	{
		struct cCellMission
		{
			/* 00h */	int state;
			/* 04h */	int progress;
			/* 08h */	int plantProgress;
			/* 0Ch */	int field_C;
		};
		ASSERT_SIZE(cCellMission, 0x10);

		class cCellSerializableData
			: public ISimulatorSerializableRefCounted
		{
		public:
			static cCellSerializableData* Get();

		public:
			/* 0Ch */	int mGameMode;
			/* 10h */	ResourceKey mPlayerCreatureKey;
			/* 1Ch */	int mFoodProgression;
			/* 20h */	int mPlantFoodProgression;
			/* 24h */	int mOverPlantFoodProgression;
			/* 28h */	int mOverAnimalFoodProgression;
			/* 2Ch */	int mEvolutionPointsSpent;
			/* 30h */	int field_30;  // 10
			/* 34h */	int mUnlockedParts[13];
			/* 68h */	bool mPartCinematicPlayed;
			/* 69h */	bool mShowMateButton;
			/* 6Ch */	int mKillCount;
			/* 70h */	int mDeathCount;
			/* 74h */	int gameTimeMS;
			/* 78h */	uint32_t gameID;
			/* 7Ch */	int difficulty;
			/* 80h */	cCellMission missions[6];
			/* E0h */	bool playerHasMoved;
			/* E1h */	bool playerHasEaten;
			/* E2h */	bool mFirstEditorEntry;
			/* E4h */	int mNanites;
			/* E8h */	bool mNanovirusActive;
			/* E9h */	bool mAddedStartTelemetry;
		};
		ASSERT_SIZE(cCellSerializableData, 0xEC);

#ifdef SDK_TO_GHIDRA
		cCellSerializableData* sCellSerializableData;
#endif

		namespace Addresses(cCellSerializableData)
		{
			DeclareAddress(_ptr);  // 0x16B8060 0x16B3DE0
		}
	};
}