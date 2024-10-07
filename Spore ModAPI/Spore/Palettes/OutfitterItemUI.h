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
#include <Spore\UTFWin\UILayout.h>
#include <Spore\Palettes\IItemFrameUI.h>

namespace Palettes
{
	enum ControlIDs
	{
		/// The ControlID of the button used to edit the creature.
		kControlEditButton = 0x5384F7B5,
	};

	enum PaletteMessages
	{
		kMsgSetCreation = 0x53850BAF
	};

	class OutfitterItemUI : public DefaultItemFrameUI, public App::IMessageListener
	{
	public:
		virtual void Initialize(PaletteItem* pItem, UTFWin::IWindow* pWindow, UTFWin::IWindow* pItemsPanel, PaletteInfo* pInfo) override;

	public:
		/* 24h */	IWindowPtr field_24;  // possible display of the creature
		/* 28h */	IWindowPtr mpMainWindow;
		/* 2Ch */	IWindowPtr field_2C;
		/* 30h */	IWindowPtr field_30;
		/* 34h */	IWindowPtr mpEditButton;
		/* 38h */	UILayoutPtr mpLayout;
		/* 3Ch */	int field_3C;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	ResourceKey mCreationName;
		/* 60h */	uint32_t mOutfitEditorUI;
		/* 64h */	int field_64;
		/* 68h */	int field_68;  // not initialized
		/// If this palette item happens to be an editor model, this will point to the model type.
		/* 6Ch */	uint32_t mItemModelTypeID;  // -1
		/// `toolData_ToolType`
		/* 70h */	uint32_t mToolTypeID;
	};
	namespace Addresses(OutfitterItemUI) {
		DeclareAddress(Initialize);  // 0x5EF6E0 0x5EF8D0
	}
}