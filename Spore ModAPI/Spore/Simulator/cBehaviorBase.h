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
#include <EASTL\vector.h>
#include <EASTL\map.h>

#define cBehaviorBasePtr eastl::intrusive_ptr<Simulator::cBehaviorBase>

namespace Simulator
{
	class cBehaviorBase
		: public Object
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x1141F86;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		// function 14h returns description eastl::string?
		// 34h bool IsSupported(cBehaviorAgent*);

	public:
		/* 08h */	int mnRefCount;
		/* 0Ch */	eastl::vector<int> field_C;
		/* 20h */	int field_20;  // 0x7F
		/* 24h */	int field_24;  // 0x3FFFFFFF
		/* 28h */	int field_28;  // 0x3FFFFFFF
		/* 2Ch */	eastl::vector<int> field_2C;
		/* 40h */	int field_40;  // 0x7F
		/* 44h */	int field_44;  // 0x3FFFFFFF
		/* 48h */	int field_48;  // 0x3FFFFFFF
		/* 4Ch */	eastl::map<int, int> field_4C;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;
	};
	ASSERT_SIZE(cBehaviorBase, 0x74);
}