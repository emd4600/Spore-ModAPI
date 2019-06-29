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

#include <Spore\Resource\IPFRecord.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\IO\FileStream.h>
#include <Spore\IO\StreamMemory.h>

namespace Resource
{
	using IO::IStream;

	///
	/// This class is used to write data to a file contained inside a DBPF. Use PFRecordRead::GetStream() to get the
	/// IStream that can be used to write the file.
	///
	class PFRecordWrite : public IPFRecord, IO::IStream
	{
	public:
		friend class DatabasePackedFile;

		static const uint32_t kType = 0x12E4A892;

		PFRecordWrite(void* pData, size_t nSize, bool bUsePointer, ResourceKey& name, DatabasePackedFile* pParentDBPF);
		PFRecordWrite(size_t nChunkOffset, size_t nSize, bool bUsePointer, ResourceKey& name, DatabasePackedFile* pParentDBPF);

		virtual ~PFRecordWrite();
		virtual int AddRef() override;
		virtual int Release() override;

		//// IPFRecord ////

		/* 10h */	virtual ResourceKey&	GetName() override;
		/* 14h */	virtual void			SetName(const ResourceKey& name) override;

		/* 18h */	virtual IO::IStream* GetStream() override;

		/* 1Ch */	virtual DatabasePackedFile* GetParentDBPF() const override;

		/* 20h */	virtual bool Open() override;
		/* 24h */	virtual bool Close() override;
		/* 28h */	virtual int func28h() override;

		//// IStream ////

		/* 0Ch */	virtual uint32_t	GetType() const override;
		/* 10h */	virtual int			GetAccessFlags() const override;
		/* 14h */	virtual IO::FileError	GetState() const override;
		// /* 18h */	virtual bool		Close() override;  // already overriden with IPFRecord

		/* 1Ch */	virtual IO::size_type	GetSize() const override;
		/* 20h */	virtual bool		SetSize(IO::size_type size) override;  // does nothing
		/* 24h */	virtual int			GetPosition(IO::PositionType positionType = IO::kPositionTypeBegin) const override;
		/* 28h */	virtual bool		SetPosition(int distance, IO::PositionType positionType = IO::kPositionTypeBegin) override;
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

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(PFRecordWrite) == 0x27C, "sizeof(PFRecordWrite) != 27Ch");

	
	namespace InternalAddressList(PFRecordWrite)
	{
		DefineAddress(GetName, GetAddress(0x6C07B0, 0x8DCA90, 0x8DCAA0));
		DefineAddress(SetName, GetAddress(0x8DCCC0, 0x6B4250, 0x6B4250));
		DefineAddress(GetStream, GetAddress(0x6C07C0, 0x8DC640, 0x8DC650));
		DefineAddress(GetParentDBPF, GetAddress(0xFC8510, 0x6C0230, 0x6C0230));
		DefineAddress(Open, GetAddress(0x8DD170, 0x8DCF50, 0x8DCF60));
		DefineAddress(Close, GetAddress(0x6C0F80, 0x6C09B0, 0x6C09B0));
		DefineAddress(func28h, GetAddress(0x6C0F20, 0x8DCEF0, 0x8DCF00));

		DefineAddress(GetType, GetAddress(0x8DCCE0, 0x6C04C0, 0x8DCAB0));
		DefineAddress(GetAccessFlags, GetAddress(0x8DCCF0, 0x8DC670, 0x8DC680));
		DefineAddress(GetState, GetAddress(0x1065680, 0xE31100, 0xE310C0));
		// DefineAddress(REMOVE_THIS_Close, GetAddress(0x66AD60, 0xB1E3E0, 0xB1E410));
		DefineAddress(GetSize, GetAddress(0x8DCD00, 0x8DCAB0, 0x8DCAC0));
		DefineAddress(SetSize, GetAddress(0x6C0A70, 0x8DCAE0, 0x8DCAF0));
		DefineAddress(GetPosition, GetAddress(0x8DCD30, 0x6C04D0, 0x6C04D0));
		DefineAddress(SetPosition, GetAddress(0x6C0AB0, 0x8DCB20, 0x8DCB30));
		DefineAddress(GetAvailable, GetAddress(0x8DCD70, 0x8DCB60, 0x8DCB70));
		DefineAddress(Read, GetAddress(0x8DCDA0, 0x6C0510, 0x6C0510));
		DefineAddress(Flush, GetAddress(0x8DCDE0, 0x6C0550, 0x6C0550));
		DefineAddress(Write, GetAddress(0x6C0AF0, 0x6C0580, 0x6C0580));

	}

}

