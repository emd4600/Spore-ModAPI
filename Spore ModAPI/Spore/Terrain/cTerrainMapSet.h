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

#include <Spore\Terrain\cTerrainMap.h>
#include <Spore\MathUtils.h>

#define cTerrainMapSetPtr eastl::intrusive_ptr<Terrain::cTerrainMapSet>

namespace Terrain
{
	enum class TerrainMapIndex : int
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
		struct cHeightRanges
		{
			cHeightRanges();

			/* 00h */	int field_0;  // 0x555
			/* 04h */	int field_4;  // 1
			/* 08h */	int field_8;  // 5
			/* 0Ch */	int field_C;  // 0x15
			/* 10h */	int field_10;  // 0x55
			/* 14h */	int field_14;  // 0x155
			/* 18h */	int* mpCell;
		};

		cTerrainMapSet();
		virtual ~cTerrainMapSet();

		int AddRef();
		int Release();

		void SetMap(TerrainMapIndex index, cTerrainMap* pMap);
		cTerrainMap* GetMap(TerrainMapIndex index);

		float GetHeight(const Math::Vector3& position) const;

		float GetWaterHeight() const;

		// PLACEHOLDER sub_F93070 SetMap

	private:
		/* 04h */	int mnRefCount;
	public:
		/* 08h */	cTerrainMapPtr mMaps[11];
		/* 34h */	float mPlanetRadius;  // 500.0
		// (kMaxMaxAlt - kMidMaxAlt) * (radius / 500.0 - 1.0)
		// or if (radius / 500.0 < 1.0)
		// kMinMaxAlt + (kMidMaxAlt - kMinMaxAlt) / 500.0
		/* 38h */	float mAltitudeRange;  // 100.0
		/// Between -1 and 1, gets multiplied by altitude range
		/* 3Ch */	float mWaterLevel;
		/* 40h */	float field_40;
		/* 44h */	float field_44;  // 0.025
		/* 48h */	float field_48;
		/* 4Ch */	float mMaxCliffGradient;
		/* 50h */	float field_50;  // -1.0
		/* 54h */	float field_54;  // -1.0
		/* 58h */	cHeightRanges* mpHeightRanges;
	};

	static_assert(sizeof(cTerrainMapSet) == 0x5C, "sizeof(cTerrainMapSet) != 5Ch");

	namespace Addresses(cTerrainMapSet) {
		DeclareAddress(GetHeight);
	}

	inline float cTerrainMapSet::GetWaterHeight() const
	{
		return mPlanetRadius + mAltitudeRange * mWaterLevel;
	}

	inline int cTerrainMapSet::AddRef() {
		++mnRefCount;
		return mnRefCount;
	}
	inline int cTerrainMapSet::Release() {
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}
}