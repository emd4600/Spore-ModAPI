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
	// Maybe SpecialReosurceObject?
	class cConversation 
		: public Resource::ResourceObject
	{
	public:
		/* 14h */	int field_14;
		/* 18h */	eastl::map<int, int> field_18;
		/* 34h */	eastl::map<int, int> field_34;
		/* 50h */	eastl::map<int, int> field_50;
		/* 6Ch */	eastl::vector<int> field_6C;
	};
	ASSERT_SIZE(cConversation, 0x80);
}
