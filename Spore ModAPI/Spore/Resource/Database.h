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

#include <Spore\Resource\IResourceFilter.h>
#include <Spore\Resource\IRecord.h>
#include <Spore\Resource\RecordInfo.h>
#include <Spore\IO\EAIOZoneObject.h>
#include <Spore\IO\IStream.h>
#include <Spore\ICoreAllocator.h>
#include <Spore\Object.h>
#include <EASTL\vector.h>

#define DatabasePtr eastl::intrusive_ptr<Resource::Database>

namespace Resource
{
	class IResourceManager;

	class Database 
		: public IO::EAIOZoneObject
		, public Object
	{
	public:
		/* 04h */	virtual bool Initialize() = 0;
		/* 08h */	virtual bool Dispose() = 0;
		/* 0Ch */	virtual uint32_t GetDatabaseType() const = 0;
		/* 10h */	virtual int GetRefCount() const = 0;
		/* 14h */	virtual void Lock(bool lock) = 0;
		/* 18h */	virtual bool Open(IO::AccessFlags desiredAccess = IO::AccessFlags::Read, IO::CD createDisposition = IO::CD::Default, bool arg_8 = false) = 0;
		/* 1Ch */	virtual bool Close() = 0;
		/* 20h */	virtual IO::AccessFlags GetAccessFlags() const = 0;
		/* 24h */	virtual bool Flush() = 0;
		/* 28h */	virtual const char16_t* GetLocation() const = 0;
		/* 2Ch */	virtual bool SetLocation(const char16_t* path) = 0;
		/* 30h */	virtual size_t GetKeyList(eastl::vector<ResourceKey>& dstVector, IResourceFilter* filter = nullptr) = 0;
		/* 34h */	virtual bool OpenRecord(
			const ResourceKey& name,
			IRecord** ppDst,
			IO::AccessFlags desiredAccess = IO::AccessFlags::Read, 
			IO::CD createDisposition = IO::CD::Default,
			bool arg_10 = true,
			RecordInfo* pDstInfo = nullptr) = 0;
		/* 38h */	virtual int GetOpenCount(const ResourceKey& key) = 0;
		/* 3Ch */	virtual bool CloseRecord(IRecord* pRecord) = 0;
		/* 40h */	virtual bool DeleteRecord(const ResourceKey& name) = 0;
		/* 44h */	virtual bool Attach(bool, IResourceManager* pResourceMan, bool) = 0;
		/* 48h */	virtual ICoreAllocator* GetAllocator() const = 0;

		virtual int AddRef() override;
		virtual int Release() override;

	public:
		int mnRefCount;
	};
	ASSERT_SIZE(Database, 0xC);
}
