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

#include <Spore\Resource\IRecord.h>
#include <Spore\IO\IStream.h>
#include <Spore\ResourceKey.h>

#define PFRecordBasePtr eastl::intrusive_ptr<Resource::PFRecordBase>

namespace Resource
{
	class DatabasePackedFile;

	/// Base implementation for records in a `.package` file (DatabasePackedFile).
	class PFRecordBase 
		: public IRecord
	{
	public:
		PFRecordBase(uint32_t type, const ResourceKey& key, DatabasePackedFile* parentDBPF, IO::AccessFlags fileAccess);

		uint32_t GetType() const;

		/* 28h */	virtual int DoPostClose() = 0;

	protected:
		/* 08h */	uint32_t			mType;
		/* 0Ch */	ResourceKey			mNameKey;
		/* 18h */	DatabasePackedFile* mpParentDBPF;
		/* 1Ch */	IO::AccessFlags		mFileAccess;
	};

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	inline PFRecordBase::PFRecordBase(uint32_t nType, const ResourceKey& name, DatabasePackedFile* pParentDBPF, IO::AccessFlags nFileAccess)
		: mType(nType)
		, mNameKey(name)
		, mpParentDBPF(pParentDBPF)
		, mFileAccess(nFileAccess)
	{
	};

	inline uint32_t PFRecordBase::GetType() const
	{
		return mType;
	}
}