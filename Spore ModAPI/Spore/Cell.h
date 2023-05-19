#pragma once

#include <Spore\Simulator\Cell\cCellGame.h>
#include <Spore\Simulator\Cell\cCellGFX.h>
#include <Spore\Simulator\Cell\cCellUI.h>
#include <Spore\Simulator\Cell\cCellObjectData.h>
#include <Spore\Simulator\Cell\cCellResource.h>
#include <Spore\Simulator\Cell\cCellSerialiazibleData.h>

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
