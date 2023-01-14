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

#include <Spore\UTFWin\IWinProc.h>
#include <Spore\Palettes\PaletteItem.h>
#include <Spore\Palettes\ItemViewer.h>
#include <Spore\Object.h>

#define StandardItemUIPtr eastl::intrusive_ptr<Palettes::StandardItemUI>

namespace Palettes
{
	class StandardItemUI
		: public DefaultRefCounted
		, public UTFWin::IWinProc
	{
	public:
		StandardItemUI();
		virtual ~StandardItemUI();

		using DefaultRefCounted::AddRef;
		using DefaultRefCounted::Release;

		virtual bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

	public:
		/* 0Ch */	PaletteItemPtr mpItem;
		/* 10h */	int field_10;
		/* 14h */	ItemViewerPtr mpViewer;
		/* 18h */	IWindowPtr field_18;
		/* 1Ch */	bool field_1C;
	};
	ASSERT_SIZE(StandardItemUI, 0x20);

	namespace Addresses(StandardItemUI)
	{
		DeclareAddress(HandleUIMessage);
	}
}