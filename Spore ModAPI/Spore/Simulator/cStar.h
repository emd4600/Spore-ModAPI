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
#include <Spore\Simulator\cStarRecord.h>
#include <Spore\Simulator\cSolarSystem.h>

#define cStarPtr eastl::intrusive_ptr<Simulator::cStar>

namespace Simulator
{
	class cStar 
		: public cGameData
	{
	public:
		static const uint32_t TYPE = 0x355C8DF;
		static const uint32_t NOUN_ID = 0x355C93A;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/// Gets the solar system of this star, creating it if necessary.
		/// @returns
		cSolarSystem* GetSolarSystem();

		StarType GetStarType();
		bool IsBinaryStar();
		bool IsStarOrBinaryStar();

		eastl::string16& GetName();

	public:
		/// For binary systems, type of the first star.
		/* 34h */	StarType mPrimaryType;
		/// For binary systems, type of the second star.
		/* 38h */	StarType mSecondaryType;
		/* 3Ch */	bool mActivatedPlanets;
		/* 40h */	cSolarSystemPtr mpSolarSystem;
		/* 44h */	bool mPlayerCanCapture;  // true
		/* 48h */	cStarRecordPtr mpStarRecord;
		/* 4Ch */	uint32_t mKey;  // -1
	};
	ASSERT_SIZE(cStar, 0x50);

	namespace Addresses(cStar)
	{
		DeclareAddress(GetSolarSystem);  // 0xC8AA90  0xC8B900
		DeclareAddress(IsBinaryStar);  // 0xC8AB00 0xC8B970
		DeclareAddress(IsStarOrBinaryStar);  // 0xC8AB20 0xC8B990
	}

	inline StarType cStar::GetStarType() {
		return mpStarRecord->mType;
	}

	inline eastl::string16& cStar::GetName() {
		return mpStarRecord->mName;
	}
}