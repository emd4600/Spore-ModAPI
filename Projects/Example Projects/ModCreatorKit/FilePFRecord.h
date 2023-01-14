/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModCreatorKit.
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

using namespace Resource;

class FilePFRecord 
	: public PFRecordBase
	, IO::IStream
{
public:
	FilePFRecord(RecordInfo& itemInfo, const ResourceKey& name, DatabasePackedFile* pParentDBPF);
	FilePFRecord(FilePFRecord* pOther, const ResourceKey& name, DatabasePackedFile* pParentDBPF);

	virtual ~FilePFRecord();
	virtual int AddRef() override;
	virtual int Release() override;

	virtual void SetPath(const char16_t* pPath);

	//// IPFRecord ////

	/* 10h */	virtual ResourceKey&	GetKey() override;
	/* 14h */	virtual void			SetKey(const ResourceKey& name) override;

	/* 18h */	virtual IStream* GetStream() override;

	/* 1Ch */	virtual Database* GetDatabase() override;

	/* 20h */	virtual bool RecordOpen() override;
	/* 24h */	virtual bool RecordClose() override;
	/* 28h */	virtual int DoPostClose() override;

	//// IStream ////

	virtual bool Close() override;
	/* 0Ch */	virtual uint32_t	GetType() const override;
	/* 10h */	virtual IO::AccessFlags	GetAccessFlags() const override;
	/* 14h */	virtual IO::FileError	GetState() const override;

	/* 1Ch */	virtual IO::size_type	GetSize() const override;
	/* 20h */	virtual bool		SetSize(IO::size_type size) override;  // does nothing
	/* 24h */	virtual int			GetPosition(IO::PositionType positionType = IO::PositionType::Begin) const override;
	/* 28h */	virtual bool		SetPosition(int distance, IO::PositionType positionType = IO::PositionType::Begin) override;
	/* 2Ch */	virtual int			GetAvailable() const override;

	/* 30h */	virtual int		Read(void* pData, size_t nSize) override;
	/* 34h */	virtual bool	Flush() override;  // does nothing
	/* 38h */	virtual int		Write(const void* pData, size_t nSize) override;  // does nothing

	static const uint32_t kType = 0x4CF999A2;  // id("FilePFRecord")

protected:
	IO::FileStream mFileStream;
	int mnStreamRefCount;
	bool mbStreamOpened;
	RecordInfo mItemInfo;
};

