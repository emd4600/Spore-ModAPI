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

#include <EASTL\hash_map.h>
#include <EASTL\vector.h>
#include <Spore\ResourceKey.h>
#include <Spore\Resource\IKeyFilter.h>
#include <Spore\FixedPoolAllocator.h>
#include <Spore\CoreAllocatorAdapter.h>
#include <Spore\IO\EAIOZoneObject.h>

namespace Resource
{
	///
	/// This class stores the metadata of all the files contained in a DBPF file. It is used for indexing and accessing
	/// files.
	///
	class PFIndexModifiable 
		: public IO::EAIOZoneObject
	{
	public:
#ifndef SDK_TO_GHIDRA
		typedef eastl::hash_map<ResourceKey, RecordInfo, eastl::hash<ResourceKey>, eastl::equal_to<ResourceKey>, ICoreAllocatorAdapter> ItemsMap;
#else
		typedef eastl::hash_map<ResourceKey, RecordInfo, int, int, ICoreAllocatorAdapter> ItemsMap;
#endif

		PFIndexModifiable(ICoreAllocator* pAllocator);
		virtual ~PFIndexModifiable() {};

		/* 04h */	virtual bool func04h();  // returns true  // is modifiable?

		///
		/// Tells whether this PFIndex is empty (i.e. contains no files) or not.
		///
		/* 08h */	virtual bool IsEmpty();

		///
		/// Returns the number of files contained in this PFIndex.
		///
		/* 0Ch */	virtual size_t GetFileCount();

		///
		/// Removes all the files from this PFIndex. 
		/// This only deletes the files' metadata, not the file content.
		///
		/* 10h */	virtual bool Reset();

		///
		/// Gets the total amount of bytes occupied by the data of the files in this PFIndex. 
		///
		/* 14h */	virtual size_t GetTotalDiskSize();

		///
		/// Returns the offset of the file where the data of this PFIndex' files ends.
		///
		/* 18h */	virtual size_t GetDataEnd();

		///
		/// Adds all the files that match the criteria to the given vector.
		/// The given filter will be applied on all the file names contained in this PFIndex.
		/// If a file matches the criteria, its name (as a ResourceKey) will be added to the vector.
		/// @param[out] dstVector The destination vector where the matching file names will be added.
		/// @param filter The RequestFilter used to decide which file names must be added into the vector.
		/// @returns The number of file names added to the vector.
		///
		/* 1Ch */	virtual size_t GetFiles(eastl::vector<ResourceKey>& dstVector, IKeyFilter* filter = nullptr);

		/// 
		/// Adds all the file names (as ResourceKeys) in this PFIndex to the given vector.
		/// @param[out] dstVector The destination vector where the file names will be added.
		/// @returns The number of file names added to the vector.
		///
		/* 20h */	virtual size_t GetAllFiles(eastl::vector<ResourceKey>& dstVector);

		/* 24h */	virtual bool func24h(int, size_t fileDataBegin, size_t fileDataEnd);

		///
		/// Returns the DBPFItem for the given file name, or NULL if the PFIndex does not contain that file.
		///
		/* 28h */	virtual RecordInfo* GetFileInfo(const ResourceKey& fileName);

		///
		/// Assigns the given file info to the specified file name.
		/// If the PFIndex does not contain a file with that name, a new entry will be created.
		///
		/* 2Ch */	virtual RecordInfo& PutFileInfo(const ResourceKey& fileName, RecordInfo& info);

		/// 
		/// Removes the specified file from this PFIndex, if it exists.
		/// @param fileName The ResourceKey name of the file to be removed.
		/// @param[out] dstInfo The destination DBPFItem that will be filled with the old information of the file, if it existed.
		/// @returns True if the file was removed successfully, false if the file did not exist.
		///
		/* 30h */	virtual bool RemoveFile(const ResourceKey& fileName, RecordInfo& dstInfo);

		///
		/// Reads the index items from the given buffer. It will be read according to the DBPF format. 
		/// nIndexCount items will be read. The buffer is expected to have a size equal to nIndexSize.
		/// @returns true if all the items were successfully read, false otherwise.
		///
		/* 34h */	virtual bool Read(void* pIndexData, size_t nIndexSize, size_t nIndexCount, bool);  // if last argument is true, sets the 0x10000 flag to every item

		///
		/// Creates a buffer to store the items and writes the index information on it.
		/// @param[out] pDstIndexData The void* that will be assigned with the pointer to the buffer containing the written information.
		/// @param[out] pDstIndexSize The size_t that will be assigned with the size of the created buffer.
		/// @param[in] nIndexCount The number of items to write.
		/// @returns true if all the items were successfully written, false otherwise.
		///
		/* 38h */	virtual bool Write(void*& pDstIndexData, size_t& nDstIndexSize, size_t nIndexCount, bool arg_C);  // if last argument is true, sets the 0x10000 flag to every item

		///
		/// Sets the mIsSaved value of all files to true, meaning that the files have already been written into a DatabasePackedFile stream.
		///
		/* 3Ch */	virtual void SetIsSaved();

		///
		/// Tells whether the data of the files in this PFIndex are contained between the given range.
		///
		/* 40h */	virtual bool CheckFilesInRange(size_t fileDataBegin, size_t fileDataEnd);

		///
		/// Tells whether the data of the files in this PFIndex are contained between the given range.
		///
		/* 44h */	virtual bool CheckFilesInSizeRange(size_t fileDataBegin, size_t size);



	protected:

		/* 04h */	ICoreAllocator*		mpParentAllocator;
		/* 08h */	FixedPoolAllocator	mAllocator;
		/* 28h */	ItemsMap			mItemsMap;

	};
	ASSERT_SIZE(PFIndexModifiable, 0x4C);

	namespace Addresses(PFIndexModifiable)
	{
		DeclareAddress(func04h);
		DeclareAddress(IsEmpty);
		DeclareAddress(GetFileCount);
		DeclareAddress(Reset);
		DeclareAddress(GetTotalDiskSize);
		DeclareAddress(GetDataEnd);
		DeclareAddress(GetFiles);
		DeclareAddress(GetAllFiles);
		DeclareAddress(func24h);
		DeclareAddress(GetFileInfo);
		DeclareAddress(PutFileInfo);
		DeclareAddress(RemoveFile);
		DeclareAddress(Read);
		DeclareAddress(Write);
		DeclareAddress(SetIsSaved);
		DeclareAddress(CheckFilesInRange);
		DeclareAddress(CheckFilesInSizeRange);
	}

}