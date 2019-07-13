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
#include <memory>

#define SPORE_ALLOCATOR_ADDRESS Address(SelectAddress(0x16CCDC4, 0x16C9B24, 0x16C8B44))
#define ADDRESS_SPORE_NEW Address(SelectAddress(0xF47650, 0xF47240, 0xF47240))
#define ADDRESS_SPORE_DELETE Address(SelectAddress(0xF47630, 0xF47220, 0xF47220))

// EASTL expects us to define these, see allocator.h line 194
void* operator new[](size_t size, const char* pName,
	int flags, unsigned debugFlags,
	const char* file, int line) {

	if (*(uint32_t*)SPORE_ALLOCATOR_ADDRESS == NULL)
	{
		return malloc(size);
	}
	else
	{
		return ((void*(*)(size_t, const char*, int, unsigned, const char*, int)) ADDRESS_SPORE_NEW)(size, pName, flags, debugFlags, file, line);
	}
}
void* operator new[](size_t size, size_t alignment,
	size_t alignmentOffset, const char* pName,
	int flags, unsigned debugFlags,
	const char* file, int line) {

	if (*(uint32_t*)SPORE_ALLOCATOR_ADDRESS == NULL)
	{
		return malloc(size);
	}
	else
	{
		return ((void*(*)(size_t, const char*, int, unsigned, const char*, int)) ADDRESS_SPORE_NEW)(size, pName, flags, debugFlags, file, line);
	}
}

void operator delete[](void* p) {

	if (*(uint32_t*)SPORE_ALLOCATOR_ADDRESS == NULL)
	{
		free(p);
	}
	else
	{
		((void(*)(void*)) ADDRESS_SPORE_DELETE)(p);
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
