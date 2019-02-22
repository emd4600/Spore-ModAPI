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

#include <Spore\UTFWin\Graphics2D.h>

namespace UTFWin
{
	// completely unknown class, but we only need to use one of its methods anyways
	class UIRenderer
	{
	public:

		Graphics2D& GetGraphics2D(int arg_0 = 0);

	private:
		UIRenderer() {}  // private constructor so users don't use it

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace InternalAddressList(UIRenderer)
	{
		DefineAddress(GetGraphics2D, GetAddress(0x95C0C0, 0x95BB70, 0x95BB70));
	}
}