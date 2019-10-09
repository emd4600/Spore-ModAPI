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

#include <Spore\MathUtils.h>

namespace Swarm
{
	class SwarmManagerStruct
	{
	protected:
		/* 00h */	float field_0;  // 1.0f
		/* 04h */	float field_04;  // 1.0f
		/* 08h */	int field_08;  // 20
		/* 0Ch */	float field_0C;  // 1000.0f
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	Math::Matrix4 field_1C;
		/* 5Ch */	Math::Matrix3 field_5C;
		/* 80h */	float field_80;
		/* 84h */	float field_84;
		/* 88h */	float field_88;
		/* 8Ch */	float field_8C;
		/* 90h */	float field_90;
		/* 94h */	float field_94;
		/* 98h */	float field_98;
		/* 9Ch */	float field_9C;
		/* A0h */	float field_A0;
		/* A4h */	float field_A4;
		/* A8h */	float field_A8;
		/* ACh */	float field_AC;  // 1.0f
		/* B0h */	bool field_B0;
		/* B4h */	int field_B4;
		/* B8h */	int field_B8;
		/* BCh */	Math::Vector3 field_BC;
		/* C8h */	float field_C8;
		/* CCh */	Math::Vector3 field_CC;
		/* D8h */	float field_D8;
		/* DCh */	float field_DC;
		/* E0h */	float field_E0;  // -1.0f
		/* E4h */	float field_E4;
		/* E8h */	Math::Vector3 field_E8;
		/* F4h */	Math::Vector3 field_F4;  // 0, 0, 1
		/* 100h */	float field_100;
		/* 104h */	Math::Vector3 field_104;  // 0, 0, 1
		/* 110h */	bool field_110;
		/* 111h */	bool field_111;
		/* 112h */	bool field_112;
		/* 114h */	float field_114;  // 0.1f
		/* 118h */	bool field_118;
		/* 119h */	bool field_119;  // true
		/* 11Ah */	bool field_11A;  // true
		/* 11Bh */	bool field_11B;  // true
		/* 11Ch */	bool field_11C;  // true
	};

	static_assert(sizeof(SwarmManagerStruct) == 0x120, "sizeof(SwarmManagerStruct) != 120h");
}