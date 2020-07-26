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

#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Object.h>
#include <EASTL\string.h>
#include <EASTL\deque.h>

#define cBehaviorAgentPtr eastl::intrusive_ptr<Simulator::cBehaviorAgent>

namespace Simulator
{
	// used by the cGameBehaviorManager
	class cBehaviorAgent
	{
	public:
		static const uint32_t TYPE = 0x11C0BA3;

		//TODO more
		virtual ~cBehaviorAgent();

		/* 04h */	virtual void func04h();
		/* 08h */	virtual bool func08h(uint32_t);
		/// For example, abducting calls this on the creature passing pSpaceGameBehaviorAbducted and the space projectile
		/* 0Ch */	virtual int func0Ch(cBehaviorBase* pBehavior, cBehaviorList* pOwner, int);
		/* 10h */	virtual int func10h(int, int, int);
		/* 14h */	virtual void func14h(bool);
		/* 18h */	virtual bool func18h();
		/* 1Ch */	virtual bool HasInteractions();
		/* 20h */	virtual cBehaviorBase* GetLastInteraction();
		/* 24h */	virtual int func24h();
		/* 28h */	virtual int func28h();
		/* 2Ch */	virtual int func2Ch();
		/* 30h */	virtual void func30h();
		/* 34h */	virtual void func34h();
		/* 38h */	virtual int GetInteractionStackSize() const;
		/* 3Ch */	virtual bool func3Ch(int);
		/* 40h */	virtual bool func40h(int, int);
		/* 44h */	virtual int func44h(int);  // ?
		/* 48h */	virtual void func48h();
		/* 4Ch */	virtual void func4Ch(bool);
		/* 50h */	virtual bool func50h();
		/* 54h */	virtual void func54h(string& dst);
		/* 58h */	virtual void func58h(string& dst);
		/* 5Ch */	virtual int Release();
		/* 60h */	virtual int AddRef();
		/* 64h */	virtual int func64h();

	public:
		/* 04h */	bool field_4;
		/* 08h */	deque<int> mInteractionHistory;
		/* 34h */	deque<cBehaviorBasePtr> mInteractionStack;
		/* 60h */	int field_60;  // not initialized
		/* 64h */	bool field_64;
		/* 65h */	bool field_65;  // true
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cBehaviorAgent) == 0x68, "sizeof(cBehaviorAgent) != 68h");
}