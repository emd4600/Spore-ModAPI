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

namespace Simulator
{
	class IGameData;
	
	class cOrnamentBase
	{
	public:
		static const uint32_t TYPE = 0x8367427;
		
		virtual ~cOrnamentBase();
		virtual IGameData* ToGameData() = 0;
		virtual void* func08h() = 0;
		
	public:
		/* 04h */	int field_4;
		/* 08h */	int field_8;
		/* 0Ch */	int field_C;
		/* 10h */	int field_10;
		/* 14h */	bool field_14;
		/* 18h */	intrusive_ptr<Object> field_18;
		/* 1Ch */	intrusive_ptr<Object> field_1C;
		/* 20h */	intrusive_ptr<Object> field_20;
		/* 24h */	int field_24;  // not initialized
		/* 28h */	int field_28;  // not initialized
		/* 2Ch */	int field_2C;  // not initialized
		/* 30h */	bool field_30;
		/* 34h */	float field_34;
		/* 38h */	intrusive_ptr<Object> field_38;
		/* 3Ch */	int field_3C;  // not initialized
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cOrnamentBase) == 0x40, "sizeof(cOrnamentBase) != 40h");
}