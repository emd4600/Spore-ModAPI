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

#include <Spore\UTFWin\Message.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\IWinProc.h>

namespace ModAPI
{
	enum UIEventContext
	{
		// The object parameter is of type Editors::EditorUI
		EditorUI,
		// The object parameter is of type GalaxyGameEntry::GlobalGGEUI
		GlobalGGEUI
	};

	class UIEventListener
	{
	public:

		virtual ~UIEventListener()
		{
		}

		virtual bool HandleEvent(UTFWin::IWindow* pWindow, const UTFWin::Message& message, UTFWin::IWinProc* pObject) = 0;
		virtual void Init(void* object) = 0;
	};

}
