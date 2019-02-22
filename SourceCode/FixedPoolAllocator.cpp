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
	VOID_THISCALL(GetAddress(0x926360, 0x9260F0, 0x9260F0), this);
}

METHOD(GetAddress(0x926370, 0x926100, 0x926100), FixedPoolAllocator, void*, FixedPoolAllocator::Alloc,
	PARAMS(size_t size, const char *name, unsigned int flags, unsigned int align, unsigned int alignOffset), PARAMS(size, name, flags, align, alignOffset));

METHOD(GetAddress(0x926490, 0x926220, 0x926220), FixedPoolAllocator, void*, FixedPoolAllocator::Alloc, PARAMS(size_t size, const char *name, unsigned int flags), PARAMS(size, name, flags));

METHOD_VOID(GetAddress(0x9263B0, 0x926140, 0x926140), FixedPoolAllocator, FixedPoolAllocator::Free, PARAMS(void *block, size_t size), PARAMS(block, size));