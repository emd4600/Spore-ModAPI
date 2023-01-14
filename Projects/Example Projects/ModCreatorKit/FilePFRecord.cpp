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

FilePFRecord::FilePFRecord(RecordInfo& itemInfo, const ResourceKey& name, DatabasePackedFile* pParentDBPF)
	: PFRecordBase(FilePFRecord::kType, name, pParentDBPF, IO::AccessFlags::Read)
	, mFileStream()
	, mnStreamRefCount(1)
	, mItemInfo(itemInfo)
	, mbStreamOpened(false)
{
	mFileStream.AddRef();
}


FilePFRecord::FilePFRecord(FilePFRecord* pOther, const ResourceKey& name, DatabasePackedFile* pParentDBPF)
	: PFRecordBase(FilePFRecord::kType, name, pParentDBPF, IO::AccessFlags::Read)
	, mFileStream()
	, mnStreamRefCount(1)
	, mItemInfo(pOther->mItemInfo)
	, mbStreamOpened(false)
{
	mFileStream.AddRef();
}


FilePFRecord::~FilePFRecord()
{
	if (mFileAccess != IO::AccessFlags::None)
	{
		mpParentDBPF->CloseRecord(this);
		mFileStream.Close();
		mFileAccess = IO::AccessFlags::None;
	}
}

ResourceKey& FilePFRecord::GetKey()
{
	return this->mNameKey;
}

void FilePFRecord::SetKey(const ResourceKey& name)
{
	this->mNameKey = name;
}

IO::IStream* FilePFRecord::GetStream()
{
	if (!mbStreamOpened)
	{
		mbStreamOpened = mFileStream.Open(mFileAccess, IO::CD::OpenExisting);
	}
	return this;
}

Database* FilePFRecord::GetDatabase()
{
	return mpParentDBPF;
}

bool FilePFRecord::RecordOpen()
{
	if (!mbStreamOpened)
	{
		mbStreamOpened = mFileStream.Open(mFileAccess, IO::CD::OpenExisting);
	}

	eastl::Internal::atomic_increment(&mnStreamRefCount);

	return mbStreamOpened;
}

bool FilePFRecord::RecordClose()
{
	if (eastl::Internal::atomic_decrement(&mnStreamRefCount) == 0)
	{
		if (mFileAccess != IO::AccessFlags::None)
		{
			mpParentDBPF->CloseRecord(this);
			mFileStream.Close();
			mFileAccess = IO::AccessFlags::None;
		}
	}

	return true;
}

bool FilePFRecord::Close()
{
	if (eastl::Internal::atomic_decrement(&mnStreamRefCount) == 0)
	{
		if (mFileAccess != IO::AccessFlags::None)
		{
			mpParentDBPF->CloseRecord(this);
			mFileStream.Close();
			mFileAccess = IO::AccessFlags::None;
		}
	}

	return true;
}

int FilePFRecord::DoPostClose()
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
	return mType;
}

IO::AccessFlags FilePFRecord::GetAccessFlags() const
{
	return mFileAccess;
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