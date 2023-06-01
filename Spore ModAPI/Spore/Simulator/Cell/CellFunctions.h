#pragma once

#include <Spore\Simulator\Cell\cCellGame.h>
#include <Spore\Simulator\GoalCard.h>

namespace Simulator
{
	namespace Cell
	{
#ifndef SDK_TO_GHIDRA
		GoalCard* GetGoalCards();
#else
		GoalCard sGoalCards[0x76];
		cCellGame* sCellGame;
#endif

		/// Returns the player cell.
		/// @returns
		cCellObjectData* GetPlayerCell();

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

		cObjectPoolIndex CreateCellObject(
			cCellQueryLinkedPool* query, 
			const Math::Vector3& position, 
			float elevation, 
			cCellDataReference<cCellCellResource>* resource, 
			CellStageScale scaleLevel, 
			float sizeFactor, 
			float cellSize, 
			bool applySize = true, 
			Math::Quaternion* pTargetOrientation = nullptr, 
			int = 0);


		void MovePlayerToMousePosition(float deltaTime);

		/// Returns scale difference between the given cell and the player cell,
		/// telling whether it is smaller, larger or the same scale (level).
		/// @param otherCell
		/// @returns
		ScaleDifference GetScaleDifferenceWithPlayer(cCellObjectData* otherCell);

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
		bool ShouldNotAttack(cCellObjectData* cell1, cCellObjectData* cell2);

		/// Returns how much hp damage the victim cell takes when attacked by another cell.
		/// The maximum HP for all cells is 6.
		/// @param attackerCell
		/// @param victimCell
		/// @returns The amount of HP damage.
		int GetDamageAmount(cCellObjectData* attackerCell, cCellObjectData* victimCell);

		/// Finds all the cells that are within a radius of a specific position.
		/// The caller must provide a buffer where 
		/// For example, getting all the cells 10 units from the player:
		/// ```cpp
		/// Math::Vector3 position = Simulator::Cell::GetAvatarCell()->mTransform.GetOffset();
		/// cObjectPoolIndex buffer[400];
		/// int numCells = Simulator::Cell::FindCellsInRadius(CellGame.field_40FC, position, 10.0f, buffer, 400);
		/// ```
		int FindCellsInRadius(cCellQueryLinkedPool* query, const Math::Vector3& position, float radius, cObjectPoolIndex* dst, int dstArraySize, void* dst2 = nullptr);
	}

	namespace Addresses(Cell) {
		DeclareAddress(GoalCards_ptr);
		DeclareAddress(GetCurrentAdvectInfo);  // 0xE594F0 0xE58EF0
		DeclareAddress(GetNextAdvectID);  // 0xE59430 0xE58E30
		DeclareAddress(CreateCellObject);  // 0xE74F60 0xE74A20
		DeclareAddress(MovePlayerToMousePosition);  // 0xE5BD90 0xE5B790
		DeclareAddress(GetScaleDifferenceWithPlayer);  // 0xE57940 0xE57340
		DeclareAddress(ShouldNotAttack);  // 0xE57A60 0xE57460
		DeclareAddress(GetDamageAmount);  // 0xE58F80 0xE58980
		DeclareAddress(FindCellsInRadius);  // 0xE876D0 0xE87210
	}
}