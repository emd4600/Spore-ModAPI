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
			int8_t		mnInt8;
			uint8_t		mnUInt8;
			int16_t		mnInt16;
			uint16_t	mnUInt16;
			int32_t		mnInt32;
			uint32_t	mnUInt32;
			int64_t		mnInt64;
			uint64_t	mnUInt64;
			float		mfFloat;
			double		mfDouble;
			Object*		mpObject;
		};

		StandardMessage();
		virtual ~StandardMessage();

		/* 08h */	MessageParameter mParams[5];
		/* 30h */	uint32_t mID;
		/* 34h */	int field_34;
		/* 38h */	uint32_t mObjectFlags;
		/* 3Ch */	int field_3C;

		void SetObject(size_t nIndex, Object* pObject);
	};

	inline void StandardMessage::SetObject(size_t nIndex, Object* pObject)
	{
		mParams[nIndex].mpObject = pObject;
		mObjectFlags |= (1 << nIndex);
	}
}