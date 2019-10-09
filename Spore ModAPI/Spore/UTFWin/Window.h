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

#include <Spore\FixedPoolAllocator.h>
#include <Spore\MathUtils.h>

#include <EASTL\string.h>
#include <EASTL\list.h>
#include <EASTL\hash_map.h>

using namespace eastl;

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
		virtual int func9() const override;
		virtual WindowFlags GetFlags() const override;
		virtual int GetState() const override;
		virtual Math::Color GetShadeColor() const override;
		virtual const Math::Rectangle& GetArea() const override;
		virtual const Math::Rectangle& GetRealArea() const override;
		virtual const char16_t* GetCaption() const override;
		virtual uint32_t GetTextFontID() const override;
		virtual const wchar_t* func17() const override;
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
		virtual void func30(int) override;
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
		virtual int func47(float, float) override;
		virtual Point func48(float, float) override;
		virtual Point func49(float, float) override;
		virtual bool func50(float, float, Point& dst) override;
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

		typedef list<pair<intrusive_ptr<IWinProc>, int>, FixedPoolAllocatorAdapter> IWinProcList_t;

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
		/* 30h */	bool field_30;
		/* 31h */	int8_t field_31;  // kUseDrawableCollision = 8
		/* 34h */	IWindowManager* mpWindowManager;
		/* 38h */	intrusive_ptr<Window> mpParentWindow;
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
		/* A8h */	int property_EEC1B009;  // EEC1B009
		/* ACh */	int mnStateFlags;
		/* B0h */	string16 mCaption;
		/* C0h */	uint32_t mTextFontID;
		/* C4h */	UnkMatrix4 field_C4;
		/* 108h */	UnkMatrix4 field_108;
		/* 14Ch */	UnkMatrix4 field_14C;
		/* 190h */	UnkMatrix4 field_190;
		/* 1D4h */	int field_1D4;
		/* 1D8h */	Math::Color mShadeColor;
		/* 1DCh */	Math::Color mFillColor;
		/* 1E0h */	intrusive_ptr<IDrawable> mpDrawable;
		/* 1E4h */	intrusive_ptr<Object> field_1E4;
		/* 1E8h */	intrusive_ptr<Object> field_1E8;
		/* 1ECh */	hash_map<int, int> field_1EC;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(Window) == 0x20C, "sizeof(Window) must be 20Ch!");

	namespace Addresses(Window)
	{
		DeclareAddress(SetSerializer, SelectAddress(0x9609E0, 0x960480, 0x960480));
		DeclareAddress(GetProxyID, SelectAddress(0x7F3780, 0x7F31E0, 0x7F3250));
		DeclareAddress(Initialize, SelectAddress(0xA37650, 0xB1FB00, 0xB1FB30));
		DeclareAddress(Dispose, SelectAddress(0x9621D0, 0x961DD0, 0x961DD0));
		DeclareAddress(DoMessage, SelectAddress(0x9608D0, 0x960370, 0x960370));
		DeclareAddress(OnPaint, SelectAddress(0x9607D0, 0x960270, 0x960270));

		DeclareAddress(GetParent, SelectAddress(0x95FE70, 0x95F930, 0x95F930));
		DeclareAddress(GetWindowManager, SelectAddress(0x804E60, 0x5AADB0, 0x5AADB0));
		DeclareAddress(func6, SelectAddress(0x95FE80, 0x1030E20, 0x1030E20));
		DeclareAddress(GetControlID, SelectAddress(0xF3E580, 0xA02C10, 0xA02C70));
		DeclareAddress(GetCommandID, SelectAddress(0x95FE90, 0xC2F7C0, 0xC2F7E0));
		DeclareAddress(func9, SelectAddress(0x95FEA0, 0x575EA0, 0x575EA0));
		DeclareAddress(GetFlags, SelectAddress(0xFCE1D0, 0x641770, 0x641760));
		DeclareAddress(GetState, SelectAddress(0xE464D0, 0x98F870, 0x98F870));
		DeclareAddress(GetShadeColor, SelectAddress(0x95FEB0, 0x95F940, 0x95F940));
		DeclareAddress(GetArea, SelectAddress(0x95FEC0, 0x95F950, 0x95F950));
		DeclareAddress(GetRealArea, SelectAddress(0xBFFB20, 0x95F960, 0x95F960));
		DeclareAddress(GetCaption, SelectAddress(0x8D6580, 0x8D6230, 0x8D6270));
		DeclareAddress(GetTextFontID, SelectAddress(0x95FF10, 0x95F9B0, 0x95F9B0));
		DeclareAddress(func17, SelectAddress(0x95FED0, 0x95F970, 0x95F970));
		DeclareAddress(func18, SelectAddress(0x960210, 0x95FCB0, 0x95FCB0));
		DeclareAddress(func19, SelectAddress(0x960220, 0x6E8850, 0x6E8850));
		DeclareAddress(SetControlID, SelectAddress(0x95FEE0, 0x95F980, 0x95F980));
		DeclareAddress(SetCommandID, SelectAddress(0x95FEF0, 0x95F990, 0x95F990));
		DeclareAddress(SetState, SelectAddress(0x960230, 0x95FCC0, 0x95FCC0));
		DeclareAddress(SetShadeColor, SelectAddress(0x960290, 0x95FD20, 0x95FD20));
		DeclareAddress(SetArea, SelectAddress(0x960310, 0x95FDA0, 0x95FDA0));
		DeclareAddress(SetLocation, SelectAddress(0x960390, 0x95FE20, 0x95FE20));
		DeclareAddress(SetSize, SelectAddress(0x9603F0, 0x95FE80, 0x95FE80));
		DeclareAddress(SetLayoutArea, SelectAddress(0x960D30, 0x960820, 0x960820));
		DeclareAddress(SetLayoutLocation, SelectAddress(0x960440, 0x95FED0, 0x95FED0));
		DeclareAddress(SetLayoutSize, SelectAddress(0x9604A0, 0x95FF30, 0x95FF30));
		DeclareAddress(func30, SelectAddress(0x9604F0, 0x95FF80, 0x95FF80));
		DeclareAddress(SetFlag, SelectAddress(0x961B00, 0x9616B0, 0x9616B0));
		DeclareAddress(SetCaption, SelectAddress(0x962270, 0x961E70, 0x961E70));
		DeclareAddress(SetTextFontID, SelectAddress(0x95FF00, 0x95F9A0, 0x95F9A0));
		DeclareAddress(func34, SelectAddress(0x960520, 0x95FFB0, 0x95FFB0));
		DeclareAddress(func35, SelectAddress(0x9602D0, 0x95FD60, 0x95FD60));
		DeclareAddress(Invalidate, SelectAddress(0x960570, 0x960000, 0x960000));
		DeclareAddress(Revalidate, SelectAddress(0x960E20, 0x960910, 0x960910));
		DeclareAddress(InvalidateTransform, SelectAddress(0x9605A0, 0x960030, 0x960030));
		DeclareAddress(func39, SelectAddress(0x961C00, 0x9617B0, 0x9617B0));
		DeclareAddress(func40, SelectAddress(0x961C80, 0x961830, 0x961830));
		DeclareAddress(GetFillColor, SelectAddress(0xBA5DD0, 0x885D40, 0x885D80));
		DeclareAddress(GetDrawable, SelectAddress(0xBFDB80, 0x960050, 0x960050));
		DeclareAddress(SetFillColor, SelectAddress(0x95FF20, 0x95F9C0, 0x95F9C0));
		DeclareAddress(SetDrawable, SelectAddress(0x961390, 0x960E80, 0x960E80));
		DeclareAddress(func45, SelectAddress(0x961CF0, 0x9618A0, 0x9618A0));
		DeclareAddress(func46, SelectAddress(0x962730, 0x962480, 0x962480));
		DeclareAddress(func47, SelectAddress(0x961450, 0x960F40, 0x960F40));
		DeclareAddress(func48, SelectAddress(0x9605C0, 0x960060, 0x960060));
		DeclareAddress(func49, SelectAddress(0x960640, 0x9600E0, 0x9600E0));
		DeclareAddress(func50, SelectAddress(0x9615C0, 0x9610B0, 0x9610B0));
		// DeclareAddress(GetChildrenBegin, SelectAddress(0x9616D0, 0x9611C0, 0x9611C0));
		// DeclareAddress(GetChildrenEnd, SelectAddress(0x9616E0, 0x9611D0, 0x9611D0));
		DeclareAddress(LocateChild, SelectAddress(0x9606A0, 0x960140, 0x960140));
		DeclareAddress(AddWindow, SelectAddress(0x962A40, 0x962780, 0x962780));
		DeclareAddress(RemoveWindow, SelectAddress(0x962AF0, 0x962830, 0x962830));
		DeclareAddress(DisposeWindowFamily, SelectAddress(0x9606F0, 0x960190, 0x960190));
		DeclareAddress(DisposeAllWindowFamilies, SelectAddress(0x960740, 0x9601E0, 0x9601E0));
		DeclareAddress(BringToFront, SelectAddress(0x9616F0, 0x9611E0, 0x9611E0));
		DeclareAddress(SendToBack, SelectAddress(0x961770, 0x961260, 0x961260));
		DeclareAddress(FindWindowByID, SelectAddress(0x962780, 0x9624D0, 0x9624D0));
		DeclareAddress(FindWindowTypeByID, SelectAddress(0x9627B0, 0x962500, 0x962500));
		DeclareAddress(IsAncestorOf, SelectAddress(0x95FF90, 0x95FA30, 0x95FA30));
		DeclareAddress(func63, SelectAddress(0x95FFE0, 0x95FA80, 0x95FA80));
		DeclareAddress(func64, SelectAddress(0x960020, 0x95FAC0, 0x95FAC0));
		DeclareAddress(AddWinProc, SelectAddress(0x962310, 0x961F10, 0x961F10));
		DeclareAddress(RemoveWinProc, SelectAddress(0x961DD0, 0x961980, 0x961980));
		DeclareAddress(GetNextWinProc, SelectAddress(0x961810, 0x961300, 0x961300));
		DeclareAddress(func68, SelectAddress(0x960780, 0x960220, 0x960220));
		DeclareAddress(SendMsg, SelectAddress(0x9607B0, 0x960250, 0x960250));
		DeclareAddress(GetComponentName, SelectAddress(0x7F3770, 0x7F31D0, 0x7F3240));

	}
}
