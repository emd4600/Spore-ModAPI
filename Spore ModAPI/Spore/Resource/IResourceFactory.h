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

#include <Spore\Resource\ThreadedObject.h>
#include <Spore\Resource\IPFRecord.h>
#include <Spore\Resource\ResourceObject.h>

#include <EASTL\intrusive_ptr.h>

#define IResourceFactoryPtr eastl::intrusive_ptr<Resource::IResourceFactory>

using namespace eastl;

namespace Resource
{
	///
	/// An interface that can be used to create resources of certain types. Resource factories are mapped into the
	/// IResourceManager so that when a resource is accessed the correct object is returned (e.g. if you access a .png
	/// file, you get the Texture object directly). The resources created must inherit from ResourceObject.
	///
	class IResourceFactory : public ThreadedObject
	{
	public:

		/* 10h */	virtual bool Initialize() = 0;
		/* 14h */	virtual bool Dispose() = 0;
		/* 18h */	virtual uint32_t GetType() = 0;

		///
		/// Creates a new resource of the specified type, using the file record given.
		/// @param pRecord The IPFRecord that points to the file used by the resource (either for reading or for writing).
		/// @param[out] pDst A pointer where the ResourceObject created must be written.
		/// @param typeID The type ID of the file to read, which might be used to differentiate between different file formats or resource types.
		///
		/* 1Ch */	virtual bool CreateResource(IPFRecord* pRecord, ResourceObjectPtr& pDst, int, uint32_t typeID) = 0;
		/* 20h */	virtual bool AsyncAccess(IPFRecord** ppDst, int, DBPF* pDBPF, int, int, int) = 0;  // ? renamed this to avoid name collisions in cPropManager...

		///
		/// Reads the data into the resource given.
		/// @param pRecord The IPFRecord that points to the file that must be read.
		/// @param pResource The ResourceObject where the data must be loaded.
		/// @param typeID The type ID of the file to read, which might be used to differentiate between different file formats.
		///
		/* 24h */	virtual bool Read(IPFRecord* pRecord, ResourceObject* pResource, int, uint32_t typeID) = 0;

		///
		/// Reads the resource into the file given.
		/// @param pResource The ResourceObject that must be saved.
		/// @param pRecord The IPFRecord that points to the file that must be written.
		/// @param typeID The type ID of the file to write, which might be used to differentiate between different file formats.
		///
		/* 28h */	virtual bool Write(ResourceObject* pResource, IPFRecord* pRecord, int, uint32_t typeID) = 0;

		///
		/// This method must tell all the type IDs that are accepted by this factory. The method must return how many type IDs
		/// are supported.
		/// @param[out] pDstTypes The uint32_t array where the type IDs must be written.
		/// @param count The size of the pDstTypes array.
		/// @returns How many type IDs are supported.
		///
		/* 2Ch */	virtual size_t GetSupportedTypes(uint32_t* pDstTypes, size_t count) const = 0;

		///
		/// This method must tell whether this type ID (which might be a generic one, e.g. .image) and the sub type ID 
		/// (e.g. .png) are accepted by this factory. The subtypeID might be 0, in which case only the type ID matters.
		/// @param typeID
		/// @param subTypeID
		///
		/* 30h */	virtual bool IsValid(uint32_t typeID, uint32_t subTypeID) = 0;
	};
}