/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\UTFWin\Window.h>
#include <Spore\UTFWin\IWindowManager.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\Constants.h>
#include <Spore\UTFWin\WindowIterators.h>
#include <EASTL\internal\thread_support.h>

#include <Spore\UTFWin\cSPUIMessageBox.h>

namespace UTFWin
{

	Window::UnkMatrix4::UnkMatrix4() : field_40(0)
	{
		SetIdentity();

	}

	Window::Window()
		: field_10()
		, field_14()
		, field_18()
		, field_1C()
		, field_20()
		, field_24()
		, mnRefCount()
		, mnFlags(kWinFlagVisible | kWinFlagEnabled)
		, field_30(false)
		, field_31()
		, mpWindowManager(nullptr)
		, mpParentWindow(nullptr)
		, mChildrenWindows()
		, mPoolAllocator(UTFWin::GetAllocator(), 0x10, sizeof(IWinProcList_t::node_type))
		, mWinProcs(FixedPoolAllocatorAdapter(nullptr, &mPoolAllocator))
		, field_74()
		, field_78()
		, field_7C()
		, mControlID()
		, mCommandID()
		, mRealArea()
		, mArea()
		, property_EEC1B009()
		, mnStateFlags()
		, mCaption()
		, mTextFontID(1)
		, field_C4()
		, field_108()
		, field_14C()
		, field_190()
		, field_1D4()
		, mShadeColor(0xFFFFFFFF)
		, mFillColor(0)
		, mpDrawable(nullptr)
		, field_1E4(nullptr)
		, field_1E8(nullptr)
		, field_1EC()
	{
		field_C4.SetIdentity();
		field_108.SetIdentity();
		field_14C.SetIdentity();
		field_190.SetIdentity();
	}

	Window::~Window()
	{
		Dispose();
	}

	int Window::AddRef()
	{
		return eastl::Internal::atomic_increment(&mnRefCount);
	}
	int Window::Release()
	{
		if (eastl::Internal::atomic_decrement(&mnRefCount) == 0)
		{
			delete this;
		}
		return mnRefCount;
	}
	void* Window::Cast(uint32_t type) const
	{
		if (type == Object::TYPE || type == IWindow::TYPE)
		{
			return (IWindow*) this;
		}
		else if (type == Window::TYPE)
		{
			return (Window*) this;
		}
		else
		{
			return nullptr;
		}
	}

	auto_METHOD_VIRTUAL_VOID(Window, Window, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(Window, Window, uint32_t, GetProxyID);
	auto_METHOD_VIRTUAL_(Window, Window, bool, Initialize);
	auto_METHOD_VIRTUAL_(Window, Window, bool, Dispose);
	auto_METHOD_VIRTUAL(Window, Window, bool, DoMessage, PARAMS(const UTFWin::Message& msg), PARAMS(msg));
	auto_METHOD_VIRTUAL(Window, Window, bool, OnPaint, PARAMS(UIRenderer* pRenderer), PARAMS(pRenderer));

	auto_METHOD_VIRTUAL_const_(Window, IWindow, IWindow*, GetParent);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, IWindowManager*, GetWindowManager);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, int, func6);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, uint32_t, GetControlID);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, uint32_t, GetCommandID);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, int, func9);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, WindowFlags, GetFlags);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, int, GetState);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, Math::Color, GetShadeColor);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, const Math::Rectangle&, GetArea);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, const Math::Rectangle&, GetRealArea);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, const char16_t*, GetCaption);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, uint32_t, GetTextFontID);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, const wchar_t*, func17);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, int, func18);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, int, func19);
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetControlID, PARAMS(uint32_t controlID), PARAMS(controlID));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetCommandID, PARAMS(uint32_t commandID), PARAMS(commandID));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetState, PARAMS(int state), PARAMS(state));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetShadeColor, PARAMS(Color color), PARAMS(color));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetArea, PARAMS(const Math::Rectangle& area), PARAMS(area));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetLocation, PARAMS(float fX, float fY), PARAMS(fX, fY));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetSize, PARAMS(float fWidth, float fHeight), PARAMS(fWidth, fHeight));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetLayoutArea, PARAMS(const Math::Rectangle& layoutArea), PARAMS(layoutArea));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetLayoutLocation, PARAMS(float fX, float fY), PARAMS(fX, fY));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetLayoutSize, PARAMS(float fWidth, float fHeight), PARAMS(fWidth, fHeight));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, func30, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetFlag, PARAMS(WindowFlags nFlag, bool bValue), PARAMS(nFlag, bValue));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetCaption, PARAMS(const char16_t* pCaption), PARAMS(pCaption));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetTextFontID, PARAMS(uint32_t styleID), PARAMS(styleID));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, func34, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, func35, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL_(Window, IWindow, int, Invalidate);
	auto_METHOD_VIRTUAL_VOID_(Window, IWindow, Revalidate);
	auto_METHOD_VIRTUAL_(Window, IWindow, int, InvalidateTransform);
	auto_METHOD_VIRTUAL_(Window, IWindow, int, func39);
	auto_METHOD_VIRTUAL_(Window, IWindow, int, func40);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, Color, GetFillColor);
	auto_METHOD_VIRTUAL_const_(Window, IWindow, IDrawable*, GetDrawable);
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetFillColor, PARAMS(Color color), PARAMS(color));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SetDrawable, PARAMS(IDrawable* drawable), PARAMS(drawable));
	auto_METHOD_VIRTUAL(Window, IWindow, int, func45, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL(Window, IWindow, int, func46, PARAMS(int arg_0, int arg_4), PARAMS(arg_0, arg_4));
	auto_METHOD_VIRTUAL(Window, IWindow, int, func47, PARAMS(float arg_0, float arg_4), PARAMS(arg_0, arg_4));

	Point Window::func48(float arg_0, float arg_4) {
		Point p;
		CALL(GetMethodAddress(Window, func48), Point*, PARAMS(IWindow*, Point*, float, float), PARAMS(this, &p, arg_0, arg_4));
		return p;
	}
	Point Window::func49(float arg_0, float arg_4) {
		Point p;
		CALL(GetMethodAddress(Window, func49), Point*, PARAMS(IWindow*, Point*, float, float), PARAMS(this, &p, arg_0, arg_4));
		return p;
	}
	auto_METHOD_VIRTUAL(Window, IWindow, bool, func50, PARAMS(float arg_0, float arg_4, Point& dst), PARAMS(arg_0, arg_4, dst));

	// Specials
	IWindowList_t::iterator Window::GetChildrenBegin() {
		return mChildrenWindows.begin();
	}

	IWindowList_t::iterator Window::GetChildrenEnd() {
		return mChildrenWindows.end();
	}


	auto_METHOD_VIRTUAL_const(Window, IWindow, IWindowList_t::iterator, LocateChild, PARAMS(const IWindow* pChild), PARAMS(pChild));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, AddWindow, PARAMS(IWindow* pWindow), PARAMS(pWindow));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, RemoveWindow, PARAMS(IWindow* pWindow), PARAMS(pWindow));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, DisposeWindowFamily, PARAMS(IWindow* pChildWindow), PARAMS(pChildWindow));
	auto_METHOD_VIRTUAL_VOID_(Window, IWindow, DisposeAllWindowFamilies);
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, BringToFront, PARAMS(IWindow* pWindow), PARAMS(pWindow));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, SendToBack, PARAMS(IWindow* pWindow), PARAMS(pWindow));
	auto_METHOD_VIRTUAL(Window, IWindow, IWindow*, FindWindowByID, PARAMS(uint32_t controlID, bool bRecursive), PARAMS(controlID, bRecursive));
	auto_METHOD_VIRTUAL(Window, IWindow, IWindow*, FindWindowTypeByID, PARAMS(uint32_t controlID, uint32_t type, bool bRecursive), PARAMS(controlID, type, bRecursive));
	auto_METHOD_VIRTUAL(Window, IWindow, bool, IsAncestorOf, PARAMS(const IWindow* pChildWindow), PARAMS(pChildWindow));
	auto_METHOD_VIRTUAL(Window, IWindow, bool, func63, PARAMS(int index), PARAMS(index));
	auto_METHOD_VIRTUAL(Window, IWindow, bool, func64, PARAMS(int index), PARAMS(index));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, AddWinProc, PARAMS(IWinProc* pWinProc), PARAMS(pWinProc));
	auto_METHOD_VIRTUAL_VOID(Window, IWindow, RemoveWinProc, PARAMS(IWinProc* pWinProc), PARAMS(pWinProc));
	auto_METHOD_VIRTUAL_const(Window, IWindow, IWinProc*, GetNextWinProc, PARAMS(const IWinProc* pWinProc), PARAMS(pWinProc));
	auto_METHOD_VIRTUAL(Window, IWindow, int, func68, PARAMS(int arg_0), PARAMS(arg_0));
	auto_METHOD_VIRTUAL(Window, IWindow, bool, SendMsg, PARAMS(Message& msg), PARAMS(msg));
	auto_METHOD_VIRTUAL_const_(Window, IWindow, const char*, GetComponentName);

	//// cSPUIMessageBox ////

	auto_STATIC_METHOD(cSPUIMessageBox, bool, ShowDialog, PARAMS(MessageBoxCallback* pCallback, const ResourceKey& name), PARAMS(pCallback, name));


	void IWindow::FitParentArea(IWindow* pWindow)
	{
		if (pWindow)
		{
			IWindow* pParent = pWindow->GetParent();
			if (pParent)
			{
				const Math::Rectangle& parentArea = pParent->GetRealArea();

				pWindow->SetLayoutArea(Math::Rectangle(0, 0, parentArea.GetWidth(), parentArea.GetHeight()));
			}
		}
	}

	IWindow* IWindow::CreatePanel(IWindow* pParent)
	{
		IWindow* pWindow = new Window();

		pWindow->SetCommandID(0);
		pWindow->SetControlID(0);
		pWindow->SetArea(Math::Rectangle(0, 0, 100.0f, 100.0f));
		pWindow->SetShadeColor(0xFFFFFFFF);
		pWindow->SetFillColor(0x00FFFFFF);
		pWindow->SetFlag(kWinFlagVisible, true);
		pWindow->SetFlag(kWinFlagEnabled, true);
		pWindow->SetFlag(kWinFlagIgnoreMouse, false);

		if (pParent)
		{
			const Math::Rectangle& area = pParent->GetArea();

			pWindow->SetArea(Math::Rectangle(0, 0, area.GetWidth(), area.GetHeight()));
			pParent->AddWindow(pWindow);
		}

		return pWindow;
	}

	void IWindow::SetOpacity(IWindow* pWindow, float fOpacity)
	{
		if (pWindow)
		{
			Math::Color shadeColor = pWindow->GetShadeColor();
			shadeColor.a = (int) round(fOpacity * 255);
			pWindow->SetShadeColor(shadeColor);
		}
	}


	/// -- LAMBDA PROCEDURE -- //

	LambdaProc::LambdaProc(HandleUILambda_t pFunction) 
		: LambdaProc(pFunction, kEventFlagBasicInput | kEventFlagAdvanced, 0)
	{
	}
	LambdaProc::LambdaProc(HandleUILambda_t pFunction, int eventFlags)
		: LambdaProc(pFunction, eventFlags, 0)
	{
	}
	LambdaProc::LambdaProc(HandleUILambda_t pFunction, int eventFlags, int priority)
		: mpFunction(pFunction)
		, mEventFlags(eventFlags)
		, mPriority(priority)
		, mnRefCount(0)
	{
	}

	int LambdaProc::AddRef()
	{
		mnRefCount++;
		return mnRefCount;
	}
	int LambdaProc::Release()
	{
		mnRefCount--;
		if (mnRefCount == 0) delete this;
		return mnRefCount;
	}
	void* LambdaProc::Cast(uint32_t typeID) const
	{
		if (typeID == IWinProc::TYPE)
		{
			return (IWinProc*)this;
		}
		else if (typeID == Object::TYPE)
		{
			return (Object*)this;
		} 
		else
		{
			return nullptr;
		}
	}

	int LambdaProc::GetPriority() const
	{
		return mPriority;
	}
	int LambdaProc::GetEventFlags() const
	{
		return mEventFlags;
	}
	bool LambdaProc::HandleUIMessage(IWindow* pWindow, const Message& message)
	{
		return mpFunction(pWindow, message);
	}

	/// WINDOW USEFUL METHODS ///

	WindowChildren IWindow::children()
	{
		return WindowChildren(this);
	}

	WindowProcedures IWindow::procedures()
	{
		return WindowProcedures(this);
	}

	intrusive_ptr<IWinProc> IWindow::AddWinProc(HandleUILambda_t pFunction, int eventFlags, int priority)
	{
		intrusive_ptr<IWinProc> ptr = new LambdaProc(pFunction, eventFlags, priority);
		AddWinProc(ptr.get());
		return ptr;
	}

	EventFlags GetEventFlags(MessageType type)
	{
		if ((type >= 0x01 && type <= 0x09) || (type >= 0x17 && type <= 0x1A))
		{
			return kEventFlagBasicInput;
		}
		else if ((uint32_t)type > 0x1C)
		{
			return kEventFlagAdvanced;
		}

		switch (type)
		{
		case kMsgUpdate:
			return kEventFlagUpdate;
		case kMsgPaint:
			return kEventFlagPaint;
		case kMsgWindowChanged:
		case 0x0F:
			return kEventWindowChanged;
		case kMsgStateChanged:
			return kEventStateChanged;
		case kMsgRefresh:
		case kMsgMouseEnter:
		case kMsgMouseLeave:
			return kEventRefresh;
		case kMsgLayout:
			return kEventFlagLayout;
		case kMsgElementAdded:
		case kMsgElementRemoved:
			return kEventFlagElement;
		default:
			return (EventFlags)0;
		}
	}


	intrusive_ptr<IWinProc> IWindow::AddWinProcFilter(HandleUILambda_t pFunction, const vector<MessageType> types, int priority)
	{
		// Get the event flags
		int flags = 0;

		for (MessageType type : types)
		{
			flags |= GetEventFlags(type);
		}

		intrusive_ptr<IWinProc> ptr = new LambdaFilterProc(pFunction, flags, priority, types);
		AddWinProc(ptr.get());
		return ptr;
	}

	LambdaFilterProc::LambdaFilterProc(HandleUILambda_t pFunction, int eventFlags, int priority, const vector<MessageType>& types)
		: LambdaProc(pFunction, eventFlags, priority)
	{
		for (MessageType type : types)
		{
			mTypes.push_back(type);
		}
	}

	bool LambdaFilterProc::HandleUIMessage(IWindow* pWindow, const Message& message)
	{
		for (MessageType type : mTypes)
		{
			if (message.IsType(type))
			{
				return mpFunction(pWindow, message);
			}
		}
		return false;
	}
}
