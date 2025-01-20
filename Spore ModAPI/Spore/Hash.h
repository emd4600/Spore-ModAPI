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

#include <cstdint>

constexpr int const_tolower(int c) {
	return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

constexpr uint32_t id(const char* pStr, uint32_t starter)
{
	int i = 0;
	while (pStr[i])
	{
		char c = pStr[i];
		// To avoid compiler warnings
		starter = static_cast<uint32_t>(starter * static_cast<unsigned long long>(0x1000193));
		starter ^= static_cast<uint32_t>(const_tolower(c));
		++i;
	}
	return starter;
}

constexpr uint32_t id(const char* pStr)
{
	return id(pStr, 0x811C9DC5u);
}

constexpr uint32_t id(const char16_t* pStr)
{
	uint32_t rez = 0x811C9DC5u;
	int i = 0;
	while (pStr[i])
	{
		char16_t c = pStr[i];
		// To avoid compiler warnings
		rez = static_cast<uint32_t>(rez * static_cast<unsigned long long>(0x1000193));
		rez ^= static_cast<uint32_t>(const_tolower(c));
		i++;
	}
	return rez;
}

