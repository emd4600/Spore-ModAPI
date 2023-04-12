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

/// @file UserInterface.h
/// This file has all the include necessaries to use the user interface system, UTFWin, in Spore.

#include <Spore\UTFWin\IWindow.h>
#include <Spore\UTFWin\Window.h>
#include <Spore\UTFWin\IWindowManager.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\IButton.h>
#include <Spore\UTFWin\ITextEdit.h>
#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\ImageDrawable.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\SimpleLayout.h>
#include <Spore\UTFWin\ProportionalLayout.h>
#include <Spore\UTFWin\Constants.h>
#include <Spore\UTFWin\Message.h>
#include <Spore\UTFWin\WindowIterators.h>
#include <Spore\UTFWin\CursorManager.h>
#include <Spore\UTFWin\SporeTooltipWinProc.h>

///
/// @namespace UTFWin
///
/// @brief The user interface system.
///
/// UTFWin is the user interface system in Spore. The ModAPI defines some functionalities of this system;
/// even though a user interface can be created via coding, it is recommended to use the SPUI Editor in SporeModder FX instead.
/// The ModAPI can be useful for programatically creating pieces of interfaces (like the editor categories) and listening
/// to UI Events.
///
/// The basic unit in UTFWin is the IWindow, an abstract class that defines an area in the screen. All classes whose name
/// start with 'Win...' are IWindows. The basic implementation is Window; there's another class called InteractiveWindow
/// which is prepared to receive events.
///
/// Another key piece in UTFWin is IWinProc, 'window procedures'. Window procedures receive events (aka messages) received on
/// windows, therefore they act as event listeners; they are the UI equivalent to IMessageListener. 
///
/// For rendering windows, the IDrawable interface is used. Windows can only have one (or none) IDrawable object assigned;
/// depending on the window implementation, the drawable might only be used to render certain parts. 
///
