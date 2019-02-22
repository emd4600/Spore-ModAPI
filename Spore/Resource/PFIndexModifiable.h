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
#include <Spore\Resource\IResourceFilter.h>
#include <Spore\FixedPoolAllocator.h>
#include <Spore\CoreAllocatorAdapter.h>
#include <Spore\IO\EAIOZoneObject.h>

namespace Resource
{
	///
	/// A structure that contains the metadata of a file stored in a DBPF, such as the offset in the package file and the size.
	///
	struct DBPFItem
	{
		/// The offset, in bytes, of the file data inside the package file.
		size_t mnChunkOffset;
		/// The size, in bytes, that this file occupies inside the package file.
		size_t mnCompressedSize;
		/// The size, in bytes, that this file occupies in memory, once uncompressed.
		size_t mnMemorySize;
		/// 0 -> no compression, -1 -> compressed
		short mFlags;  // 0xFFFF for compressed
		/// Whether this item has been saved and written into the package.
		bool mIsSaved;
	};

	///
	/// This class stores the metadata of all the files contained in a DBPF file. It is used for indexing and accessing
	/// files.
	///
	class PFIndexModifiable : public IO::EAIOZoneObject
	{
	public:
		
		typedef eastl::hash_map<ResourceKey, DBPFItem, ICoreAllocatorAdapter> ItemsMap;
		typedef eastl::vector<ResourceKey> KeysVector;

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
		/* 1Ch */	virtual size_t GetFiles(KeysVector& dstVector, IResourceFilter* filter = nullptr);

		/// 
		/// Adds all the file names (as ResourceKeys) in this PFIndex to the given vector.
		/// @param[out] dstVector The destination vector where the file names will be added.
		/// @returns The number of file names added to the vector.
		///
		/* 20h */	virtual size_t GetAllFiles(KeysVector& dstVector);

		/* 24h */	virtual bool func24h(int, size_t fileDataBegin, size_t fileDataEnd);

		///
		/// Returns the DBPFItem for the given file name, or NULL if the PFIndex does not contain that file.
		///
		/* 28h */	virtual DBPFItem* GetFileInfo(const ResourceKey& fileName);

		///
		/// Assigns the given file info to the specified file name.
		/// If the PFIndex does not contain a file with that name, a new entry will be created.
		///
		/* 2Ch */	virtual DBPFItem& PutFileInfo(const ResourceKey& fileName, DBPFItem& info);

		/// 
		/// Removes the specified file from this PFIndex, if it exists.
		/// @param fileName The ResourceKey name of the file to be removed.
		/// @param[out] dstInfo The destination DBPFItem that will be filled with the old information of the file, if it existed.
		/// @returns True if the file was removed successfully, false if the file did not exist.
		///
		/* 30h */	virtual bool RemoveFile(const ResourceKey& fileName, DBPFItem& dstInfo);

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

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(PFIndexModifiable) == 0x4C, "sizeof(PFIndexModifiable) != 4Ch");

	namespace InternalAddressList(PFIndexModifiable)
	{
		DefineAddress(func04h, GetAddress(0xA37650, 0xB1FB00, 0xB1FB30));
		DefineAddress(IsEmpty, GetAddress(0x8DBCE0, 0x6BF430, 0x6BF430));
		DefineAddress(GetFileCount, GetAddress(0xA654F0, 0x8E8220, 0x8E8230));
		DefineAddress(Reset, GetAddress(0x8DBCF0, 0x8DBA90, 0x8DBAA0));
		DefineAddress(GetTotalDiskSize, GetAddress(0x8DB570, 0x8DB2B0, 0x8DB2C0));
		DefineAddress(GetDataEnd, GetAddress(0x8DB510, 0x8DB250, 0x8DB260));
		DefineAddress(GetFiles, GetAddress(0x8DC250, 0x8DBFF0, 0x8DC000));
		DefineAddress(GetAllFiles, GetAddress(0x8DC310, 0x8DC0B0, 0x8DC0C0));
		DefineAddress(func24h, GetAddress(0x8DC810, 0x8DC5B0, 0x8DC5C0));
		DefineAddress(GetFileInfo, GetAddress(0x8DBD70, 0x8DBB10, 0x8DBB20));
		DefineAddress(PutFileInfo, GetAddress(0x8DC410, 0x8DC1B0, 0x8DC1C0));
		DefineAddress(RemoveFile, GetAddress(0x8DBDB0, 0x8DBB50, 0x8DBB60));
		DefineAddress(Read, GetAddress(0x8DBF10, 0x8DBCB0, 0x8DBCC0));
		DefineAddress(Write, GetAddress(0x8DB5C0, 0x8DB300, 0x8DB310));
		DefineAddress(SetIsSaved, GetAddress(0x8DB800, 0x8DB540, 0x8DB550));
		DefineAddress(CheckFilesInRange, GetAddress(0x8DB850, 0x8DB590, 0x8DB5A0));
		DefineAddress(CheckFilesInSizeRange, GetAddress(0x8DB8E0, 0x8DB620, 0x8DB630));
	}

}