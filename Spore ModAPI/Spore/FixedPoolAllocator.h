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

#include <Spore\ICoreAllocator.h>
#include <Spore\CoreAllocatorAdapter.h>
#include <Spore\Internal.h>

#include <EASTL\internal\fixed_pool.h>

class FixedPoolAllocator : public ICoreAllocator
{

public:
	FixedPoolAllocator(ICoreAllocator* pAllocator, int arg_4, size_t objectSize);

	virtual ~FixedPoolAllocator();

#ifndef SDK_TO_GHIDRA
	virtual void *Alloc(size_t size, const char *name, unsigned int flags) override;
	virtual void *Alloc(size_t size, const char *name, unsigned int flags, unsigned int align, unsigned int alignOffset = 0) override;
#else
	virtual void *Alloc(size_t size, const char *name, unsigned int flags, unsigned int align, unsigned int alignOffset = 0) override;
	virtual void* Alloc(size_t size, const char* name, unsigned int flags) override;
	void* Alloc_(size_t size, const char* name, unsigned int flags);
#endif
	virtual void Free(void *block, size_t size = 0) override;

protected:
	ICoreAllocator* mpAllocator;  // another allocator?
	int field_8;
	int field_C;
	int field_10;
	size_t mnObjectSize;
	int field_18;
	int field_1C;
};
ASSERT_SIZE(FixedPoolAllocator, 0x20);

typedef CoreAllocatorAdapter<FixedPoolAllocator> FixedPoolAllocatorAdapter;

namespace Addresses(FixedPoolAllocator)
{
	DeclareAddress(dtor);
	DeclareAddress(Alloc);
	DeclareAddress(Alloc_);
	DeclareAddress(Free);
}
