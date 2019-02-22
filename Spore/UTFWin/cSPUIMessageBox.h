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

#include <Spore\Internal.h>
#include <Spore\ResourceKey.h>
#include <Spore\ICoreAllocator.h>

namespace UTFWin
{
	class IWindow;

	class MessageBoxCallback
	{
	public:
		virtual void func00h(int) {};

		virtual void OnButtonPress(IWindow* pWindow, uint32_t buttonID) = 0;

		virtual ~MessageBoxCallback() {};
	};

	class cSPUIMessageBox
	{
	public:
		enum
		{
			kButtonOK = 0xfffffff1,
			kButton1 = 0x05107b17,
			kButton2 = 0x05107b18,
			kButton3 = 0x05107b19,
			kButton4 = 0x05107b1A,
		};

		static bool ShowDialog(MessageBoxCallback* pCallback, const ResourceKey& name);

	private: 
		cSPUIMessageBox() {};
	};

	namespace InternalAddressList(cSPUIMessageBox)
	{
		DefineAddress(ShowDialog, GetAddress(0x80A3B0, 0x809DD0, 0x809E60));
	}
}