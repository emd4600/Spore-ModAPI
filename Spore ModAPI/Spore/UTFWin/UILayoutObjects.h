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

#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\IWindow.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <EASTL\hash_map.h>

#define UILayoutObjectsPtr eastl::intrusive_ptr<UTFWin::UILayoutObjects>

namespace UTFWin
{
	class LayoutObjectsContainer
	{
	public:
		/* 00h */	int vftable;
		/* 04h */	int field_04;
		/* 08h */	int field_08;
		/* 0Ch */	int field_0C;
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	hash_map<int, int> field_1C;
		/* 3Ch */	hash_map<int, int> field_3C;
		/* 5Ch */	vector<ILayoutElementPtr> mRootComponents;  // root components?
		/* 70h */	string16 field_70;
	};
	ASSERT_SIZE(LayoutObjectsContainer, 0x80);

	class UILayoutObjects 
		: public DefaultRefCounted
		, LayoutObjectsContainer
	{
	public:
		/* 88h */	IWindowPtr containerWindow;  // container window?
		/* 8Ch */	bool isVisible;
		/* 8Dh */	bool field_8D;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
		/* 98h */	int field_98;

		//TODO
	};

}
