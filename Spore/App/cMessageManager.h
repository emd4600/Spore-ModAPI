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

#include <Spore\App\IMessageManager.h>
#include <Spore\Mutex.h>

#include <EASTL\hash_map.h>
#include <EASTL\list.h>

using namespace eastl;

namespace App
{
	///
	/// The implementation of IMessageManager; this should only be used for extending and detouring.
	///
	class cMessageManager : public IMessageManager
	{
	public:
		virtual bool Initialize() override;
		virtual bool Dispose() override;
		virtual bool GetOption(Options option) override;
		virtual void SetOption(Options option, bool bValue) override;
		virtual void PostMSG(uint32_t messageID, void* pMessage, IMessageListener* pListener) override;
		virtual void func18h(int, int, int) override;
		virtual void func1Ch(int, int, int, int, int) override;
		virtual void AddListener(IMessageListener* pListener, uint32_t messageID) override;
		virtual void AddUnmanagedListener(IUnmanagedMessageListener* pListener, uint32_t messageID) override;
		virtual void AddHandler(MessageHandler_t pFunction, void* pObject, uint32_t messageID, bool bRefCounted, int nPriority) override;
		virtual bool RemoveListener(IMessageListener* pListener, uint32_t messageID, int nPriority) override;
		virtual bool RemoveHandler(MessageHandler_t pFunction, uint32_t messageID, int nPriority) override;
		virtual int func34h(int, int, int) override;
		virtual int func38h() override;
		virtual int func3Ch() override;
		virtual int UseMutex(bool bLock) override;
		virtual void AddEntry(const Entry& entry, uint32_t messageID) override;
		virtual bool RemoveEntry(void* pMessageObject, uint32_t messageID, int nPriority) override;

	protected:
		/* 04h */	char field_04[0x34];
		/* 38h */	Mutex field_38;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;
		/* 70h */	hash_map<uint32_t, list<IMessageListener*>> mListeners;
		/* 90h */	Mutex mListenersMutex;
		/* C0h */	bool field_C0[6];
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cMessageManager) == 0xC8, "sizeof(cMessageManager) != C8h");

	namespace InternalAddressList(cMessageManager)
	{
		DefineAddress(Initialize, GetAddress(0xA37650, 0xB1FB00, 0xB1FB30));
		DefineAddress(Dispose, GetAddress(0x885780, 0x884B90, 0x884BD0));
		DefineAddress(GetOption, GetAddress(0x884370, 0x883930, 0x883970));
		DefineAddress(SetOption, GetAddress(0x884400, 0x8839C0, 0x883A00));
		DefineAddress(PostMSG, GetAddress(0x885F10, 0x885460, 0x8854A0));
		DefineAddress(func18h, GetAddress(0x8863F0, 0x885940, 0x885980));
		DefineAddress(func1Ch, GetAddress(0x886490, 0x8859E0, 0x885A20));
		DefineAddress(AddListener, GetAddress(0x8844D0, 0x883A90, 0x883AD0));
		DefineAddress(AddUnmanagedListener, GetAddress(0x884490, 0x883A50, 0x883A90));
		DefineAddress(AddHandler, GetAddress(0x884520, 0x883AE0, 0x883B20));
		DefineAddress(RemoveListener, GetAddress(0x884590, 0x883B50, 0x883B90));
		DefineAddress(RemoveHandler, GetAddress(0x884590, 0x883B50, 0x883B90));
		DefineAddress(func34h, GetAddress(0x884C30, 0x8841B0, 0x8841F0));
		DefineAddress(func38h, GetAddress(0x8853A0, 0x8847B0, 0x8847F0));
		DefineAddress(func3Ch, GetAddress(0x98F7F0, 0x98F4D0, 0x98F4D0));
		DefineAddress(UseMutex, GetAddress(0x8845A0, 0x883B60, 0x883BA0));
		DefineAddress(AddEntry, GetAddress(0x885920, 0x884D30, 0x884D70));
		DefineAddress(RemoveEntry, GetAddress(0x885270, 0x884680, 0x8846C0));

	}
}