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

#include <Spore\UTFWin\UIRenderer.h>
#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\Message.h>
#include <Spore\UTFWin\IWinProc.h>

#include <Spore\FixedPoolAllocator.h>
#include <Spore\MathUtils.h>

#include <EASTL\string.h>
#include <EASTL\list.h>
#include <EASTL\hash_map.h>

#define WindowPtr eastl::intrusive_ptr<UTFWin::Window>

namespace UTFWin
{

	class Window : public ILayoutElement, public IWindow
	{

	public:

		static const uint32_t TYPE = 0xEEC58382;

		Window();
		virtual ~Window();

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		virtual IWindow* GetParent() const override;
		virtual IWindowManager* GetWindowManager() const override;
		virtual int func6() const override;
		virtual uint32_t GetControlID() const override;
		virtual uint32_t GetCommandID() const override;
		virtual uint32_t GetCursorID() const override;
		virtual WindowFlags GetFlags() const override;
		virtual int GetState() const override;
		virtual Math::Color GetShadeColor() const override;
		virtual const Math::Rectangle& GetArea() const override;
		virtual const Math::Rectangle& GetRealArea() const override;
		virtual const char16_t* GetCaption() const override;
		virtual uint32_t GetTextFontID() const override;
		virtual const char16_t* func17() const override;
		virtual int func18() const override;
		virtual int func19() const override;
		virtual void SetControlID(uint32_t controlID) override;
		virtual void SetCommandID(uint32_t commandID) override;
		virtual void SetState(int state) override;
		virtual void SetShadeColor(Color color) override;
		virtual void SetArea(const Math::Rectangle& area) override;
		virtual void SetLocation(float fX, float fY) override;
		virtual void SetSize(float fWidth, float fHeight) override;
		virtual void SetLayoutArea(const Math::Rectangle& layoutArea) override;
		virtual void SetLayoutLocation(float fX, float fY) override;
		virtual void SetLayoutSize(float fWidth, float fHeight) override;
		virtual void SetCursorID(uint32_t) override;
		virtual void SetFlag(WindowFlags nFlag, bool bValue) override;
		virtual void SetCaption(const char16_t* pCaption) override;
		virtual void SetTextFontID(uint32_t styleID) override;
		virtual void func34(int) override;
		virtual void func35(int) override;
		virtual int Invalidate() override;
		virtual void Revalidate() override;
		virtual int InvalidateTransform() override;
		virtual int func39() override;
		virtual int func40() override;
		virtual Color GetFillColor() const override;
		virtual IDrawable* GetDrawable() const override;
		virtual void SetFillColor(Color color) override;
		virtual void SetDrawable(IDrawable* drawable) override;
		virtual int func45(int) override;
		virtual int func46(int, int) override;
		virtual bool ContainsPoint(struct Math::Point) override;
		virtual Math::Point ToGlobalCoordinates(struct Math::Point) override;
		virtual Math::Point ToLocalCoordinates(struct Math::Point) override;
		virtual bool ToLocalCoordinates2(struct Math::Point, Math::Point& dst) override;
		virtual IWindowList_t::iterator GetChildrenBegin() override;
		virtual IWindowList_t::iterator GetChildrenEnd() override;
		virtual IWindowList_t::iterator LocateChild(const IWindow* pChild) const override;
		virtual void AddWindow(IWindow* pWindow) override;
		virtual void RemoveWindow(IWindow* pWindow) override;
		virtual void DisposeWindowFamily(IWindow* pChildWindow) override;
		virtual void DisposeAllWindowFamilies() override;
		virtual void BringToFront(IWindow* pWindow) override;
		virtual void SendToBack(IWindow* pWindow) override;
		virtual IWindow* FindWindowByID(uint32_t controlID, bool bRecursive) override;
		virtual IWindow* FindWindowTypeByID(uint32_t controlID, uint32_t type, bool bRecursive) override;
		virtual bool IsAncestorOf(const IWindow* pChildWindow) override;
		virtual bool func63(int index) override;
		virtual bool func64(int index) override;
		virtual void AddWinProc(IWinProc* pWinProc) override;
		virtual void RemoveWinProc(IWinProc* pWinProc) override;
		virtual IWinProc* GetNextWinProc(const IWinProc* pWinProc) const override;
		virtual int func68(int) override;
		virtual bool SendMsg(Message& msg) override;
		virtual const char* GetComponentName() const override;

	protected:
		///
		/// A function that initializes this window. It is not always called so you should not rely on it.
		///
		/* 18h */	virtual bool Initialize();

		///
		/// A function that disposes this window, preparing it to be deleted. This method is called on the destructor, but it
		/// can be called before the window gets destructed as well.
		///
		/* 1Ch */	virtual bool Dispose();

		///
		/// A function called every time a message arrives to this window.
		///
		/* 20h */	virtual bool DoMessage(const UTFWin::Message& msg);

		///
		/// A method called every time this window needs to be painted. This does not paint the children windows.
		///
		/* 24h */	virtual bool OnPaint(UIRenderer* pRenderer);

	protected:

		typedef eastl::list<eastl::pair<IWinProcPtr, int>, FixedPoolAllocatorAdapter> IWinProcList_t;

		struct UnkMatrix4 : Math::Matrix4
		{
			UnkMatrix4();

			int field_40;
		};


	protected:
		/* 10h */	int field_10;
		/* 14h */	int field_14;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	int field_20;
		/* 24h */	int field_24;
		/* 28h */	int mnRefCount;
		/* 2Ch */	int mnFlags;
		/* 30h */	bool field_30;  // actually some flags
		/* 31h */	int8_t field_31;  // kUseDrawableCollision = 8
		/* 34h */	IWindowManager* mpWindowManager;
		/* 38h */	WindowPtr mpParentWindow;
		/* 3Ch */	IWindowList_t mChildrenWindows;
		/* 44h */	FixedPoolAllocator mPoolAllocator;
		/* 64h */	IWinProcList_t mWinProcs;
		/* 74h */	int field_74;
		/* 78h */	int field_78;
		/* 7Ch */	int field_7C;
		/* 80h */	uint32_t mControlID;
		/* 84h */	uint32_t mCommandID;
		/* 88h */	Math::Rectangle mRealArea;
		/* 98h */	Math::Rectangle mArea;
		/* A8h */	uint32_t mCursorID;
		/* ACh */	int mnStateFlags;
		/* B0h */	eastl::string16 mCaption;
		/* C0h */	uint32_t mTextFontID;
		/* C4h */	UnkMatrix4 field_C4;
		/* 108h */	UnkMatrix4 field_108;
		/* 14Ch */	UnkMatrix4 field_14C;
		/* 190h */	UnkMatrix4 field_190;
		/* 1D4h */	int field_1D4;
		/* 1D8h */	Math::Color mShadeColor;
		/* 1DCh */	Math::Color mFillColor;
		/* 1E0h */	IDrawablePtr mpDrawable;
		/* 1E4h */	ObjectPtr field_1E4;
		/* 1E8h */	ObjectPtr field_1E8;
		/* 1ECh */	eastl::hash_map<int, int> field_1EC;
	};
	ASSERT_SIZE(Window, 0x20C);

	namespace Addresses(Window)
	{
		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);
		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		DeclareAddress(DoMessage);
		DeclareAddress(OnPaint);

		DeclareAddress(GetParent);
		DeclareAddress(GetWindowManager);
		DeclareAddress(func6);
		DeclareAddress(GetControlID);
		DeclareAddress(GetCommandID);
		DeclareAddress(func9);
		DeclareAddress(GetCursorID);
		DeclareAddress(GetFlags);
		DeclareAddress(GetState);
		DeclareAddress(GetShadeColor);
		DeclareAddress(GetArea);
		DeclareAddress(GetRealArea);
		DeclareAddress(GetCaption);
		DeclareAddress(GetTextFontID);
		DeclareAddress(func17);
		DeclareAddress(func18);
		DeclareAddress(func19);
		DeclareAddress(SetControlID);
		DeclareAddress(SetCommandID);
		DeclareAddress(SetState);
		DeclareAddress(SetShadeColor);
		DeclareAddress(SetArea);
		DeclareAddress(SetLocation);
		DeclareAddress(SetSize);
		DeclareAddress(SetLayoutArea);
		DeclareAddress(SetLayoutLocation);
		DeclareAddress(SetLayoutSize);
		DeclareAddress(func30);
		DeclareAddress(SetCursorID);
		DeclareAddress(SetFlag);
		DeclareAddress(SetCaption);
		DeclareAddress(SetTextFontID);
		DeclareAddress(func34);
		DeclareAddress(func35);
		DeclareAddress(Invalidate);
		DeclareAddress(Revalidate);
		DeclareAddress(InvalidateTransform);
		DeclareAddress(func39);
		DeclareAddress(func40);
		DeclareAddress(GetFillColor);
		DeclareAddress(GetDrawable);
		DeclareAddress(SetFillColor);
		DeclareAddress(SetDrawable);
		DeclareAddress(func45);
		DeclareAddress(func46);
		DeclareAddress(func47);
		DeclareAddress(func48);
		DeclareAddress(func49);
		DeclareAddress(func50);
		DeclareAddress(ContainsPoint);
		DeclareAddress(ToGlobalCoordinates);
		DeclareAddress(ToLocalCoordinates);
		DeclareAddress(ToLocalCoordinates2);
		// DeclareAddress(GetChildrenBegin);
		// DeclareAddress(GetChildrenEnd);
		DeclareAddress(LocateChild);
		DeclareAddress(AddWindow);
		DeclareAddress(RemoveWindow);
		DeclareAddress(DisposeWindowFamily);
		DeclareAddress(DisposeAllWindowFamilies);
		DeclareAddress(BringToFront);
		DeclareAddress(SendToBack);
		DeclareAddress(FindWindowByID);
		DeclareAddress(FindWindowTypeByID);
		DeclareAddress(IsAncestorOf);
		DeclareAddress(func63);
		DeclareAddress(func64);
		DeclareAddress(AddWinProc);
		DeclareAddress(RemoveWinProc);
		DeclareAddress(GetNextWinProc);
		DeclareAddress(func68);
		DeclareAddress(SendMsg);
		DeclareAddress(GetComponentName);

	}
}
