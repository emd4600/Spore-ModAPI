/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#pragma once


/// @file Resources.h
/// This file includes all the necessary headers to use the resource system in Spore, which includes accessing .package files.

#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\IKeyFilter.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\DatabaseDirectoryFiles.h>
#include <Spore\Resource\Database.h>
#include <Spore\Resource\Paths.h>
#include <Spore\Resource\IRecord.h>
#include <Spore\Resource\FakeRecord.h>

/// @namespace Resource
///
/// @brief The system for accessing file resources stored in .package files.
///
/// This namespace contains all the necessary classes needed for working with file resources stored in .package files.
/// The main class is the IResourceManager, which can be used to get resources from the file system.
/// The resource manager contains a list of Database objects, which can be one of these two:
///  - The DatabasePackedFile represents a .package file that contains resources.
///  - The DatabaseDirectoryFiles represents a plain disk folder, such as the `Games/Game0` folder
///
