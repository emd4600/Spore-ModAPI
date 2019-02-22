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
#include <Spore\ResourceKey.h>

#include <EASTL\vector.h>

namespace UI
{
	class TiledScrollPanel
	{
	public:
		virtual ~TiledScrollPanel();
		virtual bool func04h(int, int);  // handle message maybe?

	protected:
		/* 04h */	intrusive_ptr<Object> field_4;
		/* 08h */	intrusive_ptr<Object> field_8;
		/* 0Ch */	ResourceKey mLayoutName;
		/* 18h */	vector<intrusive_ptr<DefaultRefCounted>> field_18;
		/* 2Ch */	int field_2C;  // 1
		/* 30h */	vector<int> field_30;
		/* 44h */	float field_44;
		/* 48h */	float field_48;
		/* 4Ch */	float field_4C;
		/* 50h */	float field_50;
		/* 54h */	float field_54;  // 1.0
		/* 58h */	float field_58;  // 1.0
		/* 5Ch */	int field_5C;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(TiledScrollPanel) == 0x70, "sizeof(SpaceGameUI) != 70h");
}