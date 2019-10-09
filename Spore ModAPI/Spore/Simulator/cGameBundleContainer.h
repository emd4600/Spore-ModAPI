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

#include <Spore\Simulator\cGameData.h>
#include <EASTL\vector.h>

namespace Simulator
{
	//PLACEHOLDER
	class cGameBundle;

	class cGameBundleContainer
	{
	public:
		//PLACEHOLDER
		virtual ~cGameBundleContainer();

	public:
		/* 04h */	vector<cGameBundle> mBundleList;
		/* 18h */	intrusive_ptr<cGameData> mpOwner;
		/* 1Ch */	int mContainerCapacity;
		/* 20h */	int mBundleCapacity;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cGameBundleContainer) == 0x24, "sizeof(cGameBundleContainer) != 24h");
}