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
#include "stdafx.h"
#include "FilePFRecord.h"

#include <EASTL\internal\thread_support.h>

FilePFRecord::FilePFRecord(DBPFItem& itemInfo, const ResourceKey& name, DatabasePackedFile* pParentDBPF)
	: IPFRecord(FilePFRecord::kType, name, pParentDBPF, IO::kAccessFlagRead)
	, mFileStream()
	, mnStreamRefCount(1)
	, mItemInfo(itemInfo)
	, mbStreamOpened(false)
{
	mFileStream.AddRef();
}


FilePFRecord::FilePFRecord(FilePFRecord* pOther, const ResourceKey& name, DatabasePackedFile* pParentDBPF)
	: IPFRecord(FilePFRecord::kType, name, pParentDBPF, IO::kAccessFlagRead)
	, mFileStream()
	, mnStreamRefCount(1)
	, mItemInfo(pOther->mItemInfo)
	, mbStreamOpened(false)
{
	mFileStream.AddRef();
}


FilePFRecord::~FilePFRecord()
{
	//if (mnFileAccess != kAccessFlagNone)
	//{
	//	mpParentDBPF->func3Ch(this);
	//}
}

ResourceKey& FilePFRecord::GetName()
{
	return this->mNameKey;
}

void FilePFRecord::SetName(const ResourceKey& name)
{
	this->mNameKey = name;
}

IO::IStream* FilePFRecord::GetStream()
{
	if (!mbStreamOpened)
	{
		mbStreamOpened = mFileStream.Open(mnFileAccess, IO::kCDOpenExisting);
	}
	return this;
}

DatabasePackedFile* FilePFRecord::GetParentDBPF() const
{
	return mpParentDBPF;
}

bool FilePFRecord::Open()
{
	if (!mbStreamOpened)
	{
		mbStreamOpened = mFileStream.Open(mnFileAccess, IO::kCDOpenExisting);
	}

	eastl::Internal::atomic_increment(&mnStreamRefCount);

	return mbStreamOpened;
}

bool FilePFRecord::Close()
{
	if (eastl::Internal::atomic_decrement(&mnStreamRefCount) == 0)
	{
		if (mnFileAccess != IO::kAccessFlagNone)
		{
			mpParentDBPF->func3Ch(this);
		}
	}

	return true;
}

int FilePFRecord::func28h()
{
	mnStreamRefCount = 0;  // ?
	return mnStreamRefCount;
}

void FilePFRecord::SetPath(const char16_t* pPath)
{
	mFileStream.SetPath(pPath);
}

uint32_t FilePFRecord::GetType() const
{
	return mnType;
}

int FilePFRecord::GetAccessFlags() const
{
	return mnFileAccess;
}

IO::FileError FilePFRecord::GetState() const
{
	return mFileStream.GetState();
}

IO::size_type FilePFRecord::GetSize() const
{
	return mFileStream.GetSize();
}

bool FilePFRecord::SetSize(IO::size_type size)
{
	return false;
}

int FilePFRecord::GetPosition(IO::PositionType positionType) const
{
	return mFileStream.GetPosition(positionType);
}

bool FilePFRecord::SetPosition(int distance, IO::PositionType positionType)
{
	return mFileStream.SetPosition(distance, positionType);
}


int	FilePFRecord::GetAvailable() const
{
	return mFileStream.GetAvailable();
}

int FilePFRecord::Read(void* pData, size_t nSize)
{
	return mFileStream.Read(pData, nSize);
}

bool FilePFRecord::Flush()
{
	return true;
}

int FilePFRecord::Write(const void* pData, size_t nSize)
{
	return 0;
}

int FilePFRecord::AddRef()
{
	return ThreadedObject::AddRef();
}
int FilePFRecord::Release()
{
	return ThreadedObject::Release();
}