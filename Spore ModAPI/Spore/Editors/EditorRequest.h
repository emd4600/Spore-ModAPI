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
#include <Spore\Object.h>
#include <Spore\Editors\ContentValidation.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

namespace Editors
{
	class IRefCounted {
	public:
		virtual ~IRefCounted() {};
		virtual int AddRef() = 0;
		virtual int Release() = 0;
	};
	
	///
	/// This class is used to access the editors. When you create a new instance of this,
	/// you have to set the \c editorID field to the ID of the editor you want to go to. 
	/// That is the ID of the configuration file in the \c editor_setup~ folder.
	/// There are some additional properties that control features available in the editor
	/// By default, new instances of this class have the properties set to:
	/// - \c sporepediaCanSwitch: false
	/// - \c disableNameEdit: false
	/// - \c allowSporepedia: false
	/// - \c hasSaveButton: false
	/// - \c hasCreateNewButton: false
	/// - \c hasExitButton: false
	/// - \c hasPublishButton: false
	/// - \c hasCancelButton: true
	///
	/// Example usage:
	/// \code{.cpp}
	/// intrusive_ptr<EditorRequest> request = new EditorRequest();
	/// request->editorID = id("CreatureEditorExtraLarge");
	/// request->allowSporepedia = true;
	/// request->hasSaveButton = true;
	/// 
	/// EditorRequest::Submit(request.get());
	/// \endcode
	class EditorRequest
		: public IRefCounted
		, public IVirtual
	{
	public:
		EditorRequest();
		virtual ~EditorRequest();

		virtual int AddRef() override;
		virtual int Release() override;

		void SetDefaultValidation();

		/// When this method is executed, the given request will be processed and 
		static bool Submit(EditorRequest* request);

	protected:
		/* 08h */	int mRefCount;

	public:
		/// The ID of the editor, such as 'id("CreatureEditorExtraLarge")'
		/* 0Ch */	uint32_t editorID;  // -1
		/// You can use this field to preload a creation.
		/* 10h */	ResourceKey creationKey;
		/* 1Ch */	uint32_t activeModeID;
		/* 20h */	bool field_20;
		/* 24h */	ContentValidation editableTests;
		/// If true, the user can change the editor by selecting a different creation type in the Sporepedia.
		/// False by default.
		/* 34h */	bool sporepediaCanSwitch;
		/// If true, the creation name cannot be edited. False by default.
		/* 35h */	bool disableNameEdit;
		/// If true, the user can edit a creation from the Sporepedia. If false, clicking the Sporepedia button
		/// will show all types of creations, but they won't be editable. False by default.
		/* 36h */	bool allowSporepedia;
		/// Whether the "Save" button is shown. False by default.
		/* 37h */	bool hasSaveButton;
		/// Whether the "Create new" button is shown. False by default.
		/* 38h */	bool hasCreateNewButton;
		/// Whether the "Exit to main menu" and "Exit game" buttons are enabled.
		/// True by default.
		/* 39h */	bool hasExitButton;
		/// Whether the "Publish creation" button is shown.
		/// False by default.
		/* 3Ah */	bool hasPublishButton;
		/// Whether the "Cancel" button is shown. True by default.
		/* 3Bh */	bool hasCancelButton;  // true
		/* 3Ch */	bool field_3C;
		/* 3Dh */	bool field_3D;  // true

		/* 40h */	eastl::string16 field_40;
		/* 50h */	eastl::string16 field_50;

		/* 60h */	float field_60;
		/* 64h */	bool field_64;
		/* 65h */	bool field_65;  // show (unused) play button?
		/* 66h */	bool field_66;
		/* 68h */	int field_68;
		/* 6Ch */	bool field_6C;
		/* 6Dh */	bool field_6D;  // true
		/* 6Eh */	bool field_6E;  // true
		/* 6Fh */	bool field_6F;

		/* 70h */	eastl::vector<void*> field_70;
		/* 84h */	int field_84;
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	uint32_t field_90;
		/* 94h */	intrusive_ptr<Object> field_94;
		/* 98h */	intrusive_ptr<EditorRequest> next;
	};

	static_assert(sizeof(EditorRequest) == 0x9C, "sizeof(EditorRequest) != 9Ch");

	inline void EditorRequest::SetDefaultValidation() {
		editableTests = ContentValidation::ValidationEditableTests();
	}

	namespace Addresses(EditorRequest) {
		DeclareAddress(Submit);
	}
}
