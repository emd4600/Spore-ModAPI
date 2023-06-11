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

#include <Spore\ResourceID.h>

namespace Swarm
{
	enum class DrawMode : uint8_t
	{
		Decal = 0,
		DecalInvertDepth = 1,
		DecalIgnoreDepth = 2,
		DepthDecal = 3,
		DecalDepth = 3,
		Additive = 4,
		AdditiveInvertDepth = 5,
		AdditiveIgnoreDepth = 6,
		Modulate = 7,
		NormalMap = 8,
		DepthNormalMap = 9,
		NormalMapDepth = 9,
		AlphaTestDissolve = 0xA,
		User1 = 0xB,
		User2 = 0xC,
		User3 = 0xD,
		User4 = 0xE,
		None = 0xF
	};

	class cTextureSlot
	{
	public:
		cTextureSlot();

		/* 00h */	ResourceID resourceID;
		/* 08h */	unsigned char format;
		/* 09h */	DrawMode drawMode;
		/* 0Ah */	unsigned char drawFlags;
		/* 0Bh */	unsigned char buffer;
		/* 0Ch */	unsigned short layer;
		/* 10h */	float sortOffset;
		/* 14h */	int field_14;
		/* 18h */	ResourceID field_18;

		enum Flags
		{
			kFlagLight = 0x1,
			kFlagNoFog = 0x2,
			kFlagShadow = 0x8,
			kFlagNoShadow = 0xF7,
			kFlagNoCull = 0x10,
			kFlagUser1 = 0x20,
			kFlagUser2 = 0x40,
			kFlagUser3 = 0x80
		};
	};
	ASSERT_SIZE(cTextureSlot, 0x20);

	inline cTextureSlot::cTextureSlot()
		:
		resourceID(), format(0), drawMode(DrawMode::Decal), drawFlags(0),
		buffer(0), layer(0), sortOffset(0), field_18()
	{
	}
}