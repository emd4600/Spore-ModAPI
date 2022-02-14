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
#include <Spore\Simulator\cLocomotiveObject.h>

namespace Simulator
{
	// also used by vehicles
	class UnknownCreatureClass
	{
	public:
		static const uint32_t TYPE = 0x7B3A16F;

		virtual ~UnknownCreatureClass();
		virtual void* Cast(uint32_t type);
		virtual int AddRef();
		virtual int Release();
		virtual cGameData* ToGameData();
		virtual cLocomotiveObject* ToLocomotiveObject();

	public:
		/* 04h */	vector<int> field_4;
		/* 18h */	int field_18;
		/* 1Ch */	char padding_1C[0x1C];
		/* 38h */	vector<int> field_38;
		/* 4Ch */	int field_4C;
		/* 50h */	vector<int> field_50;
		/* 64h */	int field_64;
		/* 68h */	fixed_vector<intrusive_ptr<cSpatialObject>, 128> field_68;
		/* 280h */	fixed_vector<intrusive_ptr<cSpatialObject>, 128> field_280;
		/* 498h */	float field_498;
		/* 49Ch */	int field_49C;
	};
	ASSERT_SIZE(UnknownCreatureClass, 0x4A0);
}