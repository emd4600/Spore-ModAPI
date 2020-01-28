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
#include <Spore\IO\IStream.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\ResourceKey.h>

#define IPFRecordPtr intrusive_ptr<Resource::IPFRecord>

namespace Resource
{
	// class DatabasePackedFile;

	///
	/// This interface defines the methods required to access the data of a file contained in a DBPF.
	///
	class IPFRecord : public ThreadedObject
	{
	public:
		friend class DatabasePackedFile;

		IPFRecord(uint32_t nType, const ResourceKey& name, DatabasePackedFile* pParentDBPF, int nFileAccess);


		uint32_t GetType() const;

		///
		/// Gets the ResourceKey name that identifies this record.
		///
		/* 10h */	virtual ResourceKey& GetName() = 0;

		///
		/// Sets the ResourceKey name that identifies this record.
		///
		/* 14h */	virtual void SetName(const ResourceKey& name) = 0;

		///
		/// Returns the IStream used to access this record data.
		///
		/* 18h */	virtual IO::IStream* GetStream() = 0;

		///
		/// Returns the DatabasePackedFile that this record belongs to.
		///
		/* 1Ch */	virtual DatabasePackedFile* GetParentDBPF() const = 0;

		/* 20h */	virtual bool Open() = 0;  // increases stream reference count
		/* 24h */	virtual bool Close() = 0;
		/* 28h */	virtual int func28h() = 0;

	protected:
		/* 08h */	uint32_t			mnType;
		/* 0Ch */	ResourceKey			mNameKey;
		/* 18h */	DatabasePackedFile* mpParentDBPF;
		/* 1Ch */	int					mnFileAccess;
	};

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	inline IPFRecord::IPFRecord(uint32_t nType, const ResourceKey& name, DatabasePackedFile* pParentDBPF, int nFileAccess)
		: mnType(nType)
		, mNameKey(name)
		, mpParentDBPF(pParentDBPF)
		, mnFileAccess(nFileAccess)
	{
	};

	inline uint32_t IPFRecord::GetType() const
	{
		return mnType;
	}
}