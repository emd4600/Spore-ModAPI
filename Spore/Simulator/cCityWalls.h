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
#include <Spore\Simulator\cOrnament.h>

namespace Simulator
{
	class cCity;

	class cCityWalls
		: public cGameData
		, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0xED7FC07;
		static const uint32_t NOUN_ID = 0x18C7C97;

	public:
		/* 108h */	bool field_108;
		/* 10Ch */	intrusive_ptr<cOrnament> mpDock;
		/* 110h */	vector<int> field_110;
		/* 124h */	vector<int> field_124;
		/* 138h */	int field_138;
		/* 13Ch */	int field_13C;
		/* 140h */	int field_140;
		/* 144h */	int field_144;
		/* 148h */	int field_148;
		/* 14Ch */	int field_14C;
		/* 150h */	int field_150;
		/* 154h */	int field_154;
		/* 158h */	int field_158;
		/* 15Ch */	vector<int> field_15C;
		/* 170h */	vector<int> field_170;
		/* 184h */	vector<int> field_184;
		/* 198h */	vector<int> field_198;
		/* 1ACh */	vector<int> field_1AC;
		/* 1C0h */	vector<int> field_1C0;
		/* 1D4h */	vector<int> field_1D4;
		/* 1E8h */	vector<int> field_1E8;
		/* 1FCh */	vector<int> field_1FC;
		/* 210h */	vector<int> field_210;
		/* 224h */	Vector3 field_224[4];
		/* 254h */	int mWallSize;
		/* 258h */	float field_258;  // 29
		/* 25Ch */	float field_25C;  // 37  sphere radius?
		/* 260h */	float field_260;
		/* 264h */	intrusive_ptr<cCity> mpCity;
		/* 268h */	Vector3 field_268;  // 1, 1, 1
		/* 274h */	char field_274[0xC4];  // 14 booleans
		/* 338h */	Vector3 mCenterAxis;  // not initialized
		/* 344h */	uint32_t mStyle;  // 0x9181A19
		/* 348h */	int mLevel;
		/* 34Ch */	int mWallOffset;
		/* 350h */	bool mbAppliedStamp;
		/* 354h */	int field_354;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cCityWalls) == 0x358, "sizeof(cCityWalls) != 358h");
}