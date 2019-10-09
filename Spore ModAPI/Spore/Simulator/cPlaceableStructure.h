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

#include <Spore\Object.h>

namespace Simulator
{
	///
	/// A structure that can be placed into a community slot, like buildings, turrets, ornaments and tribe tools.
	///
	class cPlaceableStructure
	{
	public:

		static const uint32_t TYPE = 0xE89ADF71;

		virtual ~cPlaceableStructure();

		/* 04h */	virtual int func04h();
		/* 08h */	virtual int func08h();
		/* 0Ch */	virtual int func0Ch();
		/* 10h */	virtual bool func10h();
		/* 14h */	virtual bool func18h();
		/* 18h */	virtual void* Cast(uint32_t typeID);
		/* 1Ch */	virtual int AddRef() = 0;
		/* 20h */	virtual int Release() = 0;
	};
}