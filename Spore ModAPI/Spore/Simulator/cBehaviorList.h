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

#include <Spore\Simulator\cBehaviorBase.h>

#define cBehaviorListPtr intrusive_ptr<Simulator::cBehaviorList>

namespace Simulator
{
	class cBehaviorList
	{
	public:
		static const uint32_t TYPE = 0x102A041A;

		virtual ~cBehaviorList();

		/* 04h */	virtual void* Cast(uint32_t typeID);
		/* 08h */	virtual void Remove(cBehaviorBase* pBehaviour);
		/* 0Ch */	virtual void Add(cBehaviorBase* pBehaviour);
		/* 10h */	virtual void func10h();
		/* 14h */	virtual int Release() = 0;
		/* 18h */	virtual int AddRef() = 0;

	public:
		/* 04h */	vector<intrusive_ptr<cBehaviorBase>> mData;
	};
	ASSERT_SIZE(cBehaviorList, 0x18);
}