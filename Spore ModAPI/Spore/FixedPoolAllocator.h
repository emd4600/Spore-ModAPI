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

	virtual void *Alloc(size_t size, const char *name, unsigned int flags);
	virtual void *Alloc(size_t size, const char *name, unsigned int flags, unsigned int align, unsigned int alignOffset = 0);
	virtual void Free(void *block, size_t size = 0);

protected:
	ICoreAllocator* mpAllocator;  // another allocator?
	int field_8;
	int field_C;
	int field_10;
	size_t mnObjectSize;
	int field_18;
	int field_1C;
};

typedef CoreAllocatorAdapter<FixedPoolAllocator> FixedPoolAllocatorAdapter;


///////////////////////////////////
//// INTERNAL IMPLEMENENTATION ////
///////////////////////////////////

static_assert(sizeof(FixedPoolAllocator) == 0x20, "sizeof(FixedPoolAllocator) != 20h");

namespace Addresses(FixedPoolAllocator)
{
	DeclareAddress(dtor, SelectAddress(0x926360, 0x9260F0, 0x9260F0));
	DeclareAddress(Alloc, SelectAddress(0x926370, 0x926100, 0x926100));
	DeclareAddress(Alloc_, SelectAddress(0x926490, 0x926220, 0x926220));
	DeclareAddress(Free, SelectAddress(0x9263B0, 0x926140, 0x926140));
}
