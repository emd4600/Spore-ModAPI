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
#include <Spore\App\IMessageListener.h>
#include <EASTL\vector.h>
#include <EASTL\initializer_list.h>
#include <EASTL\intrusive_ptr.h>

/// Access the active message manager.
#define MessageManager (*App::IMessageManager::Get())

#define ScheduledTaskListenerPtr eastl::intrusive_ptr<App::ScheduledTaskListener>
#define SimScheduledTaskListenerPtr eastl::intrusive_ptr<Simulator::ScheduledTaskListener>
#define UpdateMessageListenerPtr eastl::intrusive_ptr<App::UpdateMessageListener>

namespace App
{
	enum {
		/// Sent when all the systems in the game have finished initializing, except for the Simulator ones.
		/// Does not use message data.
		kMsgAppInitialized = 0x49790B2,
		/// Sent every game frame, after all other systems have been updated. Does not use message data.
		kMsgAppUpdate = 0x1EE100A
	};

	///
	/// This manager defines a messaging system, that allows communication between different parts of the code. When a message is sent
	/// from any part of the code, all the objects that are listening to that specific message (which is identified using an ID) are notified.
	/// Therefore, all the parts of the code that need to react to certain events can be notified without he sender needing to know them.
	/// 
	/// To listen to messages, two things can be used. The first one, and the most common, is the IMessageListener interface, which allow 
	/// classes to listen to messages. Another alternative is using a handler function, which is a static function that receives messages.
	///
	class IMessageManager
	{
	public:

		/// A static message handler. This is the equivalent to the IMessageListener::HandleMessage() function.
		typedef void(*MessageHandler_t)(uint32_t messageID, void* pData, void* pObject);

	protected:
		struct Entry
		{
			/* 00h */	IMessageListener* mpListener;
			/* 04h */	int mnPriority;
			/* 08h */	bool mbRefCounted;
			/* 0Ch */	MessageHandler_t mpHandler;
			/* 10h */	void* mpObject;
		};

	public:

		enum Options
		{
			/// If true, this manager uses mutexs to work with threads. Additionally, the user can use the function IMessageManager::UseMutex(bool).
			kOptionAllowLock = 0,  // C0h 
			/// If true, the listeners added in the manager will be refcounted.
			kOptionRefCount = 4,  // C4h
		};

		/* 00h */	virtual ~IMessageManager() {};

		/* 04h */	virtual bool Initialize() = 0;
		/* 08h */	virtual bool Dispose() = 0;

		///
		/// Returns the boolean value of the specified option, in the IMessageManager::Options enum.
		/// @param option The option whose value will be returned.
		///
		/* 0Ch */	virtual bool GetOption(Options option) = 0;

		///
		/// Sets the boolean value of the specified option, in the IMessageManager::Options enum.
		/// @param option The option whose value will be set.
		/// @param bValue The new boolean value of the option.
		///
		/* 10h */	virtual void SetOption(Options option, bool bValue) = 0;

		///
		/// Sends a message in this manager, notifying all the interfaces listening for the specified message ID.
		/// @param messageID The ID this message notifies.
		/// @param pMessage Data related to the message, not all messages need to use this.
		/// @param pListener [Optional] The IMessageListener that will receive this message. If this is specified, no other listener will be notified.
		///
		/* 14h */	virtual void PostMSG(uint32_t messageID, void* pMessage, IMessageListener* pListener = nullptr) = 0;

		/* 18h */	virtual void func18h(int, int, int) = 0;
		/* 1Ch */	virtual void func1Ch(int, int, int, int, int) = 0;

		///
		/// Adds a message listener to this manager, that will be notified of messages with the specified ID.
		/// A single listener can be listening to multiple message IDs.
		/// If the kOptionRefCount option is true, the IMessageListener::AddRef() method will be called on the listener.
		/// @param pListener The message listener to add.
		/// @param messageID The ID of the messages the listener is listening to.
		///
		/* 20h */	virtual void AddListener(IMessageListener* pListener, uint32_t messageID) = 0;

		///
		/// Adds a message listener to this manager, that will be notified of messages with the specified ID.
		/// A single listener can be listening to multiple message IDs.
		/// @param function The message listener to add.
		/// @param messageIDs A list of the IDs of the messages the listener will listen to.
		///
		inline void AddListener(LambdaMessageListener::HandleMessage_T function, const std::initializer_list<uint32_t> messageIDs)
		{
			auto listener = new LambdaMessageListener(function);
			for (uint32_t messageID : messageIDs) {
				AddListener(listener, messageID);
			}
		}

		///
		/// Same as IMessageManager::AddListener(), but this does not call AddRef().
		/// @param pListener The message listener to add.
		/// @param messageID The ID of the messages the listener is listening to.
		///
		/* 24h */	virtual void AddUnmanagedListener(IUnmanagedMessageListener* pListener, uint32_t messageID) = 0;

		///
		/// Adds a static handler function to this manager, that will be notified of messages with the specified ID.
		/// The same handler can be added multiple times using different priorities.
		/// @param pFunction A pointer to the handler function.
		/// @param pObject An object that will be sent as a parameter in the handler function.
		/// @param messageID The ID of the messages the handler is listening to.
		/// @param bRefCounted [Optional] If true and kOptionRefCount is true, a kMsgAddRef message will be sent on the handler.
		/// @param nPriority [Optional] The priority of this handler.
		///
		/* 28h */	virtual void AddHandler(MessageHandler_t pFunction, void* pObject, uint32_t messageID, bool bRefCounted = false, int nPriority = -1) = 0;

		///
		/// Makes the listener stop listening to the specified message ID. Optionally, a priority can be specified;
		/// if so, only if the listener with that priority will be removed.
		/// @param pListener The listener to remove.
		/// @param messageID The ID of the messages the listener is listening to, and that will stop listening.
		/// @param nPriority [Optional] The priority the listener must have to be removed. If it's -9999 (by default), it will be ignored.
		/// @returns Whether the handler was removed or not.
		///
		/* 2Ch */	virtual bool RemoveListener(IMessageListener* pListener, uint32_t messageID, int nPriority = -9999) = 0;

		///
		/// Makes the handler stop listening to the specified message ID. Optionally, a priority can be specified;
		/// if so, only if the handler with that priority will be removed.
		/// @param pFunction The handler function to remove.
		/// @param messageID The ID of the messages the handler is listening to, and that will stop listening.
		/// @param nPriority [Optional] The priority the handler must have to be removed. If it's -9999 (by default), it will be ignored.
		/// @returns Whether the handler was removed or not.
		///
		/* 30h */	virtual bool RemoveHandler(MessageHandler_t pFunction, uint32_t messageID, int nPriority = -9999) = 0;

		/* 34h */	virtual int func34h(int, int, int) = 0;
		/* 38h */	virtual int func38h() = 0;
		/* 3Ch */	virtual int func3Ch() = 0;  // returns pointer to this+0Ch

		///
		/// Locks or unlocks the mutexs in this manager, allowing to safely interact with this manager in different threads.
		/// If kOptionAllowLock is not true, this won't do anything.
		/// @param bLock True -> Lock; False -> Unlock
		///
		/* 40h */	virtual int UseMutex(bool bLock) = 0;

	protected:

		///
		/// Adds the entry to listen to the given message ID.
		/// @param entry The entry that contains the listener or handler function.
		/// @param messageID The message ID the entry will be notified.
		/// 
		/* 44h */	virtual void AddEntry(const Entry& entry, uint32_t messageID);

		///
		/// Removes the entry assigned at the given messageID with the given priority. If the priority is -9999, it will
		/// be ignored. If the entry is refcounted and kOptionRefCount is true, Release() will be called on the listener
		/// (or a kMsgRelease will be sent to the handler).
		/// This function works for both listeners and handlers.
		/// @param pMessageObject The handler or listener to remove.
		/// @param messageID The message ID the entry will be removed from.
		/// @param nPriority [Optional] The priority of the entry to be removed.
		/// @returns Whether the entry was removed or not.
		///
		/* 48h */	virtual bool RemoveEntry(void* pMessageObject, uint32_t messageID, int nPriority = -9999);

	public:

		///
		/// Returns the active message manager.
		///
		static IMessageManager* Get();
	};

	///
	/// Adds an "Update" function that is called once every game frame. 
	/// The time between frames is not constant, but you can use the Clock and Simulator::cGonzagoTimer
	/// classes to measure elapsed time.
	///
	/// The method returns the object that holds the update function. If you want to remove the function so it is not called,
	/// anymore, you can do it by calling App::RemoveUpdateFunction(...) with the returned object as parameter.
	///
	/// Internally, this is implemented just by adding a message listener that listens
	/// to the kMsgAppUpdate message.
	///
	/// @param function A void function with no parameters, that will be executed every frame.
	inline eastl::intrusive_ptr<UpdateMessageListener> AddUpdateFunction(const VoidFunction_T& function) {
		auto listener = new UpdateMessageListener(function);
		MessageManager.AddListener(listener, kMsgAppUpdate);
		return listener;
	}

	///
	/// Adds a class with an Update method that is called once every game frame. 
	/// The time between frames is not constant, but you can use the Clock and Simulator::cGonzagoTimer
	/// classes to measure elapsed time.
	///
	/// The method returns the object that holds the updatable class. If you want to remove the function so it is not called,
	/// anymore, you can do it by calling App::RemoveUpdateFunction(...) with the returned object as parameter.
	///
	/// Internally, this is implemented just by adding a message listener that listens
	/// to the kMsgAppUpdate message.
	///
	/// @param updatable An object with an Update method, that will be executed every frame.
	inline eastl::intrusive_ptr<UpdateMessageListener> AddUpdateFunction(IUpdatable* updatable) {
		auto listener = new UpdateMessageListener(updatable);
		MessageManager.AddListener(listener, kMsgAppUpdate);
		return listener;
	}

	///
	/// Executes a function after a certain time (measured in seconds) has passed from ths call. The function 
	/// is executed only once, and the time starts counting since this ScheduleTask method has been called.
	///
	/// The method returns the object that holds the scheduled task. If you want to remove the task before it is called,
	/// you can do it by calling App::RemoveScheduledTask(...) with the returned object as parameter.
	///
	/// Internally, this is implemented by adding a message listener that listens to the 
	/// kMsgAppUpdate message. Every frame uses a Clock object to compare the elapsed time since 
	/// this task as scheduled. The listener is removed once the task has finished executing.
	///
	/// @param function A void function with no parameters, that will be executed every frame.
	/// @param scheduleTime The time that has to pass, in seconds, since the task is scheduled for it to be executed.
	inline ScheduledTaskListenerPtr ScheduleTask(const VoidFunction_T& function, float scheduleTime) {
		auto listener = new ScheduledTaskListener(function, scheduleTime, 0.0f);
		MessageManager.AddListener(listener, kMsgAppUpdate);
		listener->StartClock();
		return listener;
	}

	///
	/// Executes a class method after a certain time (measured in seconds) has passed from ths call. The method 
	/// is executed only once, and the time starts counting since this ScheduleTask method has been called.
	///
	/// The method returns the object that holds the scheduled task. If you want to remove the task before it is called,
	/// you can do it by calling App::RemoveScheduledTask(...) with the returned object as parameter.
	///
	/// Internally, this is implemented by adding a message listener that listens to the 
	/// kMsgAppUpdate message. Every frame uses a Clock object to compare the elapsed time since 
	/// this task as scheduled. The listener is removed once the task has finished executing.
	///
	/// @param object The object to which the method will be called.
	/// @param method A void method with no parameters, that will be executed every frame.
	/// @param scheduleTime The time that has to pass, in seconds, since the task is scheduled for it to be executed.
	template <class T>
	inline ScheduledTaskListenerPtr ScheduleTask(T* object, VoidMethod_T<T> method, float scheduleTime) {
		return ScheduleTask([object, method]() {
			(object->*method)();
		}, scheduleTime);
	}

	///
	/// Executes a function after a certain time (measured in seconds) has passed from this call, 
	/// and then keeps repeating it after a certain period (defined by the repeatRate parameter) parameter. The function is executed only
	/// once, and the time starts counting since this ScheduleTask method has been called.
	///
	/// The method returns the object that holds the scheduled task. If you want to remove the task so it does not
	/// execute anymore, you can do it by calling App::RemoveScheduledTask(...) with the returned object as parameter.
	///
	/// Internally, this is implemented by adding a message listener that listens to the 
	/// kMsgAppUpdate message. Every frame uses a Clock object to compare the elapsed time since 
	/// this task as scheduled. The listener is removed once the task has finished executing.
	///
	/// @param function A void function with no parameters, that will be executed every frame.
	/// @param scheduleTime The time that has to pass, in seconds, since the task is scheduled for it to be executed.
	/// @param repeatRate How many seconds have to pass between every execution of the task.
	inline ScheduledTaskListenerPtr ScheduleRepeatedTask(const VoidFunction_T& function, float scheduleTime, float repeatRate) {
		auto listener = new ScheduledTaskListener(function, scheduleTime, repeatRate);
		MessageManager.AddListener(listener, kMsgAppUpdate);
		listener->StartClock();
		return listener;
	}

	///
	/// Executes a function after a certain time (measured in seconds) has passed from this call, 
	/// and then keeps repeating it after a certain period (defined by the repeatRate parameter) parameter. The function is executed only
	/// once, and the time starts counting since this ScheduleTask method has been called.
	///
	/// The method returns the object that holds the scheduled task. If you want to remove the task so it does not
	/// execute anymore, you can do it by calling App::RemoveScheduledTask(...) with the returned object as parameter.
	///
	/// Internally, this is implemented by adding a message listener that listens to the 
	/// kMsgAppUpdate message. Every frame uses a Clock object to compare the elapsed time since 
	/// this task as scheduled. The listener is removed once the task has finished executing.
	///
	/// @param object The object to which the method will be called.
	/// @param method A void method with no parameters, that will be executed every frame.
	/// @param scheduleTime The time that has to pass, in seconds, since the task is scheduled for it to be executed.
	/// @param repeatRate How many seconds have to pass between every execution of the task.
	template <class T>
	inline ScheduledTaskListenerPtr ScheduleRepeatedTask(T* object, VoidMethod_T<T> method, float scheduleTime, float repeatRate) {
		return ScheduleRepeatedTask([object, method]() {
			(object->*method)();
		}, scheduleTime, repeatRate);
	}

	inline bool RemoveUpdateFunction(eastl::intrusive_ptr<UpdateMessageListener>& updateListener) {
		return MessageManager.RemoveListener(updateListener.get(), kMsgAppUpdate);
	}

	inline bool RemoveScheduledTask(ScheduledTaskListenerPtr& taskListener) {
		return MessageManager.RemoveListener(taskListener.get(), kMsgAppUpdate);
	}


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(IMessageManager)
	{
		DeclareAddress(Get);
	}
}

namespace Simulator
 {
	///
	/// Executes a function after a certain time (measured in seconds) has passed from ths call. The function 
	/// is executed only once, and the time starts counting since this ScheduleTask method has been called.
	///
	/// The method returns the object that holds the scheduled task. If you want to remove the task before it is called,
	/// you can do it by calling Simulator::RemoveScheduledTask(...) with the returned object as parameter.
	///
	/// Internally, this is implemented by adding a message listener that listens to the 
	/// kMsgAppUpdate message. Every frame uses a cGonzagoTimer object to compare the elapsed time since 
	/// this task as scheduled. The listener is removed once the task has finished executing.
	///
	/// @param function A void function with no parameters, that will be executed every frame.
	/// @param scheduleTime The time that has to pass, in seconds, since the task is scheduled for it to be executed.
	inline SimScheduledTaskListenerPtr ScheduleTask(const App::VoidFunction_T& function, float scheduleTime) {
		auto listener = new ScheduledTaskListener(function, scheduleTime, 0.0f);
		MessageManager.AddListener(listener, App::kMsgAppUpdate);
		listener->StartClock();
		return listener;
	}

	///
	/// Executes a class method after a certain time (measured in seconds) has passed from ths call. The method 
	/// is executed only once, and the time starts counting since this ScheduleTask method has been called.
	///
	/// The method returns the object that holds the scheduled task. If you want to remove the task before it is called,
	/// you can do it by calling Simulator::RemoveScheduledTask(...) with the returned object as parameter.
	///
	/// Internally, this is implemented by adding a message listener that listens to the 
	/// kMsgAppUpdate message. Every frame uses a cGonzagoTimer object to compare the elapsed time since 
	/// this task as scheduled. The listener is removed once the task has finished executing.
	///
	/// @param object The object to which the method will be called.
	/// @param method A void method with no parameters, that will be executed every frame.
	/// @param scheduleTime The time that has to pass, in seconds, since the task is scheduled for it to be executed.
	template <class T>
	inline ScheduledTaskListenerPtr ScheduleTask(T* object, App::VoidMethod_T<T> method, float scheduleTime) {
		return ScheduleTask([object, method]() {
			(object->*method)();
		}, scheduleTime);
	}

	///
	/// Executes a function after a certain time (measured in seconds) has passed from this call, 
	/// and then keeps repeating it after a certain period (defined by the repeatRate parameter) parameter. The function is executed only
	/// once, and the time starts counting since this ScheduleTask method has been called.
	///
	/// The method returns the object that holds the scheduled task. If you want to remove the task so it does not
	/// execute anymore, you can do it by calling Simulator::RemoveScheduledTask(...) with the returned object as parameter.
	///
	/// Internally, this is implemented by adding a message listener that listens to the 
	/// kMsgAppUpdate message. Every frame uses a cGonzagoTimer object to compare the elapsed time since 
	/// this task as scheduled. The listener is removed once the task has finished executing.
	///
	/// @param function A void function with no parameters, that will be executed every frame.
	/// @param scheduleTime The time that has to pass, in seconds, since the task is scheduled for it to be executed.
	/// @param repeatRate How many seconds have to pass between every execution of the task.
	inline SimScheduledTaskListenerPtr ScheduleRepeatedTask(const App::VoidFunction_T& function, float scheduleTime, float repeatRate) {
		auto listener = new ScheduledTaskListener(function, scheduleTime, repeatRate);
		MessageManager.AddListener(listener, App::kMsgAppUpdate);
		listener->StartClock();
		return listener;
	}

	///
	/// Executes a function after a certain time (measured in seconds) has passed from this call, 
	/// and then keeps repeating it after a certain period (defined by the repeatRate parameter) parameter. The function is executed only
	/// once, and the time starts counting since this ScheduleTask method has been called.
	///
	/// The method returns the object that holds the scheduled task. If you want to remove the task so it does not
	/// execute anymore, you can do it by calling Simulator::RemoveScheduledTask(...) with the returned object as parameter.
	///
	/// Internally, this is implemented by adding a message listener that listens to the 
	/// kMsgAppUpdate message. Every frame uses a cGonzagoTimer object to compare the elapsed time since 
	/// this task as scheduled. The listener is removed once the task has finished executing.
	///
	/// @param object The object to which the method will be called.
	/// @param method A void method with no parameters, that will be executed every frame.
	/// @param scheduleTime The time that has to pass, in seconds, since the task is scheduled for it to be executed.
	/// @param repeatRate How many seconds have to pass between every execution of the task.
	template <class T>
	inline ScheduledTaskListenerPtr ScheduleRepeatedTask(T* object, App::VoidMethod_T<T> method, float scheduleTime, float repeatRate) {
		return ScheduleRepeatedTask([object, method]() {
			(object->*method)();
		}, scheduleTime, repeatRate);
	}

	inline bool RemoveScheduledTask(ScheduledTaskListenerPtr& taskListener) {
		return MessageManager.RemoveListener(taskListener.get(), App::kMsgAppUpdate);
	}
}