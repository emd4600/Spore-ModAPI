#pragma once

#include <Spore\Simulator\Cell\cCellSerialiazibleData.h>
#include <Spore\Simulator\Cell\cCellResource.h>
#include <Spore\Simulator\Cell\cCellObjectData.h>
#include <Spore\Simulator\GoalCard.h>
#include <Spore\Simulator\cObjectPool.h>
#include <EASTL\fixed_vector.h>
#include <EASTL\map.h>

#define CellGame (*Simulator::Cell::cCellGame::Get())

namespace Simulator
{
	namespace Cell
	{
		enum class ScaleDifference
		{
			/// Cell is 2 or more levels smaller than player cell
			MuchSmaller = 0,
			/// Cell is 1 level smaller than player cell
			Smaller = 1,
			/// Cell is same level as player cell
			Equal = 2,
			/// Cell is 1 level larger than player cell
			Larger = 3,
			/// Cell is 2 or more levels larger than player cell
			MuchLarger = 4
		};

		class cCellGame
		{
		public:
			static cCellGame* Get();

			static void Initialize();

			static cObjectPoolIndex CreateCellObject(int, const Math::Vector3& position, int, cCellDataReference<cCellCellResource>*, int, float sizeFactor, float cellSize, int, int, int);


			static void MovePlayerToMousePosition(float deltaTime);

			/// Returns scale difference between the given cell and the player cell,
			/// telling whether it is smaller, larger or the same scale (level).
			/// @param otherCell
			/// @returns
			static ScaleDifference GetScaleDifferenceWithPlayer(cCellObjectData* otherCell);

			/// Calculates whether the first cell will or will not attack the second cell.
			/// This returns false when:
			/// - The two cells are the same type (the same `.cell` file)
			/// - `field_112` is true for any of the cells
			/// - Cell 1 `wontAttackPlayerWhenSmall` is true, cell 2 is player, and the cell is smaller
			/// - Cell 1 `wontAttackPlayer` is true and cell 2 is player
			/// - Both cells have the same `friendGroup` and it's not 0
			/// @param cell1
			/// @param cell2
			/// @returns True if cell 1 must not attack cell 2, false if it must attack.
			static bool ShouldNotAttack(cCellObjectData* cell1, cCellObjectData* cell2);

		public:
			/* 00h */	cAdvectResourcePtr mpCurrentAdvectionMap;
			/* 04h */	float field_4;  // related with advection
			/* 08h */	int field_8;
			/* 0Ch */	int field_C;
			/* 10h */	float field_10;
			/* 14h */	float field_14;
			/* 18h */	float field_18;
			/// 4096 objects of cCellObjectData
			/* 1Ch */	cObjectPool<cCellObjectData> mCells;
			/* 38h */	cObjectPool_ field_38;  // size 0x304
			/* 54h */	cObjectPool_ field_54;
			/* 70h */	eastl::map<int, int> field_70;
			/* 8Ch */	cObjectPool_ field_8C;
			/* A8h */	cObjectPool_ field_A8;
			/* C4h */	cObjectPool_ field_C4;
			/* E0h */	eastl::fixed_vector<int, 4096> field_E0;
			/* 40F8h */	void* field_40F8;
			/* 40FCh */	void* field_40FC;  //TODO pointer to some object from a pool
			/* 4100h */	char padding_4100[0x4114 - 0x4100];
			/* 4114h */	cCellDataReference<cCellWorldResource>* mpCurrentWorld;
			/* 4118h */	cCellDataReference<cCellWorldResource>* mpCurrentWorldBackground;
			/* 411Ch */	cObjectPoolIndex mAvatarCellIndex;
			/* 4120h */	int field_4120;
			/* 4124h */	int field_4124;
			/* 4128h */	eastl::fixed_vector<int64_t, 512> field_4128;
			/* 5140h */	char padding_5140[0x514C - 0x5140];
			/* 514Ch */	float field_514C;
			/* 5150h */	char padding_5150[0x5164 - 0x5150];
			/* 5164h */	ObjectPtr field_5164;
			/* 5168h */	int field_5168;
			/* 516Ch */	int field_516C;
			/* 5170h */	eastl::map<int, int> field_5170;
			/* 518Ch */	int field_518C;
			/* 5190h */	cCellSerializableDataPtr mpSerializableData;
			/* 5194h */	char field_5194[0x51E4 - 0x5194];
		};
		ASSERT_SIZE(cCellGame, 0x51E4);	

		namespace Addresses(cCellGame)
		{
			DeclareAddress(_ptr);  // 0x16B7E84 0x16B3C04
			DeclareAddress(Initialize);  // 0xE81130 0xE80BA0
			DeclareAddress(CreateCellObject);  // 0xE74F60 0xE74A20
			DeclareAddress(MovePlayerToMousePosition);  // 0xE5BD90 0xE5B790
			DeclareAddress(GetScaleDifferenceWithPlayer);  // 0xE57940 0xE57340
			DeclareAddress(ShouldNotAttack);  // 0xE57A60 0xE57460
		}

#ifndef SDK_TO_GHIDRA
		GoalCard* GetGoalCards();
#else
		GoalCard sGoalCards[0x76];
		cCellGame* sCellGame;
#endif

		/// Returns the info of the cCellWorldResource::cAdvectInfo of the current world and cell scale,
		/// based on the current food progression.
		/// @param[out] dst0
		/// @param[out] dstStrength
		/// @param[out] dstVariance
		/// @param[out] dstPeriod
		/// @returns The advect file ID
		uint32_t GetCurrentAdvectInfo(CellStageScale& dst0, float& dstStrength, float& dstVariance, float& dstPeriod);

		/// Returns the advect file ID for the next cell scale in the current world, based on the current food progression.
		uint32_t GetNextAdvectID();
	}

	namespace Addresses(Cell) {
		DeclareAddress(GoalCards_ptr);
		DeclareAddress(GetCurrentAdvectInfo);  // 0xE594F0 0xE58EF0
		DeclareAddress(GetNextAdvectID);  // 0xE59430 0xE58E30
	}
}