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
#include <Spore\UTFWin\Constants.h>
#include <Spore\Object.h>

#include <EASTL\initializer_list.h>
#include <EASTL\functional.h>

#define IWinProcPtr eastl::intrusive_ptr<UTFWin::IWinProc>

namespace UTFWin
{

	///
	/// This class is a window procedure, also known as an event/message listener. IWinProc objects are added to windows;
	/// when a message (aka event) is received or generated on the window, the window procedures receive it and handle it.
	/// 
	class IWinProc : public Object
	{
	public:
		///
		/// Gets a number that represents the priority of this IWinProc. The procedures with highest priority
		/// will be the first ones to receive a message when the window they are added to receives it.
		///
		/* 10h */	virtual int GetPriority() const { return 0; };

		///
		/// Gets the flags that represent which type of messages this IWinProc can handle. This allows for better
		/// performance, since generally a procedure only needs to listen specific events. The flags are in the
		/// kEventFlag... values.
		///
		/* 14h */	virtual int GetEventFlags() const = 0; 

		///
		/// Method called every time a message is received on a window that has this IWinProc added. 
		/// This method is responsible of handling (or not) the message. This method receives the IWindow
		/// that is currently receiving the message; this way, the same IWinProc can be listening for more than
		/// one window. This method returns whether the message was handled or not; if it was handled, no other 
		/// IWinProcs will be called on that window.
		/// @param pWindow The window that received this message.
		/// @param message The message received.
		/// @returns Whether the message was handled or not.
		///
		/* 18h */	virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) = 0;

		static const uint32_t TYPE = 0x2F009DD0;
	};

	class LambdaProc : public IWinProc
	{
	public:
		LambdaProc(HandleUILambda_t pFunction);
		LambdaProc(HandleUILambda_t pFunction, int eventFlags);
		LambdaProc(HandleUILambda_t pFunction, int eventFlags, int priority);

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t typeID) const override;

		virtual int GetPriority() const override;
		virtual int GetEventFlags() const override;
		virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

	protected:
		int mnRefCount;
		HandleUILambda_t mpFunction;
		int mEventFlags;
		int mPriority;
	};

	class LambdaFilterProc : public LambdaProc
	{
	public:
		LambdaFilterProc(HandleUILambda_t pFunction, int eventFlags, int priority, const eastl::vector<MessageType>& types);

		virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

	protected:
		eastl::vector<MessageType> mTypes;
	};
};
