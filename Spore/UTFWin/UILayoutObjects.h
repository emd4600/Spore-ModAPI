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

#include "..\Object.h"
#include "IWindow.h"
#include <EASTL\vector.h>

namespace UTFWin
{
	class LayoutObjectsContainer
	{

		// /* 5Ch */	eastl::vector<>
	};

	class UILayoutObjects : public DefaultRefCounted, LayoutObjectsContainer
	{
	public:

		/* 64h */	vector<intrusive_ptr<UTFWin::IWindow>> rootComponents;

		/* 88h */	intrusive_ptr<UTFWin::IWindow> containerWindow;  // container window?
		/* 8Ch */	bool isVisible;
		/* 8Dh */	bool field_8D;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
		/* 98h */	int field_98;

		//TODO
	};

}
