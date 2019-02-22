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
#include <Spore\Resource\IResourceFilter.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\IPFRecord.h>

/// @namespace Resource
///
/// This namespace contains all the necessary classes needed for working with file resources stored in .package files.
/// The main class is the IResourceManager, which can be used to get resources from the file system.
/// The DatabasePackedFile represents a .package file that contains resources.
///

/// 
/// @page resources Resources
///
/// This page has information about interacting with resources and game files. To use them,
/// you need to include the header Models.h
///
/// To read the contents of a file, you might want to check the \ref io "IO module".
///
/// @tableofcontents
///
/// @section resources_tutorial1 Tutorial: Get the stream of a file
///
/// In order to get the raw stream of a file, so its contents can be read using the IO namespace, follow these steps:
/// 1. First, you must get the DBPF (.package file) that contains the file. If more that one package contains the file,
/// the one with the highest priority will be returned. You need to use the Resource::IResourceManager::GetDBPF() method for
/// that.
/// 
/// 2. Once you have the DBPF, use the Resource::DatabasePackedFile::GetFile() method to get the file you want. You must
/// pass the ResourceKey of the file you want as an argument. The method is used to get the Resource::IPFRecord of the file, which
/// can then be used to get the data from the file.
/// 
/// This is the resulting code to get the file 0x405010BB!TestFile.txt:
/// ~~~~~~~~~~~~~~~~~~{.cpp}
/// // The constructor takes instanceID, typeID and groupID as parameters.
/// // We use the Hash::FNV() to get the ID from a string.
/// // Note that some extensions might use different IDs than the FNV hash.
/// ResourceKey key = ResourceKey(Hash::FNV("TestFile"), Hash::FNV("txt"), 0x405010BB);
/// Resource::DBPF* pDBPF = Resource::IResourceManager::Get()->GetDBPF(key);
/// if (pDBPF != nullptr)
/// {
///		// If the file does not exist, pDBPF will be nullptr and nothing will happen
///		Resource::IPFRecord* pRecord;
///		if (pDBPF->GetFile(name, &pRecord))
///		{
///			// Do something with the IPFRecord
///		}
/// }
/// ~~~~~~~~~~~~~~~~~~
/// Generally, the most common function of Resource::IPFRecord is Resource::IPFRecord::GetStream(), which returns an IO::IStream.
/// For more information about reading/writing data from/to a file, check the IO namespace and the page about input/output.
///
/// @section resources_tutorial2 Tutorial: Get multiple files from a folder
/// Sometimes it is convenient to get all the files from a folder, or a certain extension, or that just fit a certain criteria. 
///
/// 1. Create a filter. You can do it by inheriting the Resource::IResourceFilter class, but if you don't want anything complicated
/// you can just use the predefined Resource::StandardFileFilter class. For example, this filter will get all the files in the
/// 0x4010C000 folder (the type doesn't matter).
/// ~~~~~~~~~~~~~~~~~~{.cpp}
/// // The constructor arguments are instanceID, groupID and typeID. Use ResourceKey::kWildcardID to accept any ID.
/// Resource::StandardFileFilter filter = Resource::StandardFileFilter(ResourceKey::kWildcardID, 0x4010C000, ResourceKey::kWildcardID);
/// ~~~~~~~~~~~~~~~~~~
/// 
/// 2. Get all the ResourceKeys of the files and the DBPF files that contain them, using the Resource::IResourceManager::GetFileKeys()
/// method. The method returns the number of files returned, so you can store it for later use.
/// ~~~~~~~~~~~~~~~~~~{.cpp}
/// eastl::vector<ResourceKey> keys;  // the resource keys will be put here.
/// eastl::vector<DBPF*> dbpfs;  // the DBPFs that contain each of the files will be put here.
/// size_t numFiles = Resource::IResourceManager::Get()->GetFileKeys(keys, &filter, &dbpfs);
/// ~~~~~~~~~~~~~~~~~~
///
/// 3. Use the generated vectors to get the files as in the previous tutorial:
/// ~~~~~~~~~~~~~~~~~~{.cpp}
/// for (size_t i = 0; i < numFiles; i++)
/// {
///		Resource::IPFRecord* pRecord;
///		if (dbpfs[i]->GetFile(keys[i], &pRecord))
///		{
///			// Do something with the IPFRecord
///		}
/// }
/// ~~~~~~~~~~~~~~~~~~
///
/// @section more_info More information:
/// - Resource::IResourceManager
/// - Resource::IPFRecord
/// - Resource::DatabasePackedFile
/// - Resource::IResourceFilter
/// - ResourceKey
///
