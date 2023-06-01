#pragma once

#include <Spore\Simulator\Cell\cCellGame.h>
#include <Spore\Simulator\Cell\cCellGFX.h>
#include <Spore\Simulator\Cell\cCellUI.h>
#include <Spore\Simulator\Cell\cCellObjectData.h>
#include <Spore\Simulator\Cell\cCellResource.h>
#include <Spore\Simulator\Cell\cCellSerialiazibleData.h>
#include <Spore\Simulator\Cell\CellFunctions.h>
#include <Spore\Simulator\Cell\CellAnimations.h>

/// @namespace Simulator::Cell
///
/// @brief Cell stage functionality
///
/// This namespace contains all the functionality of the Cell stage. The main classes are:
///  - Simulator::Cell::cCellGame: Used to control cell gameplay. Quick access with CellGame.
///  - Simulator::Cell::cCellGFX: Keeps track of the visuals, like models, effects, anim worlds, etc. Quick access with CellGFX.
///  - Simulator::Cell::cCellUI: The user interface. Quick access with CellUI.
///  - App::cCellModeStrategy: The App::IGameMode for the cell stage. It has the functions for mouse and keyboard controls, and the `Update()` function where cell stage code is executed.
/// 
/// Most of cell stage is defined thorugh several files: `.effectMap`, `.cell`, `.lootTable`, etc. 
/// All these files have their representation in code as Simulator::Cell::cCellEffectMapResource, Simulator::Cell::cCellCellResource, etc
/// The main file is `CellGame.globals`, which can be obtained in code with Simulator::Cell::GetGlobalsData()
/// 
/// Everything you see in the cell stage is considered a "cell", including rocks, bubbles, poison and food.
/// Cells are represented by the Simulator::Cell::, and are stored in the Simulator::Cell::cCellGame::mCells object pool.
/// Every cell is backed by a `.cell` file (Simulator::Cell::cCellCellResource) that defines all its properties, such as 
/// AI configuration, model, etc.
/// 
/// For many of the cells actions, it is just enough to change a variable to see changes, as the cell stage update method
/// takes care of the rest. Such values are `mTargetPosition`, `mTargetOrientation`, `mTargetOpacity`, `mTargetSize`, etc.
/// For example, changing `mTargetPosition` and setting `mIsIdle` to false, will not teleport the cell but make it swim
/// towards the target position instead.
/// 
/// ## Code examples
/// 
/// Moving the player cell 10 units to the right. This does not teleport it immediately, but it makes it swim towards there.
/// ```cpp
/// auto cell = Simulator::Cell::GetPlayerCell();
/// cell->mTargetPosition.x += 10.0f;
/// cell->mIsIdle = false;
/// ```
/// 
/// Creating a cell next to the player:
/// ```cpp
/// auto player = Simulator::Cell::GetPlayerCell();
/// auto cellIndex = Simulator::Cell::CreateCellObject(
/// 	CellGame.mpCellQuery,
/// 	player->mTransform.GetOffset() + Math::Vector3(4.0f, 0.0f, 0.0f),
/// 	0.0f,
/// 	player->mCellResource,
/// 	player->mScale,
/// 	1.0f,
/// 	1.0f
/// );
/// ```
/// 
/// Finding nearby cells and enlarging them:
/// ```cpp
/// auto player = Simulator::Cell::GetPlayerCell();
/// Simulator::cObjectPoolIndex cellIndices[400];
/// int numCells = Simulator::Cell::FindCellsInRadius(
/// 	CellGame.mpCellQuery,
/// 	player->GetPosition(), 5.0,  // center and radius of search
/// 	cellIndices, 400);
/// 
/// for (int i = 0; i < numCells; i++)
/// {
/// 	auto cell = CellGame.mCells.Get(cellIndices[i]);
/// 	cell->mTargetSize *= 2.0f;
/// }
/// ```
/// 
/// Make nearby cells chase the player:
/// ```cpp
/// auto player = Simulator::Cell::GetPlayerCell();
/// 
/// Simulator::cObjectPoolIndex cellIndices[400];
/// int numCells = Simulator::Cell::FindCellsInRadius(
/// 	CellGame.mpCellQuery,
/// 	player->GetPosition(), 20.0,  // center and radius of search
/// 	cellIndices, 400);
/// 
/// for (int i = 0; i < numCells; i++)
/// {
/// 	auto cell = CellGame.mCells.Get(cellIndices[i]);
/// 	if (cell->IsCreature()) {
/// 		cell->mChaseCellTime = 10.0f;
/// 		cell->mChaseCellIndex = player->Index();
///			// If we don't disable this, fleeing cells will not chase us
///			cell->mFleeCellTime = 0.0f;
///			cell->mFleeCellIndex = 0;
/// 	}
/// }
/// ```
/// 
/// Read data from a `.cell` file:
/// ```cpp
/// // Declare this as a static variable
/// Simulator::Cell::cCellCellResource::Reference* sCellChomperReference;
/// 
/// // In the initialize method, choose which `.cell` file we are reading
/// sCellChomperReference = Simulator::Cell::cCellCellResource::Reference::Create(id("cell_chomper"));
/// 
/// // To use the data
/// cCellCellResourcePtr cellResource;
/// auto cellData = Simulator::Cell::GetData(sCellChomperReference, cellResource);
/// ```
/// 
