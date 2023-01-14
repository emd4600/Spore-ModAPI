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

namespace Graphics
{

	// off_17008A4: baked lighting for shaders
	class cLightingConfig
	{
	public:
		enum Flags
		{
			kUseSkylight = 0x10,
			kUsePointLight = 0x20
		};

		struct DirectionalLight {
			/* 00h */	Math::ColorRGB color;  // black
			/* 0Ch */	float strength;  // 1.0
			/* 10h */	Math::Vector3 direction;  // 0,0,-1
		};

	public:
		/* 00h */	PropertyListPtr mpPropList;
		/* 04h */	int mFlags;
		/* 08h */	DirectionalLight dirLightSun;
		/* 24h */	DirectionalLight dirLightSky;
		/* 40h */	DirectionalLight dirLightFill1;
		/* 5Ch */	DirectionalLight dirLightFill2;
		/* 78h */	Math::Vector3 mPointLightColor;
		/* 84h */	float mPointLightStrength;  // 1.0
		/* 88h */	float mPointLightRadius;  // 10.0
		/* 8Ch */	Math::Vector3 mPointLightPos;
		/* 98h */	Math::ColorRGB mSkylight;
		/* A4h */	bool mbCameraSpaceLighting;
		/* A8h */	eastl::vector<int> field_A8;
		/* BCh */	eastl::vector<int> field_BC;
		/// Global planet lighting multiplier -- 0 = off.
		/* D0h */	float mPlanetAtmosphere;
		/* D4h */	float field_D4;  // 1.0
		/* D8h */	float field_D8;  // 1.0
		/* DCh */	float field_DC;
		/* E0h */	float field_E0;
		/* E4h */	Math::Vector4 field_E4;
		/* F4h */	Math::Vector4 field_F4;
		/* 104h */	Math::Vector4 field_104;
		/* 114h	*/	float field_114;  // 0.2
		/* 118h	*/	float field_118;  // 10.0
		/* 11Ch	*/	float field_11C;  // 0.2
		/* 120h */	float field_120;  // 10.0
		/* 124h */	float field_124;
		/* 128h */	float field_128;
		/* 12Ch */	float field_12C;  // 1000.0
		/* 130h */	float field_130;
		/* 134h */	bool field_134;  // true
		/* 138h */	float field_138;  // 0.5
		/* 13Ch */	float field_13C;  // 40.0
		/* 140h */	float field_140;
	};
	ASSERT_SIZE(cLightingConfig, 0x144);
}