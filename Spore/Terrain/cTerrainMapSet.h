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

#include <Spore\Terrain\TerrainMaps.h>

namespace Terrain
{
	enum class TerrainMapIndices : int
	{
		HeightMap = 0,
		NormalMap = 1,
		ControlMap = 2,
		ColorMap = 3,
		JetStreamMap = 4,
		PressureMap = 5,
		CloudEmitMap = 6,
		HeightAboveMap = 7,
		WindTempMap = 8,
		FloatTempMap = 9,
		FilteredMap = 10,
	};

	class cTerrainMapSet
	{
	public:

		virtual ~cTerrainMapSet();

		// PLACEHOLDER sub_F93070 SetMap

	private:
		/* 04h */	int mnRefCount;
	protected:
		/* 08h */	cTerrainMap mMaps[11];
		/* 34h */	float field_34;  // 500.0
		/* 38h */	float field_38;  // 100.0
		/* 3Ch */	float field_3C;
		/* 40h */	float field_40;
		/* 44h */	float field_44;  // 0.025
		/* 48h */	float field_48;
		/* 4Ch */	float field_4C;
		/* 50h */	float field_50;  // -1.0
		/* 54h */	float field_54;  // -1.0
		/* 58h */	int field_58;  // cHeightRanges PLACEHOLDER
	};

	static_assert(sizeof(cTerrainMapSet) == 0x5C, "sizeof(cTerrainMapSet) != 5Ch");
}