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
#include <EASTL\map.h>

using namespace eastl;

namespace Simulator
{
	///
	/// A Simulator class inherited by all those classes that can have an identity color, such as 
	/// empires, tribes, etc
	///
	/// The following attributes are saved:
	/// - mIDColorID
	/// - mCachedColor
	///
	class cIdentityColorable
	{
	public:
		static const uint32_t TYPE = 0x5593A1A;

		virtual ~cIdentityColorable();

		/* 04h */	virtual uint32_t GetType();
		/* 08h */	virtual int AddRef() = 0;
		/* 0Ch */	virtual int Release() = 0;
		/* 10h */	virtual void* Cast(uint32_t typeID);
		/* 14h */	virtual void Write(void*);
		/* 18h */	virtual void Read(void*);

	protected:
		/* 04h */	uint32_t mIDColorID;  // 0x53DBCF1
		/* 08h */	map<int, int> field_8;
		/* 24h */	Math::ColorRGB mCachedColor;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cIdentityColorable) == 0x30, "sizeof(cIdentityColorable) != 30h");
}