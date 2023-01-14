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

#include <Spore\Resource\PFRecordBase.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\IO\FileStream.h>
#include <Spore\IO\StreamMemory.h>

#define PFRecordWritePtr eastl::intrusive_ptr<Resource::PFRecordWrite>

namespace Resource
{
	///
	/// This class is used to write data to a file contained inside a DBPF. Use PFRecordRead::GetStream() to get the
	/// IStream that can be used to write the file.
	///
	class PFRecordWrite : public PFRecordBase, IO::IStream
	{
	public:
		static const uint32_t kType = 0x12E4A892;

		PFRecordWrite(void* pData, size_t nSize, bool bUsePointer, ResourceKey& name, DatabasePackedFile* pParentDBPF);
		PFRecordWrite(size_t nChunkOffset, size_t nSize, bool bUsePointer, ResourceKey& name, DatabasePackedFile* pParentDBPF);

		virtual ~PFRecordWrite();
		virtual int AddRef() override;
		virtual int Release() override;

		//// IRecord ////

		/* 10h */	virtual const ResourceKey&	GetKey() override;
		/* 14h */	virtual void			SetKey(const ResourceKey& name) override;

		/* 18h */	virtual IO::IStream* GetStream() override;

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

	protected:
		/* 24h */	IO::MemoryStream field_24;
		/* 48h */	IO::FileStream field_48;
		/* 274h */	bool field_274;
		/* 278h */	int mnStreamRefCount;  // decreased when calling Close()
	};
	ASSERT_SIZE(PFRecordWrite, 0x27C);
	
	namespace Addresses(PFRecordWrite)
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

		DeclareAddress(GetKey);
		DeclareAddress(SetKey);
		DeclareAddress(GetDatabase);
		DeclareAddress(RecordOpen);
		DeclareAddress(RecordClose);
		DeclareAddress(DoPostClose);

	}

}

