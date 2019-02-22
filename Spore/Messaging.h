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

/// @file Messaging.h 
/// This file includes all the headers necessary for the messaging system in Spore.
/// For more information, check the App::IMessageListener and App::IMessageManager classes.

#include <Spore\App\IMessageListener.h>
#include <Spore\App\IMessageManager.h>

/// 
/// @page messaging Messaging
///
/// The messaging system allows different parts of the code to communicate between them. When a message is sent,
/// all the listeners registered to that type of message will be noticed. Therefore, an event can be raised without
/// needing to have any knowledge about the classes that will receive and react to the event.
/// To use the messaging system, you need to include the Messaging.h
///
/// @tableofcontents
///
/// @section messaging_tutorial1 Tutorial: Register a message listener
///
/// Message listeners are classes that publicly inherit from the App::IMessageListener class. To create a listener for 
/// a certain type of message, you need to create a class that inherits from that. However, you would need to give an 
/// implementation for the AddRef() and Release() methods; if you don't want that, you can directly inherit the class
/// App::DefaultMessageListener.
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// class MyListener : public App::DefaultMessageListener
/// {
/// public:
///		// You need to implement this method, which is called when a message of the type the listener
///		// is registered to is sent
///		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;
/// }
/// ~~~~~~~~~~~~~~~~~
///
/// You can use the "ModAPI Message Listener" item template to create a basic IMessageListener class.
///
/// On the code of that class, you must give an implemetnation to the App::IMessageListener::HandleMessage() method,
/// which is called every time a message of the type the listener is expecting is sent.
///
/// Now, in order to receive messages, you must register the listener to one or more message IDs. Just
/// call the App::IMessageManager::AddListener() method:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// MyListener* pListener = new MyListener();
/// ...
/// App::IMessageManager::Get()->AddListener(pListener, 0x40FD2019);
/// // you can register a single listener to more than one message ID
/// App::IMessageManager::Get()->AddListener(pListener, 0x001D0003);
/// ~~~~~~~~~~~~~~~~~
///
/// @section messaging_tutorial2 Tutorial: Send a message
///
/// When a message is sent, all the listeners registered to that ID will be notified. Sending a message is very simple, you
/// just have to use the App::IMessageManager::PostMSG() method:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// App::IMessageManager::Get()->PostMSG(0x001D0003, nullptr);
/// ~~~~~~~~~~~~~~~~~
/// The second argument is data for the message, which can be any object you want (or nullptr). The use of this parameter
/// depends on the implementation of the listeners.
///
/// @section more_info More information:
/// - App::IMessageManager
/// - App::IMessageListener
///
