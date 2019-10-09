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

#include <Spore\App\PropertyList.h>
#include <EASTL\vector.h>

using namespace eastl;

namespace Graphics
{

	// off_17008A4: baked lighting for shaders
	class LightingProperties
	{
	public:
		enum Flags
		{
			kUseSkylight = 0x10,
			kUsePointLight = 0x20
		};

	public:
		/* 00h */	intrusive_ptr<App::PropertyList> mpPropList;
		/* 04h */	int mFlags;
		/* 08h */	Vector3 field_08;
		/* 14h */	float field_14;  // 1.0
		/* 18h */	float field_18;
		/* 1Ch */	float field_1C;
		/* 20h */	float field_20;  // -1.0
		/* 24h */	Vector3 field_24;
		/* 30h */	float field_30;  // 1.0
		/* 34h */	float field_34;
		/* 38h */	float field_38;
		/* 3Ch */	float field_3C;  // -1.0
		/* 40h */	Vector3 field_40;
		/* 4Ch */	float field_4C;  // 1.0
		/* 50h */	float field_50;
		/* 54h */	float field_54;
		/* 58h */	float field_58;  // -1.0
		/* 5Ch */	Vector3 field_5C;
		/* 68h */	float field_68;  // 1.0
		/* 6Ch */	float field_6C;
		/* 70h */	float field_70;
		/* 74h */	float field_74;  // -1.0
		/* 78h */	Vector3 mPointLightColor;
		/* 84h */	float mPointLightStrength;  // 1.0
		/* 88h */	float mPointLightRadius;  // 10.0
		/* 8Ch */	Vector3 mPointLightPos;
		/* 98h */	ColorRGB mSkylight;
		/* A4h */	bool mbCameraSpaceLighting;
		/* A8h */	vector<int> field_A8;
		/* BCh */	vector<int> field_BC;
		/// Global planet lighting multiplier -- 0 = off.
		/* D0h */	float mPlanetAtmosphere;
		/* D4h */	float field_D4;  // 1.0
		/* D8h */	float field_D8;  // 1.0
		/* DCh */	float field_DC;
		/* E0h */	float field_E0;
		/* E4h */	Vector4 field_E4;
		/* F4h */	Vector4 field_F4;
		/* 104h */	Vector4 field_104;
		/* 114h	*/	float field_114;  // 0.2
		/* 118h	*/	float field_118;  // 10.0
		/* 11Ch	*/	float field_11C;  // 0.2
		/* 120h */	float field_120;  // 10.0
		/* 124h */	float field_124;
		/* 128h */	float field_128;
		/* 12Ch */	float field_12C;  // 1000.0
		/* 130h */	float field_130;
		/* 134h */	bool field_134;  // true
		/* 138h */	float field_134;  // 0.5
		/* 13Ch */	float field_13C;  // 40.0
		/* 140h */	float field_140;
	};

	static_assert(sizeof(LightingProperties) == 0x144, "sizeof(LightingProperties) != 144h");
}