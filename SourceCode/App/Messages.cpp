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

#include <Spore\App\IMessageListener.h>
#include <Spore\App\IMessageManager.h>
#include <Spore\App\cMessageManager.h>
#include <Spore\App\StandardMessage.h>

// PLACEHOLDER ONLY FOR TESTNIG REMOVE
#include <Spore\Cheats.h>

namespace App
{
	auto_STATIC_METHOD_(IMessageManager, IMessageManager*, Get);

	auto_METHOD_VIRTUAL_(cMessageManager, IMessageManager, bool, Initialize);
	auto_METHOD_VIRTUAL_(cMessageManager, IMessageManager, bool, Dispose);
	auto_METHOD_VIRTUAL(cMessageManager, IMessageManager, bool, GetOption, Args(Options option), Args(option));
	auto_METHOD_VIRTUAL_VOID(cMessageManager, IMessageManager, SetOption, Args(Options option, bool bValue), Args(option, bValue));
	auto_METHOD_VIRTUAL_VOID(cMessageManager, IMessageManager, PostMSG, Args(uint32_t messageID, void* pMessage, IMessageListener* pListener), Args(messageID, pMessage, pListener));
	auto_METHOD_VIRTUAL_VOID(cMessageManager, IMessageManager, func18h, Args(int arg_0, int arg_4, int arg_8), Args(arg_0, arg_4, arg_8));
	auto_METHOD_VIRTUAL_VOID(cMessageManager, IMessageManager, func1Ch, Args(int arg_0, int arg_4, int arg_8, int arg_c, int arg_10), Args(arg_0, arg_4, arg_8, arg_c, arg_10));
	auto_METHOD_VIRTUAL_VOID(cMessageManager, IMessageManager, AddListener, Args(IMessageListener* pListener, uint32_t messageID), Args(pListener, messageID));
	auto_METHOD_VIRTUAL_VOID(cMessageManager, IMessageManager, AddUnmanagedListener, Args(IUnmanagedMessageListener* pListener, uint32_t messageID), Args(pListener, messageID));
	auto_METHOD_VIRTUAL_VOID(cMessageManager, IMessageManager, AddHandler, Args(MessageHandler_t pFunction, void* pObject, uint32_t messageID, bool bRefCounted, int nPriority), Args(pFunction, pObject, messageID, bRefCounted, nPriority));
	auto_METHOD_VIRTUAL(cMessageManager, IMessageManager, bool, RemoveListener, Args(IMessageListener* pListener, uint32_t messageID, int nPriority), Args(pListener, messageID, nPriority));
	auto_METHOD_VIRTUAL(cMessageManager, IMessageManager, bool, RemoveHandler, Args(MessageHandler_t pFunction, uint32_t messageID, int nPriority), Args(pFunction, messageID, nPriority));
	auto_METHOD_VIRTUAL(cMessageManager, IMessageManager, int, func34h, Args(int arg_0, int arg_4, int arg_8), Args(arg_0, arg_4, arg_8));
	auto_METHOD_VIRTUAL_(cMessageManager, IMessageManager, int, func38h);
	auto_METHOD_VIRTUAL_(cMessageManager, IMessageManager, int, func3Ch);
	auto_METHOD_VIRTUAL(cMessageManager, IMessageManager, int, UseMutex, Args(bool bLock), Args(bLock));
	auto_METHOD_VIRTUAL_VOID(cMessageManager, IMessageManager, AddEntry, Args(const Entry& entry, uint32_t messageID), Args(entry, messageID));
	auto_METHOD_VIRTUAL(cMessageManager, IMessageManager, bool, RemoveEntry, Args(void* pMessageObject, uint32_t messageID, int nPriority), Args(pMessageObject, messageID, nPriority));

	DefaultMessageListener::DefaultMessageListener() : mnRefCount(0)
	{
	}
	int DefaultMessageListener::AddRef()
	{
		mnRefCount++;
		return mnRefCount;
	}
	int DefaultMessageListener::Release()
	{
		mnRefCount--;
		if (mnRefCount == 0) delete this;
		return mnRefCount;
	}


	StandardMessage::StandardMessage()
		: id(0)
		, objectFlags(0)
	{
	}

	StandardMessage::~StandardMessage()
	{
		for (size_t i = 0; i < 32; i++)
		{
			if (objectFlags & (1 << i))
			{
				if (params[i].object) params[i].object->Release();
			}
		}
	}


	LambdaMessageListener::LambdaMessageListener(HandleMessage_T function)
		: mnRefCount(0)
		, mFunction(function)
	{
	}
	int LambdaMessageListener::AddRef()
	{
		mnRefCount++;
		return mnRefCount;
	}
	int LambdaMessageListener::Release()
	{
		mnRefCount--;
		if (mnRefCount == 0) delete this;
		return mnRefCount;
	}

	bool LambdaMessageListener::HandleMessage(uint32_t messageID, void* pMessage)
	{
		return mFunction(messageID, pMessage);
	}

	UpdateMessageListener::UpdateMessageListener(VoidFunction_T function)
		: DefaultMessageListener()
		, mFunction(function)
		, mpUpdatable(nullptr)
	{
	}

	UpdateMessageListener::UpdateMessageListener(IUpdatable* updatable)
		: DefaultMessageListener()
		, mFunction()
		, mpUpdatable(updatable)
	{
	}

	bool UpdateMessageListener::HandleMessage(uint32_t messageID, void* pMessage)
	{
		if (mpUpdatable) mpUpdatable->Update();
		else mFunction();
		return false;
	}


	ScheduledTaskListener::ScheduledTaskListener(VoidFunction_T function, float scheduleTime, float repeatRate)
		: DefaultMessageListener()
		, mClock(Clock::Mode::Seconds)
		, mFunction(function)
		, mScheduleTime(scheduleTime)
		, mRepeatRate(repeatRate)
		, mbFirstTime(true)
	{
	}

	bool ScheduledTaskListener::HandleMessage(uint32_t messageID, void* pMessage)
	{
		if (mbFirstTime) {
			if (mClock.GetElapsed() >= mScheduleTime) {
				mFunction();
				mbFirstTime = false;
				if (mRepeatRate == 0) {
					MessageManager()->RemoveListener(this, kMsgAppUpdate);
				}
				else {
					mClock.Stop();
					mClock.Start();
				}
			}
		} else {
			if (mClock.GetElapsed() >= mRepeatRate) {
				mFunction();
				mClock.Stop();
				mClock.Start();
			}
		}
		return false;
	}
}

namespace Simulator
{
	ScheduledTaskListener::ScheduledTaskListener(App::VoidFunction_T function, float scheduleTime, float repeatRate)
		: DefaultMessageListener()
		, mClock()
		, mFunction(function)
		, mScheduleTime(scheduleTime)
		, mRepeatRate(repeatRate)
		, mbFirstTime(true)
	{
	}

	bool ScheduledTaskListener::HandleMessage(uint32_t messageID, void* pMessage)
	{
		//mClock.UpdateTime();
		if (mbFirstTime) {
			if ((mClock.GetElapsed().QuadPart / 1000.0f) >= mScheduleTime) {
				mFunction();
				mbFirstTime = false;
				if (mRepeatRate == 0) {
					App::MessageManager()->RemoveListener(this, App::kMsgAppUpdate);
				}
				else {
					mClock.Stop();
					mClock.Start();
				}
			}
		}
		else {
			if ((mClock.GetElapsed().QuadPart / 1000.0f) >= mRepeatRate) {
				mFunction();
				mClock.Stop();
				mClock.Start();
			}
		}
		return false;
	}
}