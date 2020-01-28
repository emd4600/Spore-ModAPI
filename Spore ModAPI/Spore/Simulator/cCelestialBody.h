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
#include <Spore\MathUtils.h>
#include <EASTL\string.h>

#define cCelestialBodyPtr intrusive_ptr<Simulator::cCelestialBody>

namespace Simulator
{
	class cCelestialBody
		: public cGameData
	{
	public:
		static const uint32_t TYPE = 0x38CFB68;
		static const uint32_t NOUN_ID = 0x38CFB6B;

	public:
		/* 34h */	int mType;
		/* 38h */	bool mbOrbit;  // true
		/* 3Ch */	char _padding_3C[0x64];
		/* A0h */	Math::Vector3 mPosition;
		/* ACh */	float mfRotationRate;
		/* B0h */	string16 mName;
		/* C0h */	intrusive_ptr<Object> field_C0;
		/* C4h */	intrusive_ptr<Object> field_C4;
		/* C8h */	float mfHitSphereSize;  // 1.0
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cCelestialBody) == 0xCC, "sizeof(cCelestialBody) != CCh");
}