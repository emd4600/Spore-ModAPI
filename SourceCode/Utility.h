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

#pragma once

#include <EASTL\internal\thread_support.h>

#define DEFAULT_REFCOUNT(className) int className::AddRef() \
{ \
	return eastl::Internal::atomic_increment(&mnRefCount); \
} \
int className::Release() \
{ \
	if (eastl::Internal::atomic_decrement(&mnRefCount) == 0) \
	{ \
		delete this; \
	} \
	return mnRefCount; \
}