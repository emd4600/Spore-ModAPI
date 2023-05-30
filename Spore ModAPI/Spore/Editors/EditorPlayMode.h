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
#include <Spore\App\IMessageListener.h>
#include <Spore\Editors\IPlayModeModule.h>
#include <Spore\Editors\PlayModeUI.h>
#include <Spore\Editors\PlayModeAnimations.h>
#include <Spore\Editors\PlayModeActor.h>
#include <Spore\Editors\PlayModeBackgrounds.h>
#include <EASTL\vector.h>

//TODO vftable 10h OnMouseClick sub_62A810

namespace Editors
{
	class cEditor;

	//PLACEHOLDER complete this
	class EditorPlayMode 
		: public DefaultRefCounted
		, public App::IUnmanagedMessageListener
	{
	public:
		// sub_639D70 walks?

		/* 10h */	virtual bool OnMouseDown(int mouseButton, float mouseX, float mouseY, int flags);
		/* 14h */	virtual bool OnMouseUp(int mouseButton, float mouseX, float mouseY, int flags);
		/* 18h */	virtual bool OnMouseMove(float mouseX, float mouseY, int state);
		/* 1Ch */	virtual bool OnKeyDown(int virtualKey, int modifiers);
		/* 20h */	virtual bool OnKeyUp(int virtualKey, int modifiers);
		/* 24h */	virtual bool HandleUIButton(uint32_t buttonID);

		void Update(int deltaMS);

		void Load(cEditor* editor, int8_t playModeBackgroundSet);
		void Dispose();

		uint32_t GetNextEnvironmentReactionAnimID();

		void sub_628CC0(bool);

	public:
		struct UnkStruct
		{
			/* 00h */	eastl::string16 field_0;
			/* 10h */	eastl::string16 field_10;
			/* 20h */	eastl::string16 field_20;
			/* 30h */	eastl::string16 field_30;
			/* 40h */	eastl::string16 field_40;
		};
		ASSERT_SIZE(UnkStruct, 0x50);

		/* 0Ch */	PlayModeUIPtr mpUI;
		/* 10h */	char padding_10[0x7C - 0x10];
		/* 7Ch */	PlayModeActor** mpMainActor;  // at 10h, AnimatedCreatureController
		/* 80h */	char padding_80[0xC8 - 0x80];
		/* C8h */	IPlayModeModule* mModules[4];
		/* D8h */	char padding_D8[0x3588 - 0xD8];
		/* 3588h */	PlayModeAnimations mAnimations;
		/* 3614h */	cEditor* mpEditor;
		/* 3618h */	PlayModeBackgrounds mBackgrounds;
		/* 3660h */	int field_3660;
		/* 3664h */	uint32_t mCollisionBGPropertyID;  // not initialized, it is set to 'editorPlayModeCollisionBG' on Load
		/* 3668h */	float field_3668;
		/* 366Ch */	eastl::vector<int> field_366C;
		/* 3680h */	eastl::vector<int> field_3680;
		/* 3694h */	eastl::vector<int> field_3694;
		/* 36A8h */	eastl::vector<int> field_36A8;
		/* 36BCh */	char padding_36BC[0x36D0 - 0x36BC];  // not initialized
		/* 36D0h */	int8_t field_36D0;  //TODO 36D0h mNumAdditionalActors
		/* 36D4h */	uint32_t mLastEnvironmentReactionAnimID;  // not initialized
		/* 36D8h */	int padding_36D4[(0x36E4 - 0x36D8) / 4];  // not initialized
		/* 36E4h */	uint32_t mLookAtMeButtonID;  // not initialized
		/* 36E8h */	uint32_t field_36E8;  // not initialized
		/* 36ECh */	uint32_t field_36EC;  // not initialized
		/* 36F0h */	Clock field_36F0;
		/* 3708h */	int8_t field_3708;  // not initialized
		/* 3709h */	int8_t field_3709;
		/* 370Ah */	int8_t mPlayModeBackgroundSet;
		/* 370Ch */	UnkStruct field_370C[52];
		/* 474Ch */	UnkStruct field_474C[52];
	};
	ASSERT_SIZE(EditorPlayMode, 0x5790);

	namespace Addresses(EditorPlayMode)
	{
		DeclareAddress(Load);  // 0x62A3F0 0x62A400
		DeclareAddress(Dispose);  // 0x62C930 0x62C940
		DeclareAddress(GetNextEnvironmentReactionAnimID);  // 0x6286C0 0x6286D0
		DeclareAddress(sub_628CC0);  // 0x628CC0 0x628CD0
		DeclareAddress(HandleUIButton);  // 0x628D70 0x628D80
		DeclareAddress(OnMouseDown);  // 0x62A810 0x62A820
		DeclareAddress(OnMouseUp);  // 0x628540 0x628550
		DeclareAddress(OnMouseMove);  // 0x628590 0x6285A0
		DeclareAddress(OnKeyDown);  // 0x628B10 0x628B20
		DeclareAddress(OnKeyUp);  // 0x6285E0 0x6285F0
		DeclareAddress(Update);  // 0x62C570 0x62C580
	}
}