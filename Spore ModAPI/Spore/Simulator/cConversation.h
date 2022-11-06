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

#include <Spore\Resource\ResourceObject.h>
#include <EASTL\map.h>
#include <EASTL\vector.h>

#define cConversationPtr eastl::intrusive_ptr<Simulator::cConversation>

namespace Simulator
{
	using namespace eastl;

	// Maybe SpecialReosurceObject?
	class cConversation : public Resource::ResourceObject
	{
	public:
		/* 14h */	int field_14;
		/* 18h */	map<int, int> field_18;
		/* 34h */	map<int, int> field_34;
		/* 50h */	map<int, int> field_50;
		/* 6Ch */	vector<int> field_6C;
	};

	static_assert(sizeof(cConversation) == 0x80, "sizeof(cConversation) != 80h");
}
