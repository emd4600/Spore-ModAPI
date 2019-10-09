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

namespace Simulator
{
	class ISimulatorStrategy
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		/* 08h */	virtual void Initialize() = 0;
		/* 0Ch */	virtual void Dispose() = 0;
		/* 10h */	virtual const char* GetName() = 0;
		/* 14h */	virtual void OnModeExited(uint32_t previousModeID, uint32_t newModeID) = 0;
		/* 18h */	virtual void OnModeEntered(uint32_t previousModeID, uint32_t newModeID) = 0;
		/* 1Ch */	virtual int func1Ch() = 0;
		/* 20h */	virtual int func20h() = 0;
		/* 24h */	virtual bool func24h() = 0;
		/* 28h */	virtual bool Write(void*) = 0;
		/* 2Ch */	virtual bool Read(void*) = 0;
		/* 30h */	virtual void func30h(int) = 0;
		/* 34h */	virtual bool func34h(int) = 0;
		/* 38h */	virtual void Update(int deltaTime, int deltaGameTime) = 0;
		/* 3Ch */	virtual void PostUpdate(int deltaTime, int deltaGameTime) = 0;
		/* 40h */	virtual void func40h(int) = 0;
		/* 44h */	virtual void func44h(int) = 0;
		/* 48h */	virtual void func48h() = 0;
		/* 4Ch */	virtual void func4Ch() = 0;
	};

	class cStrategy
		: public ISimulatorStrategy
		, public IVirtual
	{
	protected:
		/* 08h */	int mnRefCount;
		/* 0Ch */	int field_C;  // -1
		/* 10h */	int field_10;  // -1
		/* 14h */	int field_14;  // -1
		/* 18h */	int field_18;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cStrategy) == 0x1C, "sizeof(cStrategy) != 1Ch");
}

