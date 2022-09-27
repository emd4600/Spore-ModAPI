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
#include <Spore\Editors\INameableEntity.h>
#include <Spore\Editors\cEditorResource.h>

#include <EASTL\string.h>
#include <EASTL\vector.h>

namespace Editors 
{
	/// Represents the state of a creation in an editor. This class keeps track of all its parts and paints,
	/// and is used to load and save the creation of the editor.
	/// The data can be converted into a cEditorResource with the Load() and Save() methods;
	/// then, you can use the ResourceManager to save the editor resource into a `.crt`, `.bld`, etc file.
	class EditorModel
		: public INameableEntity
		, public IVirtual
	{
	public:
		EditorModel();
		virtual ~EditorModel();

		virtual void SetName(const char16_t* pString) override;
		virtual const char16_t* GetName() override;
		virtual void SetDescription(const char16_t* pString) override;
		virtual const char16_t* GetDescription() override;
		virtual void SetTags(const char16_t* pString) override;
		virtual const char16_t* GetTags() override;


		void Load(cEditorResource* pResource);
		void Save(cEditorResource* pResource);

		void Dispose();

		string16& GetCreationName() const;

		void SetColor(int index, struct ColorRGB color);

		ColorRGB GetColor(int index) const;

		int GetPartsCount() const;
		EditorRigblock* GetPart(int index);

	protected:
		/* 08h */	int mnRefCount;

	public:
		/* 0Ch */	ResourceKey mKey;
		/* 18h */	vector<EditorRigblockPtr> mParts;
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
		/* 54h */	int mTranslationOptions;
		/* 58h */	uint32_t mModelType;
		/* 5Ch */	string16 mName;
		/* 6Ch */	string16 mDescription;  // message 0x14418C3F ?
		/* 7Ch */	string16 mAcceptedName;  // the name after removing illegal characters
		/* 8Ch */	int mSkinEffectIDs[3];
		/* 98h */	int mSkinEffectSeeds[3];  // 1234
		/* A4h */	ColorRGB mColors[3];
		/* C8h */	vector<BoundingBox> field_C8;
		/* DCh */	int mZCorpScore;  // not initialized
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(EditorModel) == 0xE0, "sizeof(cOrnament) != E0h");

	namespace Addresses(EditorModel)
	{
		DeclareAddress(SetName);  // 0x4ADC20, 0x4AE280
		DeclareAddress(SetDescription);  // 0x4ADDE0, 0x4AE440
		DeclareAddress(GetCreationName);
		DeclareAddress(SetColor);
		DeclareAddress(Load);  // 0x4AE240, 0x4AE8D0
		DeclareAddress(Save);  // 0x4AF0F0, 0x4AF780
		DeclareAddress(Dispose);  // 0x4AD1F0, 0x4AD850
	}

	inline ColorRGB EditorModel::GetColor(int index) const {
		return mColors[index];
	}

	inline int EditorModel::GetPartsCount() const {
		return mParts.size();
	}
	inline EditorRigblock* EditorModel::GetPart(int index) {
		return mParts[index].get();
	}
}

