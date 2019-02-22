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

#include <Spore\Mutex.h>

#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\Message.h>

namespace UTFWin
{
	class IWindowManager
	{
	public:
		/* 00h */	virtual void func0();

		/// Returns the main window that displays the whole game and contains everything else.
		/* 04h */	virtual IWindow* GetMainWindow();

		//TODO
		/* 08h */	virtual void func2();
		/* 0Ch */	virtual void func3();
		/* 10h */	virtual void SendMsg(IWindow* pSource, IWindow* pDest, const Message& msg, bool inheritable);
		/* 14h */	virtual void func5();
		/* 18h */	virtual void func6(IWindow*, IWindow*, Message&);
		/* 1Ch */	virtual void func7();
		/* 20h */	virtual void func8();
		/* 24h */	virtual void func9();
		/* 28h */	virtual void func10();
		/* 2Ch */	virtual void func11(const Math::Rectangle& area);  // generates Graphics2D, maybe renders UI?
		/* 00h */	virtual void func12();
		/* 00h */	virtual void func13();
		/* 00h */	virtual void func14();
		/* 00h */	virtual void func15();
		/* 00h */	virtual void func16();
		/* 00h */	virtual void func17();

		/* 48h */	virtual IWindow* GetMainWindowIndex(int index);

		static IWindowManager* Get();


	protected:
		// /* 04h */	IWindow* mpMainWindow;
	};

	///
	/// Returns the active window manager. Same as IWindowManager::Get().
	///
	inline IWindowManager* WindowManager()
	{
		return IWindowManager::Get();
	}

	// static_assert(sizeof(WindowManager) == 0x838, "sizeof(WindowManager) != 838h");

	namespace InternalAddressList(IWindowManager)
	{
		DefineAddress(Get, GetAddress(0x67CBF0, 0x67CA60, 0x67CA60));
	}
}