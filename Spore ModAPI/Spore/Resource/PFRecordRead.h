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

#include <Spore\ResourceKey.h>
#include <Spore\IO\StreamMemory.h>
#include <Spore\Resource\RecordInfo.h>
#include <Spore\Resource\PFRecordBase.h>
#include <Spore\Resource\PFIndexModifiable.h>
#include <Spore\Resource\ThreadedObject.h>

#define PFRecordReadPtr eastl::intrusive_ptr<Resource::PFRecordRead>

namespace Resource
{
	///
	/// This class is used to read the data of a file contained inside a DBPF. Use PFRecordRead::GetStream() to get the
	/// IStream that can be used to read the file. If the file is compressed, it will be decompressed before reading it.
	///
	class PFRecordRead : public PFRecordBase, IO::IStream
	{
	public:
		static const uint32_t kType = 0x12E4A891;

	public:
		PFRecordRead(RecordInfo& itemInfo, const ResourceKey& name, DatabasePackedFile* pParentDBPF);
		PFRecordRead(PFRecordRead* pOther, const ResourceKey& name, DatabasePackedFile* pParentDBPF);

		virtual ~PFRecordRead();
		virtual int AddRef() override;
		virtual int Release() override;

		//// IRecord ////

		/* 10h */	virtual const ResourceKey&	GetKey() override;
		/* 14h */	virtual void				SetKey(const ResourceKey& name) override;

		/* 18h */	virtual IStream* GetStream() override;

		/* 1Ch */	virtual Database* GetDatabase() override;

		/* 20h */	virtual bool RecordOpen() override;
		/* 24h */	virtual bool RecordClose() override;
		/* 28h */	virtual int DoPostClose() override;

		//// IStream ////

		/* 0Ch */	virtual uint32_t	GetType() const override;
		/* 10h */	virtual IO::AccessFlags	GetAccessFlags() const override;
		/* 14h */	virtual IO::FileError	GetState() const override;
		// /* 18h */	virtual bool		Close() override;  // already overriden with IRecord

		/* 1Ch */	virtual IO::size_type	GetSize() const override;
		/* 20h */	virtual bool		SetSize(IO::size_type size) override;  // does nothing
		/* 24h */	virtual int			GetPosition(IO::PositionType positionType = IO::PositionType::Begin) const override;
		/* 28h */	virtual bool		SetPosition(int distance, IO::PositionType positionType = IO::PositionType::Begin) override;
		/* 2Ch */	virtual int			GetAvailable() const override;

		/* 30h */	virtual int		Read(void* pData, size_t nSize) override;
		/* 34h */	virtual bool	Flush() override;  // does nothing
		/* 38h */	virtual int		Write(const void* pData, size_t nSize) override;  // does nothing

	public:
		void ReadData();

	public:
		/* 24h */	int field_24;
		/* 28h */	int field_28;  // -1
		/* 2Ch */	IO::MemoryStream mInternalBuffer;
		/* 50h */	RecordInfo mDBPFItem;
		/* 60h */	size_t mnOffset;
		/* 64h */	size_t mnSize;
		/* 68h */	char mnFlags;  // if & 2, use internal stream?
		/* 6Ch */	int mnStreamRefCount;  // decreased when calling Close()

		enum Flags
		{
			kPFRRBufferReady = 2,
			kPFRRDataFitsBuffer = 1,
		};
	};
	ASSERT_SIZE(PFRecordRead, 0x70);

	namespace Addresses(PFRecordRead)
	{
		DeclareAddress(GetName);
		DeclareAddress(SetName);
		DeclareAddress(GetStream);
		DeclareAddress(GetParentDBPF);
		DeclareAddress(Open);
		DeclareAddress(Close);
		DeclareAddress(func28h);

		DeclareAddress(GetType);
		DeclareAddress(GetAccessFlags);
		DeclareAddress(GetState);
		// DeclareAddress(REMOVE_THIS_Close);
		DeclareAddress(GetSize);
		DeclareAddress(SetSize);
		DeclareAddress(GetPosition);
		DeclareAddress(SetPosition);
		DeclareAddress(GetAvailable);
		DeclareAddress(Read);
		DeclareAddress(Flush);
		DeclareAddress(Write);


		DeclareAddress(ReadData);

		DeclareAddress(GetKey);
		DeclareAddress(SetKey);
		DeclareAddress(GetDatabase);
		DeclareAddress(RecordOpen);
		DeclareAddress(RecordClose);
		DeclareAddress(DoPostClose);
	}
}
