#ifndef MODAPI_DLL_EXPORT
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

#include <Spore\UTFWin\InteractiveWindow.h>
#include <Spore\UTFWin\InteractiveWinProc.h>

namespace UTFWin
{
	InteractiveWinProc::InteractiveWinProc()
		: mnRefCount(0)
	{
	}

	int InteractiveWinProc::AddRef()
	{
		return ++mnRefCount;
	}
	int InteractiveWinProc::Release()
	{
		if (--mnRefCount == 0)
		{
			delete this;
		}
		return mnRefCount;
	}

	void* InteractiveWinProc::Cast(uint32_t typeID) const
	{
		if (typeID == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (typeID == IWinProc::TYPE || typeID == Object::TYPE)
		{
			return (IWinProc*) this;
		}
		else
		{
			return nullptr;
		}
	}

	void InteractiveWinProc::SetSerializer(Serializer& dst)
	{
		dst.pSerialization = &InteractiveWinProc::SerializationData;
		dst.pObject = (IWinProc*) this;
		dst.count = 1;
		dst.proxyID = GetProxyID();
	}
	uint32_t InteractiveWinProc::GetProxyID() const
	{
		return 0;
	}

	const ComponentSerialization InteractiveWinProc::SerializationData = 
		ComponentSerialization(0, 0, sizeof(InteractiveWinProc), nullptr, 0);

	auto_METHOD_VIRTUAL(InteractiveWinProc, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	bool InteractiveWinProc::OnKeyDown2(IWindow* pWindow, int, int virtualKey, int modifiers) { return false; };
	bool InteractiveWinProc::OnKeyUp2(IWindow* pWindow, int, int virtualKey, int modifiers) { return false; };
	bool InteractiveWinProc::OnKeyDown(IWindow* pWindow, int, int virtualKey, int modifiers) { return false; };
	bool InteractiveWinProc::OnKeyUp(IWindow* pWindow, int, int virtualKey, int modifiers) { return false; };
	bool InteractiveWinProc::OnKeyPress(IWindow* pWindow, int, int16_t virtualKey) { return false; };
	bool InteractiveWinProc::OnMouseDown(IWindow* pWindow, float fMouseX, float fMouseY, int, int state) { return false; };
	bool InteractiveWinProc::OnMouseUp(IWindow* pWindow, float fMouseX, float fMouseY, int, int state) { return false; };
	bool InteractiveWinProc::OnMouseMove(IWindow* pWindow, float fMouseX, float fMouseY, int state) { return false; };
	bool InteractiveWinProc::OnMouseWheel(IWindow* pWindow, float fMouseX, float fMouseY, int state, int nWheelDelta) { return false; };
	bool InteractiveWinProc::OnRefresh(IWindow* pWindow, RefreshType type, IWindow*) { return false; };
	bool InteractiveWinProc::func44h(IWindow* pWindow, int arg_4, int arg_8) { return false; };
	bool InteractiveWinProc::OnUpdate(IWindow* pWindow) { return false; };
	bool InteractiveWinProc::OnCollisionDetect(IWindow* pWindow, float fMouseX, float fMouseY, bool* pbResult) { return false; };
	bool InteractiveWinProc::OnElementAdd(IWindow* pWindow) { return false; };
	bool InteractiveWinProc::OnElementRemove(IWindow* pWindow) { return false; };
	void InteractiveWinProc::OnLayout(IWindow* window, Math::Rectangle& parentBounds) {};
	void InteractiveWinProc::OnTransform(IWindow* pWindow, Math::Matrix4* pTransformation) {};
	void InteractiveWinProc::OnWinProcAdd(IWindow* pWindow) {};
	void InteractiveWinProc::OnWinProcRemove(IWindow* pWindow) {};
	bool InteractiveWinProc::OnButtonClick(IWindow* pWindow, IWindow* pSourceWindow, uint32_t commandID) { return false; };
	bool InteractiveWinProc::OnButtonSelect(IWindow* pWindow, IWindow* pSourceWindow, uint32_t commandID, Message& message) { return false; };
	bool InteractiveWinProc::func70h(IWindow* pWindow, int arg_4, int arg_8) { return false; };
	bool InteractiveWinProc::func74h(IWindow* pWindow, int arg_4, int arg_8) { return false; };
	bool InteractiveWinProc::OnMouseEnter(IWindow* pWindow, int, IWindow* pFocusWindow) { return false; };
	bool InteractiveWinProc::OnMouseLeave(IWindow* pWindow, int, IWindow* pLostFocusWindow) { return false; };



	bool InteractiveWindow::OnKeyDown2(int, int virtualKey, int modifiers) { return false; };
	bool InteractiveWindow::OnKeyUp2(int, int virtualKey, int modifiers) { return false; };
	bool InteractiveWindow::OnKeyDown(int, int virtualKey, int modifiers) { return false; };
	bool InteractiveWindow::OnKeyUp(int, int virtualKey, int modifiers) { return false; };
	bool InteractiveWindow::OnKeyPress(int, int16_t virtualKey) { return false; };
	bool InteractiveWindow::OnMouseDown(float fMouseX, float fMouseY, int, int state) { return false; };
	bool InteractiveWindow::OnMouseUp(float fMouseX, float fMouseY, int, int state) { return false; };
	bool InteractiveWindow::OnMouseMove(float fMouseX, float fMouseY, int state) { return false; };
	bool InteractiveWindow::OnMouseWheel(float fMouseX, float fMouseY, int state, int nWheelDelta) { return false; };
	bool InteractiveWindow::OnRefresh(RefreshType type, IWindow*) { return false; };
	bool InteractiveWindow::func50h(int, IWindow*) { return false; };
	bool InteractiveWindow::func54h(int, IWindow*) { return false; };
	void InteractiveWindow::OnUpdate() {};
	void InteractiveWindow::OnElementAdd() {};
	void InteractiveWindow::OnElementRemove() {};
	bool InteractiveWindow::OnCollisionDetect(float fMouseX, float fMouseY, bool* pbResult) { return false; };
	void InteractiveWindow::OnLayout(Math::Rectangle* pArea) {};
	void InteractiveWindow::OnTransform(Math::Matrix4* pTransformation) {};
	bool InteractiveWindow::OnButtonClick(IWindow* pSourceWindow, uint32_t commandID) { return false; };
	bool InteractiveWindow::OnButtonSelect(IWindow* pSourceWindow, uint32_t commandID, Message& msg) { return false; };
	bool InteractiveWindow::func78h(int, int) { return false; };
	bool InteractiveWindow::func7Ch(int, int) { return false; };
	bool InteractiveWindow::OnMouseEnter(int, IWindow* pFocusWindow) { return false; };
	bool InteractiveWindow::OnMouseLeave(int, IWindow* pLostFocusWindow) { return false; };

}
#endif
