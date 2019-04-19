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
#include <cinttypes>

namespace App
{
	class StandardMessage : public MultithreadObject
	{
	public:
		union MessageParameter
		{
			int8_t		int8;
			uint8_t		uint8;
			int16_t		int16;
			uint16_t	uint16;
			int32_t		int32;
			uint32_t	uint32;
			int64_t		int64;
			uint64_t	uint64;
			float		_float;
			double		_double;
			Object*		object;
		};

		StandardMessage();
		virtual ~StandardMessage();

		/* 08h */	MessageParameter params[5];
		/* 30h */	uint32_t id;
		/* 34h */	int field_34;
		/* 38h */	uint32_t objectFlags;
		/* 3Ch */	int field_3C;

		void SetObject(size_t nIndex, Object* pObject);
	};

	inline void StandardMessage::SetObject(size_t nIndex, Object* pObject)
	{
		params[nIndex].object = pObject;
		objectFlags |= (1 << nIndex);
	}
}