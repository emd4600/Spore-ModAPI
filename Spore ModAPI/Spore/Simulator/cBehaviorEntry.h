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

namespace Simulator
{
	class cBehaviorEntry
	{
	public:
		struct BehaviorTarget
		{
			int type;
			int value;
		};

	public:
		/* 00h */	int mConditionType;
		/* 04h */	BehaviorTarget mConditionTarget;
		/* 0Ch */	int mActionType;
		/* 10h */	BehaviorTarget mActionTarget;
		/* 18h */	BehaviorTarget mActionSecondaryTarget;
	};
	ASSERT_SIZE(cBehaviorEntry, 0x20);
}