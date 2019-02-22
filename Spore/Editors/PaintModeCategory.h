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

#include "..\UTFWin\IWinProc.h"
#include "..\Message.h"
#include "..\Object.h"
#include "..\SporeAllocator.h"
#include "ColorChooser.h"
#include <EASTL\vector.h>

namespace Editors
{
	class PaintModeCategory : 
		public MessageListener, 
		public UTFWin::IWinProc, 
		public DefaultRefCounted
	{
	public:
		SPORE_ALLOCATION();

	private:
		char _padding_10[0x20];

		/* 30h */	intrusive_ptr<ColorChooser> primaryChooser;
		/* 34h */	intrusive_ptr<ColorChooser> secondaryChooser;

		char _padding_38[0x90];

		/* C8h */	unsigned long paintID;
		/* CCh */	ColorRGB primaryColor;
		/* D8h */	ColorRGB secondaryColor;

		/* E4h */	bool primaryIsDefault;
		/* E5h */	bool secondaryIsDefault;

		/* E8h */	vector<void*, spore_allocator> field_E8;
	};

	static_assert(sizeof(PaintModeCategory) == 0xFC, "sizeof(PaintModeCategory) != FCh");
}