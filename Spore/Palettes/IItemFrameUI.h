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

#include <Spore\Palettes\PaletteItem.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IWinProc.h>

namespace Palettes
{
	using namespace UTFWin;

	class IItemFrameUI
	{
	public:

		virtual ~IItemFrameUI() {};

		/* 04h */	virtual void Initialize(PaletteItem* pItem, IWindow* pWindow, IWindow* pItemsPanel, void*) = 0;
		/* 08h */	virtual void Dispose() = 0;
		// A setter for a intrusive_ptr<DefaultRefCounted>
		/* 0Ch */	virtual void func0Ch(int) = 0;
		/* 10h */	virtual int func10h() = 0;
		/* 14h */	virtual void func14h() = 0;
		/* 18h */	virtual void func18h(int) = 0;
		/* 1Ch */	virtual void func1Ch() = 0;
		/* 20h */	virtual void func20h() = 0;
		/* 24h */	virtual void func24h() = 0;
		/* 28h */	virtual void func28h() = 0;
		/* 2Ch */	virtual void SetVisible(bool bVisible) = 0;

	protected:
		int mnRefCount;
		uint32_t mFrameTypeID;
	};

	class DefaultItemFrameUI : public IItemFrameUI, public IWinProc, public DefaultRefCounted
	{
	public:
		DefaultItemFrameUI();

	protected:
		/* 14h */	int field_14;
		/* 18h */	bool field_18;
		/* 1Ch */	int field_1C;
	};
}