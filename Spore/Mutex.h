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

#include <Windows.h>

class Mutex
{
public:
	static const DWORD kDefaultWait = -1;

	struct MutexInfo
	{
		bool bUseCriticalSection;
		char mutexName[15];
	};

	Mutex(MutexInfo* pInfo, bool bUseCriticalSection);
	~Mutex();

	int Lock(const DWORD& dwMilliseconds);
	int Unlock();

protected:
	bool Initialize(MutexInfo* pInfo);

protected:
	/* 00h */	HANDLE mhMutex;
	/* 04h */	int field_04;
	/* 08h */	int field_08;
	/* 0Ch */	int field_0C;
	/* 10h */	int field_10;
	/* 14h */	int field_14;
	/* 18h */	int field_18;
	/* 1Ch */	int field_1C;
	/* 20h */	int mnRecursionCount;
	/* 24h */	bool mbUseCriticalSection;
	/* 28h */	int field_28;
	/* 2Ch */	int field_2C;
};

///////////////////////////////////
//// INTERNAL IMPLEMENENTATION ////
///////////////////////////////////

static_assert(sizeof(Mutex) == 0x30, "sizeof(Mutex) != 30h");
static_assert(sizeof(Mutex::MutexInfo) == 0x10, "sizeof(Mutex::MutexInfo) != 10h");
