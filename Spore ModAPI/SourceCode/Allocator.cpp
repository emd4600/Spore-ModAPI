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

#include <Spore\Internal.h>
#include <Spore\GeneralAllocator.h>
#include <memory>

GeneralAllocator* GeneralAllocator::Get()
{
	return *(GeneralAllocator**)GetAddress(Internal, Allocator_ptr);
}

// EASTL expects us to define these, see allocator.h line 194
void* operator new[](size_t size, const char* pName,
	int flags, unsigned debugFlags,
	const char* file, int line) {

	if (*(uint32_t*)GetAddress(Internal, Allocator_ptr) == NULL)
	{
		return malloc(size);
	}
	else
	{
		return ((void*(*)(size_t, const char*, int, unsigned, const char*, int)) GetAddress(Internal, new_))(size, pName, flags, debugFlags, file, line);
	}
}
void* operator new[](size_t size, size_t alignment,
	size_t alignmentOffset, const char* pName,
	int flags, unsigned debugFlags,
	const char* file, int line) {

	if (*(uint32_t*)GetAddress(Internal, Allocator_ptr) == NULL)
	{
		return malloc(size);
	}
	else
	{
		return ((void*(*)(size_t, const char*, int, unsigned, const char*, int)) GetAddress(Internal, new_))(size, pName, flags, debugFlags, file, line);
	}
}

void operator delete[](void* p) {

	if (*(uint32_t*)GetAddress(Internal, Allocator_ptr) == NULL)
	{
		free(p);
	}
	else
	{
		((void(*)(void*)) GetAddress(Internal, delete_))(p);
	}
}

void* operator new(size_t n) {
	return operator new[](n, "", 0, 0, __FILE__, __LINE__);
}

void operator delete(void* p) {
	operator delete[](p);
}

void operator delete(void* p, size_t) {
	operator delete[](p);
}

void* operator new[](size_t n) {
	return operator new[](n, "", 0, 0, __FILE__, __LINE__);
}
