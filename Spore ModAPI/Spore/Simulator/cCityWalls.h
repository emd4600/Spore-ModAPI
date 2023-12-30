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

#define cCityWallsPtr eastl::intrusive_ptr<Simulator::cCityWalls>

namespace Simulator
{
	class cCity;

	constexpr int MAX_LAYOUT_SLOTS = 14;

	class cCityWalls
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
	{
	public:
		static const uint32_t TYPE = 0xED7FC07;
		static const uint32_t NOUN_ID = 0x18C7C97;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		// 70h GetDirection ?

	public:
		/* 108h */	bool field_108;
		/* 10Ch */	cOrnamentPtr mpDock;
		/* 110h */	eastl::vector<int> field_110;
		/* 124h */	eastl::vector<int> field_124;
		/* 138h */	int field_138;
		/* 13Ch */	int field_13C;
		/* 140h */	int field_140;
		/* 144h */	int field_144;
		/* 148h */	int field_148;
		/* 14Ch */	int field_14C;
		/* 150h */	int field_150;
		/* 154h */	int field_154;
		/* 158h */	int field_158;
		/// From property `Turrets` 
		/* 15Ch */	eastl::vector<Math::Vector3> mTurrets;
		/// Positions from mTurrets transformed with the city position/rotation
		/* 170h */	eastl::vector<Math::Vector3> mTurretsTransformed;
		/// First is property `Main_Gate`, index 1 and 2 are property `Side_Gates`, index 3 is property `Sea_Gate`,
		// index 4 is property `Harvest_Gate`, index 5 is `Freight_Gate`
		/* 184h */	eastl::vector<Math::Vector3> mGates;
		/// Positions from mGates transformed with the city position/rotation
		/* 198h */	eastl::vector<Math::Vector3> mGatesTransformed;
		/// First slot is `City_Hall`, the rest is `Buildings`
		/* 1ACh */	eastl::vector<Math::Vector3> mBuildings;
		/// Positions from mBuildings transformed with the city position/rotation
		/* 1C0h */	eastl::vector<Math::Vector3> mBuildingsTransformed;
		/// From property `Decorations`
		/* 1D4h */	eastl::vector<Math::Vector3> mDecorations;
		/// Positions from mDecorations transformed with the city position/rotation
		/* 1E8h */	eastl::vector<Math::Vector3> mDecorationsTransformed;
		/// From property `Plazas`
		/* 1FCh */	eastl::vector<Math::Vector3> mPlazas;
		/// Positions from mPlazas transformed with the city position/rotation
		/* 210h */	eastl::vector<Math::Vector3> mPlazasTransformed;
		/* 224h */	Vector3 mFirstBoatPos;
		/* 230h */	Vector3 mFirstBoatPosTransformed;
		/* 23Ch */	Vector3 mModelDocksOffset;
		/* 248h */	Vector3 mModelDocksOffsetTransformed;
		/* 254h */	int mWallSize;
		/* 258h */	float mInnerRadius;  // 29
		/* 25Ch */	float mOuterRadius;  // 37  sphere radius?
		/* 260h */	float mCityHallDiasHeight;
		/* 264h */	eastl::intrusive_ptr<cCity> mpCity;
		/* 268h */	Vector3 field_268;  // 1, 1, 1
		/// A matrix teling which building slots are connected to which slots
		/* 274h */	bool mBuildingLinks[MAX_LAYOUT_SLOTS][MAX_LAYOUT_SLOTS];
		/* 338h */	Vector3 mCenterAxis;  // not initialized
		/* 344h */	uint32_t mStyle;  // 0x9181A19
		/* 348h */	int mLevel;
		/* 34Ch */	int mWallOffset;
		/* 350h */	bool mbAppliedStamp;
		/* 354h */	int field_354;
	};
	ASSERT_SIZE(cCityWalls, 0x358);
}