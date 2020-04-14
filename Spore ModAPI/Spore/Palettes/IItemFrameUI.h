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
		static const uint32_t TYPE = 0x4785A3D;

		IItemFrameUI();
		virtual ~IItemFrameUI() {};

		/* 04h */	virtual void Initialize(PaletteItem* pItem, IWindow* pWindow, IWindow* pItemsPanel, void*) = 0;
		/* 08h */	virtual void Dispose() = 0;
		/* 0Ch */	virtual void SetPaletteItem(PaletteItem* pItem) = 0;
		/* 10h */	virtual PaletteItem* GetPaletteItem() = 0;
		/* 14h */	virtual void func14h() = 0;
		/* 18h */	virtual void Update(int dt) = 0;
		/* 1Ch */	virtual void OnMouseEnter() = 0;
		/* 20h */	virtual void OnMouseLeave() = 0;
		/* 24h */	virtual void OnMouseDown() = 0;
		/* 28h */	virtual void OnMouseUp() = 0;
		/* 2Ch */	virtual void SetVisible(bool visible) = 0;

	protected:
		PaletteItemPtr mpItem;
		uint32_t mFrameTypeID;
	};


	class DefaultItemFrameUI 
		: public IItemFrameUI
		, public IWinProc
		, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x4784B27;

		DefaultItemFrameUI();

		int AddRef() override;
		int Release() override;
		void* Cast(uint32_t type) const override;

		void Initialize(PaletteItem* pItem, IWindow* pWindow, IWindow* pItemsPanel, void*) override;
		void Dispose() override;
		void SetPaletteItem(PaletteItem* pItem) override;
		PaletteItem* GetPaletteItem() override;
		void func14h() override;
		void Update(int dt) override;
		void OnMouseEnter() override;
		void OnMouseLeave() override;
		void OnMouseDown() override;
		void OnMouseUp() override;
		void SetVisible(bool visible) override;

		int GetEventFlags() const override;
		bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

	protected:
		/* 14h */	int field_14;
		/* 18h */	bool mIsHovering;
		/* 1Ch */	IWindowPtr mpWindow;
	};


	struct UnkItemFrameMessage_
	{
		virtual ~UnkItemFrameMessage_() {}
		virtual int AddRef() = 0;
		virtual int Release() = 0;
	};
	struct UnkItemFrameMessage
		: public UnkItemFrameMessage_
		, public IVirtual
	{
		int AddRef() override;
		int Release() override;

		/* 08h */	int mnRefCount;
		/* 0Ch */	uint32_t messageID;
		/* 10h */	uint32_t frameTypeID;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	ObjectPtr field_20;
		/* 24h */	ObjectPtr field_24;
	};
}