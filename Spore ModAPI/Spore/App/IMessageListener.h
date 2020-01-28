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

#include <cstdint>
#include <Spore\Object.h>
#include <Spore\Clock.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <EASTL\functional.h>

#define IMessageListenerPtr intrusive_ptr<App::IMessageListener>

namespace App
{
	///
	/// An interface that can receive messages sent through the app. 
	/// Using the App::IMessageManager, listeners sign up to receive certain message IDs.
	///
	class IMessageListener
	{
	public:

		virtual ~IMessageListener() {};

		///
		/// Called every time a message is received. Only the messages with an ID this listened
		/// signed up for will call this event.
		/// @param messageID The ID of the message received.
		/// @param msg The data of the message received, it might be nullptr.
		/// @returns Whether the message was handled or not.
		///
		virtual bool HandleMessage(uint32_t messageID, void* msg) = 0;

		virtual int AddRef() = 0;
		virtual int Release() = 0;
	};

	///
	/// Same as App::IMessageListener, but this one does not use ref-counting.
	///
	class IUnmanagedMessageListener
	{
	public:

		virtual ~IUnmanagedMessageListener() {};

		///
		/// Called every time a message is received. Only the messages with an ID this listened
		/// signed up for will call this event.
		/// @param messageID The ID of the message received.
		/// @param msg The data of the message received, it might be nullptr.
		/// @returns Whether the message was handled or not.
		///
		virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
	};

	///
	/// A class that inherits from App::IMessageListener and defines an implementation for the AddRef() and Release() metods.
	/// If you inherit from this class, you only have to provide an implementation for the HandleMessage() method.
	///
	class DefaultMessageListener : public IMessageListener
	{
	public:
		DefaultMessageListener();

		virtual int AddRef() override;
		virtual int Release() override;

	protected:
		int mnRefCount;
	};

	///
	/// An implementation of IMessageListener using lambda functions.
	///
	class LambdaMessageListener
		: public IMessageListener
	{
	public:
		typedef eastl::function<bool(uint32_t, void*)> HandleMessage_T;

		LambdaMessageListener(HandleMessage_T function);

		virtual ~LambdaMessageListener() {};
		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

		virtual int AddRef() override;
		virtual int Release() override;

	protected:
		int mnRefCount;
		HandleMessage_T mFunction;
	};

	/// The type of function used in Update or schedule scripts.
	typedef eastl::function<void()> VoidFunction_T;
	/// The type of member method used in Update or schedule scripts.
	template <class T>
	using VoidMethod_T = void(T::*)();

	class IUpdatable
	{
	public:
		virtual int AddRef() = 0;
		virtual int Release() = 0;
		virtual void Update() = 0;
	};

	/// A message listener used for Update script methods. Mostly of internal use, 
	/// average developer does not need this class.
	class UpdateMessageListener : public DefaultMessageListener
	{
	public:
		UpdateMessageListener(VoidFunction_T function);
		UpdateMessageListener(IUpdatable* updatable);

		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

	protected:
		VoidFunction_T mFunction;
		intrusive_ptr<IUpdatable> mpUpdatable;
	};

	/// A message listener that, listening to Update messages, executes the given task after a certain
	/// time has passed and (optionally) repetaing it periodically. Mostly of internal use, 
	/// average developer does not need this class.
	class ScheduledTaskListener : public DefaultMessageListener
	{
	public:
		ScheduledTaskListener(VoidFunction_T function, float scheduleTime, float repeatRate = 0.0f);

		inline void StartClock() {
			mClock.Start();
		}

		/// Returns true if the task has already been executed.
		inline bool HasExecuted() {
			return mbHasExecuted;
		}

		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

	protected:
		Clock mClock;
		VoidFunction_T mFunction;
		float mScheduleTime;
		float mRepeatRate;
		float mbFirstTime;
		bool mbHasExecuted;
	};
}

namespace Simulator
{
	/// A message listener that, listening to Update messages, executes the given task after a certain
	/// time has passed and (optionally) repetaing it periodically. Mostly of internal use, 
	/// average developer does not need this class.
	class ScheduledTaskListener : public App::DefaultMessageListener
	{
	public:
		ScheduledTaskListener(App::VoidFunction_T function, float scheduleTime, float repeatRate = 0.0f);

		inline void StartClock() {
			mClock.Start();
		}

		/// Returns true if the task has already been executed.
		inline bool HasExecuted() {
			return mbHasExecuted;
		}

		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

	protected:
		cGonzagoTimer mClock;
		App::VoidFunction_T mFunction;
		float mScheduleTime;
		float mRepeatRate;
		float mbFirstTime;
		bool mbHasExecuted;
	};
}