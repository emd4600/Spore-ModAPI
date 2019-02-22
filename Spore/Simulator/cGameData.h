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
#include <Spore\Simulator\ISimulatorSerializable.h>
#include <EASTL\intrusive_list.h>

namespace Simulator
{

	class cGameData 
		: public ISimulatorSerializable
		, public DefaultRefCounted
		, public intrusive_list_node
	{
	public:
		static const uint32_t TYPE = 0x17F243B;

		using DefaultRefCounted::AddRef;
		using DefaultRefCounted::Release;

		cGameData();
		virtual ~cGameData();

		/* 24h */	virtual bool SetDefinitionID(int);  // 3 arguments, parses prop?? // the parameter is not a uint32_t
		/* 28h */	virtual void SetGameDataOwner(cGameData* pOwner);  // also sets politicalID
		/* 2Ch */	virtual bool IsDestroyed();
		/* 30h */	virtual cGameData* GetGameDataOwner();
		/* 34h */	virtual void SetGameDataOwner2(cGameData* pOwner);  // also sets politicalID
		/* 38h */	virtual int func38h() = 0;  //TODO
		/* 3Ch */	virtual bool func3Ch(int);  // just calls 40h
		/* 40h */	virtual bool func40h();
		/* 44h */	virtual void RemoveOwner();
		/* 48h */	virtual void SetPoliticalID(uint32_t id);
		/* 4Ch */	virtual uint32_t GetPoliticalID();
		/* 50h */	virtual void func50h(int);  // related with attributes

	protected:
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;  // -1
		/* 20h */	bool field_20;
		/* 21h */	bool mbIsDestroyed;
		/* 24h */	uint32_t mID;  // -1
		/* 28h */	uint32_t mDefinitionID;
		/* 2Ch */	intrusive_ptr<cGameData> mpGameDataOwner;
		/* 30h */	uint32_t mPoliticalID;  // -1
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cGameData) == 0x34, "sizeof(cGameData) != 34h");
}
