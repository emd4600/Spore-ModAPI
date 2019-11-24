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

#include <Spore\ResourceKey.h>
#include <Spore\MathUtils.h>
#include <Spore\Editors\EditorRigblock.h>
#include <Spore\Simulator\cNameableEntity.h>

#include <EASTL\string.h>
#include <EASTL\vector.h>

namespace Editors 
{
	class EditorModel
		: public Simulator::cNameableEntity
		, public IVirtual
	{
	protected:
		/* 08h */	int mnRefCount;

	public:
		/* 0Ch */	ResourceKey field_0C;
		/* 18h */	vector<intrusive_ptr<EditorRigblock>> parts;
		/* 2Ch */	bool field_2C;
		/* 30h */	int field_30;  // intrusive_ptr, but not to an Object
		/* 34h */	bool field_34;
		/* 38h */	float field_38;
		/* 3Ch */	float field_3C;
		/* 40h */	float field_40;  // -2.0
		/* 44h */	float field_44;  // 2.0
		/* 48h */	float field_48; 
		/* 4Ch */	bool field_4C;
		/* 4Dh */	bool field_4D;
		/* 4Eh */	bool field_4E;  // true
		/* 4Fh */	bool field_4F;
		/* 50h */	bool field_50;
		/* 51h */	bool field_51;
		/* 54h */	int field_54;
		/* 58h */	uint32_t mModelType;
		/* 5Ch */	string16 mName;
		/* 6Ch */	string16 mDescription;  // message 0x14418C3F ?
		/* 7Ch */	string16 mAcceptedName;  // the name after removing illegal characters
		/* 8Ch */	int field_8C[3];
		/* 98h */	int field_98[3];  // 1234
		/* A4h */	ColorRGB mColors[3];
		/* C8h */	vector<int> field_C8;  // size 18h
		/* ECh */	int field_EC;  // not initialized

	public:

		string16& GetCreationName() const;

		void SetColor(int index, struct ColorRGB color);
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(EditorModel) == 0xE0, "sizeof(cOrnament) != E0h");

	namespace Addresses(EditorModel)
	{
		DeclareAddress(GetCreationName);
		DeclareAddress(SetColor);
	}
}

