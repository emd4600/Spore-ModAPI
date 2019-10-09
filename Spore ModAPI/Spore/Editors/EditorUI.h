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

#include <Spore\App\IMessageListener.h>
#include <Spore\App\IMessageManager.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\UILayout.h>
#include <EASTL\array.h>

namespace Editors
{
	using namespace UTFWin;
	class Editor;
	
	class _EditorUI_interface {
		// ?
		virtual void func00h(const ResourceKey&) = 0;
	};

	class EditorUI
		: public _EditorUI_interface
		, public IWinProc
		, public App::IMessageListener
		, public DefaultRefCounted
	{
	public:
		EditorUI();
		virtual ~EditorUI();

		//TODO sub_5DE330 Update

		bool Load(Editor* pEditor, uint32_t instanceID, uint32_t groupID, bool editorModelForceSaveover);

		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

		virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

	public:

		/* 14h */	UTFWin::UILayout mMainUI;
		/* 2Ch */	UTFWin::UILayout mSharedUI;
		/* 44h */	UTFWin::UILayout mCameraControlsUI;
		/* 5Ch */	Editor* mpEditor;
		/* 60h */	int field_60;
		/* 64h */	IWindow* field_64;  // 0x5100B176
		/* 68h */	IWindow* field_68;  // 0xF006F308
		/* 6Ch */	IWindow* field_6C;  // 0xF006F309
		/* 70h */	IWindow* field_70;  // 0xD0353720
		/* 74h */	int field_74;  // IWinGrid*, editor types
		/* 78h */	IWindow* field_78;
		/* 7Ch */	int field_7C;
		/* 80h */	IWindow* field_80;  // 0x908891A7
		/* 84h */	IWindow* field_84;  // 0xF383C97D
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;  // not initialized
		/* 98h */	int field_98;
		/* 9Ch */	int field_9C;
		/* A0h */	bool mbEditorModelForceSaveover;
		/* A1h */	bool field_A1;  // true
		/* A2h */	bool field_A2;
		/* A3h */	char field_A3;  // 0xFF
		/* A4h */	int field_A4;  // not initialized
		/* A8h */	int field_A8;
		/* ACh */	int field_AC;
		/* B0h */	int field_B0;
		/* B4h */	int field_B4;  // vftable, related with sound?
		/* B8h */	int field_B8;  // points to this
		/* BCh */	int field_BC;
		/* C0h */	int field_C0;
		/* C4h */	int field_C4;
		/* C8h */	int field_C8;  // not initialized
		/* CCh */	int field_CC;
		/* D0h */	bool field_D0;  // true
		/* D1h */	bool field_D1;  // true
		/* D4h */	int field_D4;
		/* D8h */	int field_D8;
		/* DCh */	int field_DC;
		/* E0h */	int field_E0;
		/* E4h */	bool field_E4;
		/* E5h */	bool field_E5;
		/* E8h */	int field_E8;
		/* ECh */	bool field_EC;
		/* F0h */	int field_F0;
		/* F4h */	bool field_F4;
		/* F8h */	int field_F8;
		/* FCh */	int field_FC;
		/* 100h */	bool field_100;
		/* 101h */	bool field_101;
		/* 102h */	bool field_102;
		/* 103h */	bool field_103;  // true
		/* 104h */	bool field_104;
		/* 105h */	bool field_105;
		/* 106h */	bool field_106;  // true
		/* 107h */	bool field_107;
		/* 108h */	int field_108;
		/* 10Ch */	bool field_10C;
		/* 110h */	int field_110;
		/* 114h */	bool mbMessageListenerAdded;
		/* 118h */	App::IMessageManager* mpMessageManager;
		/* 11Ch */	App::IMessageListener* mpMessageListener;  // this
		/* 120h */	uint32_t* mMessageIDs;
		/* 124h */	size_t mNumMessageIDs;  // 7
		/* 128h */	int field_128;

		// loc_5DCD86 -> disable undo button?

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(EditorUI) == 0x12C, "sizeof(EditorUI) must be 0x20C!");
	static_assert(sizeof(eastl::array<uint32_t>) == 8, "sizeof(EditorUI) must be 8!");

	namespace Addresses(EditorUI)
	{
		DeclareAddress(HandleMessage, SelectAddress(0x5DED50, 0x5DEEB0, 0x5DEEB0));

		DeclareAddress(HandleUIMessage, SelectAddress(0x5DFEE0, 0x5E0040, 0x5E0040));

		DeclareAddress(Load, SelectAddress(0x5DDC40, 0x5DDDA0, 0x5DDDA0));
	}
};