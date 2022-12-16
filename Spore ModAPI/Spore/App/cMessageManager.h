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

namespace App
{
	///
	/// The implementation of IMessageManager; this should only be used for extending and detouring.
	///
	class cMessageManager 
		: public IMessageManager
	{
	public:
		virtual bool Initialize() override;
		virtual bool Dispose() override;
		virtual bool GetOption(Options option) override;
		virtual void SetOption(Options option, bool bValue) override;
		virtual void MessageSend(uint32_t messageID, void* pMessage, IUnmanagedMessageListener* pListener) override;
		virtual void MessagePost(uint32_t messageID, IMessageRC* pMessage, IMessageListener* pListener) override;
		virtual void MessagePostFunction(uint32_t messageID, IMessageRC* pMessage, int, MessageHandler_t handler, void*) override;
		virtual void AddListener(IMessageListener* pListener, uint32_t messageID) override;
		virtual void AddUnmanagedListener(IUnmanagedMessageListener* pListener, uint32_t messageID) override;
		virtual void AddHandler(IMessageManager::MessageHandler_t pFunction, void* pObject, uint32_t messageID, bool bRefCounted, int nPriority) override;
		virtual bool RemoveListener(IUnmanagedMessageListener* pListener, uint32_t messageID, int nPriority) override;
		virtual bool RemoveHandler(IMessageManager::MessageHandler_t pFunction, uint32_t messageID, int nPriority) override;
		virtual int ProcessQueue(int, int, int) override;
		virtual int ProcessQueue2() override;
		virtual int GetMessageQueue() override;
		virtual int Lock(bool bLock) override;
		virtual void AddEntry(const IMessageManager::Entry& entry, uint32_t messageID) override;
		virtual bool RemoveEntry(void* pMessageObject, uint32_t messageID, int nPriority) override;

	public:
		/* 04h */	char field_04[0x34];
		/* 38h */	Mutex field_38;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;
		/* 70h */	eastl::hash_map<uint32_t, eastl::list<IMessageListener*>> mListeners;
		/* 90h */	Mutex mListenersMutex;
		/* C0h */	bool field_C0[6];
	};
	ASSERT_SIZE(cMessageManager, 0xC8);

	namespace Addresses(cMessageManager)
	{
		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		DeclareAddress(GetOption);
		DeclareAddress(SetOption);
		DeclareAddress(PostMSG);
		DeclareAddress(func18h);
		DeclareAddress(func1Ch);
		DeclareAddress(AddListener);
		DeclareAddress(AddUnmanagedListener);
		DeclareAddress(AddHandler);
		DeclareAddress(RemoveListener);
		DeclareAddress(RemoveHandler);
		DeclareAddress(func34h);
		DeclareAddress(func38h);
		DeclareAddress(func3Ch);
		DeclareAddress(UseMutex);
		DeclareAddress(AddEntry);
		DeclareAddress(RemoveEntry);

		DeclareAddress(MessageSend);
		DeclareAddress(MessagePost);
		DeclareAddress(MessagePostFunction);
		DeclareAddress(ProcessQueue);
		DeclareAddress(ProcessQueue2);
		DeclareAddress(GetMessageQueue);
		DeclareAddress(Lock);
	}
}