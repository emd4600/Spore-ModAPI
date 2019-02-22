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

#include <Spore\RenderWare\RWSectionInfo.h>
#include <Spore\Internal.h>

namespace RenderWare
{
	struct RWObjectQuery
	{
		RWObjectQuery();

		/* 00h */	uint32_t typeCode;
		/* 04h */	void* pData;
		/* 08h */	int field_8[4];
		/* 18h */	int field_18[8];
	};

	///
	/// A structure that represents the general information contained in the header of a rw4 file.
	///
	struct RWHeader
	{
		/* 00h */	char mMagic[28];
		/* 1Ch */	int mRWTypeCode;
		/* 20h */	int field_20;  // usually same as sectionCount
		/* 24h */	size_t mnSectionCount;
		/* 28h */	int field_28;  // 0x10 if it's a model, 4 if it's a texture
		/* 2Ch */	int field_2C;
		/* 30h */	RWSectionInfo* mpSectionInfos;
		/* 34h */	int field_34;
		/* 38h */	int field_38;  // always 0x98
		/* 3Ch */	int field_3C;  // always 0 ?
		/* 40h */	int field_40;  // always 0 ?
		/* 44h */	int field_44;  // always 0 ?
		/* 48h */	void* mpBufferData;

		void GetRWObject(int index, RWObjectQuery& query);
	};

	namespace InternalAddressList(RWHeader)
	{
		DefineAddress(GetRWObject, GetAddress(0x11E5060,, 0x11E2920));
	}
}