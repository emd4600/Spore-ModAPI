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

#include <Spore\App\IMessageListener.h>
#include <Spore\App\ITokenTranslator.h>
#include <Spore\UTFWin\UILayout.h>

namespace UI
{
	class GlobalUIUnkBase1
		: public App::IMessageListener	
	{
	public:
		/* 04h */	ObjectPtr field_4;
		/* 08h */	UILayoutPtr mpLayout;
	};

	class GlobalUIUnkBase2
	{
	public:
		virtual void func00h(int);
		virtual void func04h(int, int);
		virtual ~GlobalUIUnkBase2();
	};

	class GlobalUI
		/* 00h */	: public GlobalUIUnkBase1
		/* 0Ch */	, public GlobalUIUnkBase2
		/* 10h */	, public App::ITokenTranslator
	{
		// vftable 08h sets the main stage layout, for example 0x1E453B88 for space stage

	public:
		/* 14h */	bool field_14;
	};
	//ASSERT_SIZE(GlobalUI, 0x68);
}