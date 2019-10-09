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

#include <Spore\Mutex.h>


Mutex::Mutex(MutexInfo* pInfo, bool bUseCriticalSection)
	: mhMutex(NULL)
	, field_04(NULL)
	, field_08(NULL)
	, field_0C(NULL)
	, field_10(NULL)
	, field_14(NULL)
	, field_18(NULL)
	, field_1C(NULL)
	, mnRecursionCount(NULL)
	, mbUseCriticalSection(true)
	, field_28(NULL)
	// field_2C is not initialized
{
	if (pInfo == nullptr || !bUseCriticalSection)
	{
		Initialize(pInfo);
	}
	else
	{
		MutexInfo info;
		info.bUseCriticalSection = true;
		Initialize(&info);
	}
}

Mutex::~Mutex()
{
	if (mbUseCriticalSection)
	{
		DeleteCriticalSection((LPCRITICAL_SECTION) this);
	}
	else
	{
		CloseHandle(mhMutex);
	}
}


bool Mutex::Initialize(MutexInfo* pInfo)
{
	if (pInfo == nullptr)
	{
		return false;
	}
	mnRecursionCount = 0;
	mbUseCriticalSection = pInfo->bUseCriticalSection;

	if (mbUseCriticalSection)
	{
		InitializeCriticalSection((LPCRITICAL_SECTION) this);
		return true;
	}
	else
	{
		mhMutex = CreateMutexA(NULL, false, pInfo->mutexName);
		return mhMutex != nullptr;
	}
}


int Mutex::Lock(const DWORD& millisecondsTime)
{
	if (mbUseCriticalSection)
	{
		if (millisecondsTime == INFINITE)
		{
			EnterCriticalSection((LPCRITICAL_SECTION) this);
		}
		else
		{
			while (!TryEnterCriticalSection((LPCRITICAL_SECTION) this))
			{
				if (GetTickCount() >= millisecondsTime)
				{
					return -2;
				}
				SleepEx(1, true);
			}
		}
	}
	else
	{
		DWORD dwMilliseconds = millisecondsTime;
		if (dwMilliseconds != INFINITE && dwMilliseconds != 0)
		{
			DWORD tickCount = GetTickCount();
			if (dwMilliseconds > tickCount)
			{
				dwMilliseconds -= tickCount;
			}
			else
			{
				dwMilliseconds = 0;
			}
		}

		DWORD result = WaitForSingleObject(mhMutex, dwMilliseconds);
		if (result == WAIT_TIMEOUT)
		{
			return -2;
		}
		else if (result != WAIT_OBJECT_0)
		{
			return -1;
		}
	}

	mnRecursionCount++;
	return mnRecursionCount;
}

int Mutex::Unlock()
{
	mnRecursionCount--;

	if (mbUseCriticalSection)
	{
		LeaveCriticalSection((LPCRITICAL_SECTION) this);
	}
	else
	{
		ReleaseMutex(mhMutex);
	}

	return mnRecursionCount;
}