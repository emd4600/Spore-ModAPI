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

namespace UTFWin
{
	class OutlineFormat
	{
	public:
		OutlineFormat();
		OutlineFormat(const OutlineFormat& other);

		/* 00h */	int size;
		/* 04h */	int strength;
		/* 08h */	int quality;
		/* 0Ch */	float offsetX;
		/* 10h */	float offsetY;
		/* 14h */	float sizeX;
		/* 18h */	float sizeY;
		/* 1Ch */	float smoothness;
		/* 20h */	float saturation;
		/* 24h */	Math::Color color;

		///
		/// Sets the strength of the outline. This will also change the smoothness and saturation:
		/// the bigger the strength, the greater the saturation will be, but the smoothness value will be smaller.
		///
		void SetStrength(int strength);

		///
		/// Sets the size of the outline. This will also change sizeX and sizeY properties.
		///
		void SetSize(int size);
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(OutlineFormat) == 0x28, "sizeof(OutlineFormat) != 28h");

	inline OutlineFormat::OutlineFormat()
		: size(0)
		, strength(2)
		, quality(3)
		, offsetX(0)
		, offsetY(0)
		, sizeX(0)
		, sizeY(0)
	{
	}

	inline OutlineFormat::OutlineFormat(const OutlineFormat& other)
		: size(other.size)
		, strength(other.strength)
		, quality(other.quality)
		, offsetX(other.offsetX)
		, offsetY(other.offsetY)
		, sizeX(other.sizeX)
		, sizeY(other.sizeY)
		, smoothness(other.smoothness)
		, saturation(other.saturation)
	{
	}
}