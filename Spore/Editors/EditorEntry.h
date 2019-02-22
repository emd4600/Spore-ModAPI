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

#include <Spore\Internal.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

// absolutely no idea of what this is, I invented the name

namespace Editors
{
	class EditorEntryDelegate
	{
	public:
		EditorEntryDelegate() {
			VOID_THISCALL(GetAddress(0x5A8F10, 0x5A9140, 0x5A9140), this);
		};

	public:
		/* 00h */	int vftable_0;
		/* 04h */	int vftable_1;
		/* 08h */	int useCount;
		/* 0Ch */	int field_0C;
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	uint32_t mActiveContextID;
		/* 20h */	bool field_20;
		/* 24h */	int field_24;
		/* 28h */	int field_28;
		/* 2Ch */	int field_2C;
		/* 30h */	int field_30;
		/* 34h */	bool field_34;
		/* 35h */	bool field_35;
		/* 36h */	bool field_36;
		/* 37h */	bool field_37;
		/* 38h */	bool field_38;
		/* 39h */	bool field_39;
		/* 3Ah */	bool field_3A;
		/* 3Bh */	bool field_3B;
		/* 3Ch */	bool field_3C;
		/* 3Dh */	bool field_3D;

		/* 40h */	eastl::string field_40;
		/* 50h */	eastl::string field_50;

		/* 60h */	float field_60;
		/* 64h */	bool field_64;
		/* 65h */	bool field_65;
		/* 66h */	bool field_66;
		/* 68h */	int field_68;
		/* 6Ch */	bool field_6C;
		/* 6Dh */	bool field_6D;
		/* 6Eh */	bool field_6E;
		/* 6Fh */	bool field_6F;

		/* 70h */	eastl::vector<void*> field_70;
		/* 84h */	int field_84;
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
		/* 98h */	int field_98;
	};

	static_assert(sizeof(EditorEntryDelegate) == 0x9C, "sizeof(EditorEntryDelegate) != 9Ch");
}
