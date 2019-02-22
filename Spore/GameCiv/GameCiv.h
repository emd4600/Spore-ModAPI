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

#include <Spore\UTFWin\IWinProc.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\IGameMode.h>
#include <Spore\Clock.h>

namespace GameCiv
{
	class GameCiv
		: public App::IGameModeObject
		, public UTFWin::IWinProc
		, public App::IMessageListener
	{
	public:
		//TODO Apart from the IGameModeObject methods, it also has another virtual method

	protected:
		/* 28h */	bool field_28;
		/* 29h */	bool field_29;
		/* 2Ah */	bool field_2A;
		/* 2Bh */	bool field_2B;
		/* 2Ch */	vector<int> field_2C;
		/* 40h */	vector<int> field_40;
		/* 54h */	vector<int> field_58;
		/* 68h */	char field_68[0x48];
		/* B0h */	bool field_B0;
		/* B4h */	int field_B4;
		/* B8h */	int field_B8;
		/* BCh */	int field_BC;
		/* C0h */	int field_C0;
		/* C4h */	int field_C4;  // not initialized
	};
}