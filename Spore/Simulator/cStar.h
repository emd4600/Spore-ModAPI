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

namespace Simulator
{
	class cStarRecord;

	class cStar 
		: public cGameData
	{
	public:
		static const uint32_t TYPE = 0x355C8DF;
		static const uint32_t NOUN_ID = 0x355C93A;

	public:
		/* 34h */	int mPrimaryType;
		/* 38h */	int mSecondaryType;
		/* 3Ch */	bool mActivatedPlanets;
		/* 40h */	int field_40;
		/* 44h */	bool mPlayerCanCapture;  // true
		/* 48h */	intrusive_ptr<cStarRecord> mpStarRecord;
		/* 4Ch */	uint32_t mKey;  // -1
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cStar) == 0x50, "sizeof(cStar) != 50h");
}