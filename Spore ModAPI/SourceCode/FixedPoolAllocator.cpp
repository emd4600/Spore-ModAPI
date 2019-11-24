#ifndef MODAPI_DLL_EXPORT
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

#include <Spore\FixedPoolAllocator.h>

FixedPoolAllocator::FixedPoolAllocator(ICoreAllocator* pAllocator, int arg_4, size_t objectSize)
	: mpAllocator(pAllocator)
	, field_18(arg_4)
	, mnObjectSize(objectSize)
	, field_8(0)
	, field_C(0)
	, field_10(0)
	, field_1C(0)
{}

FixedPoolAllocator::~FixedPoolAllocator()
{
	VOID_THISCALL(GetAddress(FixedPoolAllocator, dtor), this);
}

auto_METHOD(FixedPoolAllocator, void*, Alloc,
	Args(size_t size, const char *name, unsigned int flags, unsigned int align, unsigned int alignOffset), 
	Args(size, name, flags, align, alignOffset));

METHOD(GetAddress(FixedPoolAllocator, Alloc_), FixedPoolAllocator, void*, FixedPoolAllocator::Alloc, 
	Args(size_t size, const char *name, unsigned int flags), Args(size, name, flags));

auto_METHOD_VOID(FixedPoolAllocator, Free, Args(void *block, size_t size), Args(block, size));
#endif
