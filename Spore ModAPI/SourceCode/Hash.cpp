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

#include <Spore\Internal.h>
#include <Spore\Hash.h>
#include <iostream>
#include <sstream>
#include <string>

namespace Hash
{
	unsigned long fnvInternal(const char* str)
	{
		int rez = 0x811C9DC5;
		int i = 0;
		while (true)
		{
			if (str[i] == 0) break;
			rez *= 0x1000193;
			rez ^= tolower(str[i]);
			i++;
		}
		return rez;
	}

	unsigned long fnvInternal(const char16_t* str)
	{
		int rez = 0x811C9DC5;
		int i = 0;
		while (true)
		{
			if (str[i] == 0) break;
			rez *= 0x1000193;
			rez ^= tolower(str[i]);
			i++;
		}
		return rez;
	}

	uint32_t FNV(const char* str)
	{
		return fnvInternal(str);
	}

	uint32_t FNV(const char16_t* str)
	{
		return fnvInternal(str);
	}
}
#endif
