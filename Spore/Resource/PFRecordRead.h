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
#include <Spore\Resource\IPFRecord.h>
#include <Spore\Resource\PFIndexModifiable.h>
#include <Spore\Resource\ThreadedObject.h>

namespace Resource
{
	using IO::IStream;

	///
	/// This class is used to read the data of a file contained inside a DBPF. Use PFRecordRead::GetStream() to get the
	/// IStream that can be used to read the file. If the file is compressed, it will be decompressed before reading it.
	///
	class PFRecordRead : public IPFRecord, IStream
	{
	public:
		friend class DatabasePackedFile;

		static const uint32_t kType = 0x12E4A891;

	public:
		PFRecordRead(DBPFItem& itemInfo, const ResourceKey& name, DatabasePackedFile* pParentDBPF);
		PFRecordRead(PFRecordRead* pOther, const ResourceKey& name, DatabasePackedFile* pParentDBPF);

		virtual ~PFRecordRead();
		virtual int AddRef() override;
		virtual int Release() override;

		//// IPFRecord ////

		/* 10h */	virtual ResourceKey&	GetName() override;
		/* 14h */	virtual void			SetName(const ResourceKey& name) override;

		/* 18h */	virtual IStream* GetStream() override;

		/* 1Ch */	virtual DatabasePackedFile* GetParentDBPF() const override;

		/* 20h */	virtual bool Open() override;
		/* 24h */	virtual bool Close() override;
		/* 28h */	virtual int func28h() override;

		//// IStream ////

		/* 0Ch */	virtual uint32_t	GetType() const override;
		/* 10h */	virtual int			GetAccessFlags() const override;
		/* 14h */	virtual FileError	GetState() const override;
		// /* 18h */	virtual bool		Close() override;  // already overriden with IPFRecord

		/* 1Ch */	virtual size_type	GetSize() const override;
		/* 20h */	virtual bool		SetSize(size_type size) override;  // does nothing
		/* 24h */	virtual int			GetPosition(PositionType positionType = kPositionTypeBegin) const override;
		/* 28h */	virtual bool		SetPosition(int distance, PositionType positionType = kPositionTypeBegin) override;
		/* 2Ch */	virtual int			GetAvailable() const override;

		/* 30h */	virtual int		Read(void* pData, size_t nSize) override;
		/* 34h */	virtual bool	Flush() override;  // does nothing
		/* 38h */	virtual int		Write(const void* pData, size_t nSize) override;  // does nothing

	protected:
		void ReadData();

	protected:
		/* 24h */	int field_24;
		/* 28h */	int field_28;  // -1
		/* 2Ch */	MemoryStream mInternalBuffer;
		/* 50h */	DBPFItem mDBPFItem;
		/* 60h */	size_t mnOffset;
		/* 64h */	size_t mnSize;
		/* 68h */	char mnFlags;  // if & 2, use internal stream?
		/* 6Ch */	int mnStreamRefCount;  // decreased when calling Close()

		enum
		{
			kPFRRBufferReady = 2,
			kPFRRDataFitsBuffer = 1,
		};
	};

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	static_assert(sizeof(PFRecordRead) == 0x70, "sizeof(PFRecordRead) != 70h");


	namespace InternalAddressList(PFRecordRead)
	{
		DefineAddress(GetName, GetAddress(0x6C07B0, 0x8DCA90, 0x8DCAA0));
		DefineAddress(SetName, GetAddress(0x8DCCC0, 0x6B4250, 0x6B4250));
		DefineAddress(GetStream, GetAddress(0x6C07C0, 0x8DC640, 0x8DC650));
		DefineAddress(GetParentDBPF, GetAddress(0xFC8510, 0x6C0230, 0x6C0230));
		DefineAddress(Open, GetAddress(0x8DCFD0, 0x6C0810, 0x8DCD60));
		DefineAddress(Close, GetAddress(0x8DCFF0, 0x6C0830, 0x8DCD80));
		DefineAddress(func28h, GetAddress(0x8DCF80, 0x6C07C0, 0x8DCD10));

		DefineAddress(GetType, GetAddress(0x8DC8A0, 0x6C0240, 0x8DC670));
		DefineAddress(GetAccessFlags, GetAddress(0x8DCCF0, 0x8DC670, 0x8DC680));
		DefineAddress(GetState, GetAddress(0x1065680, 0xE31100, 0xE310C0));
		// DefineAddress(REMOVE_THIS_Close, GetAddress(0x6C07D0, 0x8DC650, 0x8DC660));
		DefineAddress(GetSize, GetAddress(0x113BA60, 0xBB9C20, 0x113AE80));
		DefineAddress(SetSize, GetAddress(0x101B0F0, 0xDDE980, 0xDDE930));
		DefineAddress(GetPosition, GetAddress(0x8DC8B0, 0x6C0250, 0x8DC690));
		DefineAddress(SetPosition, GetAddress(0x8DD030, 0x6C0870, 0x8DCDC0));
		DefineAddress(GetAvailable, GetAddress(0x8DC8F0, 0x6C0290, 0x8DC6D0));
		DefineAddress(Read, GetAddress(0x8DD0F0, 0x6C0930, 0x8DCE80));
		DefineAddress(Flush, GetAddress(0xA37650, 0xB1FB00, 0xB1FB30));
		DefineAddress(Write, GetAddress(0x951320, 0x950E00, 0x950E00));


		DefineAddress(ReadData, GetAddress(0x8DCA40, 0x6C03F0, 0x8DC820));
	}
}
