/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\Object.h>
#include <Spore\Resource\ResourceObject.h>
#include <EASTL\internal\thread_support.h>

using namespace Resource;

///////////////////////////////////
//// INTERNAL IMPLEMENENTATION ////
///////////////////////////////////

//// DefaultObject ////


int DefaultObject::AddRef()
{
	return mnRefCount++;
}
int DefaultObject::Release()
{
	int refCount = --mnRefCount;
	if (refCount <= 0)
	{
		delete this;
		return 0;
	}
	return mnRefCount;
}
void* DefaultObject::Cast(uint32_t typeID) const
{
	return (DefaultObject*)this;
}

//// DefaultRefCounted ////


int DefaultRefCounted::AddRef()
{
	return mnRefCount++;
}
int DefaultRefCounted::Release()
{
	int refCount = --mnRefCount;
	if (refCount <= 0)
	{
		delete this;
		return 0;
	}
	return refCount;
}
int DefaultRefCounted::GetReferenceCount()
{
	return mnRefCount;
}

//// ResourceObject ////


int ResourceObject::AddRef()
{
	return eastl::Internal::atomic_increment(&mnRefCount);
}

int ResourceObject::Release()
{
	if (eastl::Internal::atomic_decrement(&mnRefCount) == 0)
	{
		delete this;
		return 0;
	}
	return mnRefCount;
}

void* ResourceObject::Cast(uint32_t typeID) const
{
	if (typeID == Object::TYPE)
	{
		return (Object*) this;
	}
	else if (typeID == ResourceObject::TYPE)
	{
		return (ResourceObject*) this;
	}
	else
	{
		return nullptr;
	}
}

int ResourceObject::GetReferenceCount()
{
	return mnRefCount;
}

//// ResourceObject ////

int CachedResourceObject::AddRef()
{
	mnRefCount += 2;
	return mnRefCount / 2;
}

int CachedResourceObject::Release()
{
	mnRefCount -= 2;
	if (mnRefCount == 0)
	{
		mnRefCount = 2;
		delete this;
		return 0;
	}
	else if (mnRefCount == 3 && mpManager)
	{
		mpManager->Delete(this);
	}

	return mnRefCount;
}

void* CachedResourceObject::Cast(uint32_t typeID) const
{
	if (typeID == Object::TYPE)
	{
		return (Object*) this;
	}
	else if (typeID == CachedResourceObject::TYPE)
	{
		return (CachedResourceObject*) this;
	}
	else if (typeID == ResourceObject::TYPE)
	{
		return (ResourceObject*) this;
	}
	else
	{
		return nullptr;
	}
}

int CachedResourceObject::GetReferenceCount()
{
	return mnRefCount / 2;
}

static_assert(sizeof(CachedResourceObject) == 0x18, "sizeof(ResourceObject) must be 18h");

int MultithreadObject::AddRef()
{
	return eastl::Internal::atomic_increment(&mnRefCount);
}

int MultithreadObject::Release()
{
	int refCount = eastl::Internal::atomic_decrement(&mnRefCount);
	if (refCount == 0)
	{
		mnRefCount = 1;
		delete this;
		return 0;
	}
	return refCount;
}


int BasicLockRefCounted::AddRef()
{
	return eastl::Internal::atomic_increment(&mnRefCount);
}

int BasicLockRefCounted::Release()
{
	int refCount = eastl::Internal::atomic_decrement(&mnRefCount);
	if (refCount == 0)
	{
		mnRefCount = 1;
		delete this;
		return 0;
	}
	return refCount;
}