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
#include <Spore\Simulator\cSpatialObject.h>

#define cCityTerritoryPtr eastl::intrusive_ptr<Simulator::cCityTerritory>

namespace Simulator
{
	class cCityTerritory
		: public cGameData
		, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0x2450023;
		static const uint32_t NOUN_ID = 0x244FB08;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 108h */	bool field_108;  // true
		/* 10Ch */	float field_10C;  // 100.0
		/* 110h */	bool field_110;
		/* 111h */	bool field_111;
	};
	ASSERT_SIZE(cCityTerritory, 0x114);
}