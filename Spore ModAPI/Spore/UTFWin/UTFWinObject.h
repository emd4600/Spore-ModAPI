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

#include <Spore\Object.h>
#include <Spore\UTFWin\Allocator.h>

namespace UTFWin
{
	class UTFWinObject : public Object
	{
	public:

		static void operator delete(void* p);

		static void* operator new(size_t n, size_t align, const char* pName, ICoreAllocator* pAllocator = UTFWin::GetAllocator());

		static void* operator new(size_t n);
	};

#define UTFWinObject_AMBIGOUS_DECLARATION static void* operator new(size_t n, ICoreAllocator* pAllocator, const char* pName); \
static void* operator new(size_t n); \
static void operator delete(void* p, ICoreAllocator* pAllocator, const char* pName); \
static void operator delete(void* p);

#define UTFWinObject_AMBIGOUS(className) void* className::operator new(size_t n, ICoreAllocator* pAllocator, const char* pName) {return UTFWinObject::operator new(n, pAllocator, pName);} \
void* className::operator new(size_t n) { return UTFWinObject::operator new(n); } \
void className::operator delete(void* p, ICoreAllocator* pAllocator, const char* pName) { return UTFWinObject::operator delete(p, pAllocator, pName); }\
void className::operator delete(void* p) { return UTFWinObject::operator delete(p); }
}