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
#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\Constants.h>
#include <Spore\UTFWin\Message.h>
#include <Spore\UTFWin\WindowIterators.h>

///
/// @namespace UTFWin
/// UTFWin is the user interface system in Spore. The ModAPI defines some functionalities of this system;
/// although a user interface can be created via coding, it is recommended to use the SPUI Editor in SporeModder instead.
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

/// 
/// @page ui User Interface
///
/// This page includes information about the user interface system in Spore (UTFWin).
/// To use the UI system, you need to include the UserInterface.h
///
/// @tableofcontents
///
/// @section ui_tutorial1 Tutorial: Load a SPUI file
///
/// User interfaces are saved in the game files as .spui files. To load a SPUI file, first you must create an instance
/// of the UTFWin::UILayout class. It is recommended that you store it somewhere. Later, just use the UTFWin::UILayout::Load()
/// , UTFWin::UILayout::LoadByID() or the UTFWin::UILayout::LoadByName() methods.
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// UTFWin::UILayout layout;
/// // The LoadByName method takes a wstring as a parameter, so you need to prefix it with L
/// layout.LoadByName(L"EditorSharedUI");
/// ~~~~~~~~~~~~~~~~~
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// UTFWin::UILayout layout;
/// layout.LoadByID(0xF0F17503);
/// ~~~~~~~~~~~~~~~~~
///
/// By default, the layout is added to the main window of the game. Probably that's not what you want. If
/// you already have an IWindow* where you want to place your layout (more on that later), you just need to use
/// UTFWin::UILayout::GetContainerWindow() method and add it to the IWindow:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// UTFWin::UILayout layout;
/// layout.LoadByID(0xF0F17503);
///
/// // pWindow is a UTFWin::IWindow*
/// pWindow->AddWindow(layout.GetContainerWindow());
/// ~~~~~~~~~~~~~~~~~
///
/// @section ui_tutorial2 Tutorial: Getting a certain window
///
/// If you have ever used the SPUI Editor in SporeModder, you might have seen that windows are identified using a Control ID.
/// This control ID is considered the "name" of the window, and it is used in message listening and to get windows.
/// Both the UTFWin::IWindow and the UTFWin::UILayout classes have a method called FindWindowByID(), which is used to
/// get a window contained in that window/layout that has the specified Control ID. If the window does not exist, the methods
/// return nullptr.
///
/// There's a special case: the main window. The main window is the top window in the hierarchy, and it's the one that contains 
/// all the game interface. To get the main window:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// UTFWin::IWindow* pMainWindow = UTFWin::IWindowManager::Get()->GetMainWindow();
/// ~~~~~~~~~~~~~~~~~
///
/// @section ui_tutorial3 Tutorial: Other window operations
///
/// Here are other basic operations that can be done with windows. In the following examples the UTFWin:: scope 
/// has been ommited for simplicity.
///
/// - *Showing/hiding windows*: To toggle the visibility of a window, you must use the UTFWin::IWindow::SetFlag() method 
/// like this:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// IWindow* pWindow;
/// ...
/// pWindow->SetFlag(UTFWin::kWinFlagVisible, true);  // true -> visible, false -> invisible
/// ~~~~~~~~~~~~~~~~~
/// This method can be used for other window flags as well, check the UTFWin::WindowFlags namespace.
///
/// - **Creating new windows**: UTFWin::IWindow is an interface that represents a user interface component in the screen.
/// However, when you want to create new windows from the code, you need to use their concrete instances: UTFWin::Window, 
/// UTFWin::WinButton, etc. Most of them are not supported yet, but the most important one, UTFWin::Window, is; creating a
/// new window is as simple as this:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// intrusive_ptr<Window> pWindow = new Window();
/// ~~~~~~~~~~~~~~~~~
///
/// - **Destroying windows**: When you are done with a window and you want to destroy it (not hide it, destroy it), this is 
/// what you must do. Note that this method will destroy all the children of pWindow as well. In addition, pWindow must have 
/// a parent in order for this to work.
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// pWindow->GetParent()->DisposeWindowFamily(pWindow);
/// ~~~~~~~~~~~~~~~~~
///
/// - **Working with window hierarchy**: Windows are structured in a hierarchy. A window can have multiple children; a window can
/// only be a child of a single window (the parent window). Window coordinates are relative to the position of their parent.
/// These are the different operations you can do relating hierarchy:
///		- To make a window be child of another window, UTFWin::IWindow::AddWindow():
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// pParent->AddWindow(pWindow);
/// ~~~~~~~~~~~~~~~~~
///		- To remove a window from its parent hierarchy, therefore setting it to have no parent, UTFWin::IWindow::RemoveWindow():
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// pParent->RemoveWindow(pWindow);
/// ~~~~~~~~~~~~~~~~~
///		- To get the parent of a window, UTFWin::IWindow::GetParent():
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// IWindow* pParent = pWindow->GetParent();
/// ~~~~~~~~~~~~~~~~~
///		- To check if a window is contained in the hierarchy of another window. This will check the children' children, etc
/// so it might return true even if it's not a direct child. UTFWin::IWindow::IsAncestorOf():
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // is pWindow contained in the hierarchy of pParent?
/// if (pParent->IsAncestorOf(pWindow)) ...
/// ~~~~~~~~~~~~~~~~~
///		- To iterate through all the children of a window, UTFWin::IWindow::children():
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// for (IWindow* pChild : children())
/// {
///		...
/// }
/// ~~~~~~~~~~~~~~~~~
///		- To change the Z index of a window, you need to use the UTFWin::IWindow::BringToFront() and 
/// UTFWin::IWindow::SendToBack() methods. When a window is in front of its siblings (other children of its parent)
/// it is rendered the last.
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// // pWindow must be a child of pParent
/// pParent->BringToFront(pWindow);
/// ~~~~~~~~~~~~~~~~~
///
/// @section ui_tutorial4 Tutorial: Window layouts
///
/// A window occupies a rectangle in the screen. Relating this, we can distinguish two properties: the 'area' and the
/// 'real area'. 
/// - The 'area' is a Rectangle that defines certain parameters for the UI layout. Usually this is just the
/// position and the size of the rectangle, but certain layouts might use it differently. It is relativeto the parent
/// of the window. Check the UTFWin::IWindow::GetArea() and UTFWin::IWindow::SetArea() methods.
/// - The 'real area' is the real position and size of the window relative to the screen, after all layouts have been
/// applied. The real area is, therefore, the real Rectangle that the window occupies in the game screen.
/// Check the UTFWin::IWindow::GetRealArea() method. To update the real area (apply all layouts and area changes)
/// use the UTFWin::IWindow::Revalidate() method.
///
/// Apart from this methods, there are other utility methods that can be used to change the 'area' property:
/// UTFWin::IWindow::SetArea(), UTFWin::IWindow::SetLocation() and UTFWin::IWindow::SetSize(). There are also
/// equivalent methods that set those parameters after the layouts are applied (note that it's still relative to the
/// parent): UTFWin::IWindow::SetLayoutArea(), UTFWin::IWindow::SetLayoutLocation() and UTFWin::IWindow::SetLayoutSize().
///
/// A layout (classes that inherit from UTFWin::ILayoutStyle) uses the 'area' of a window and its parent to apply some modifications.
/// Layouts have some parameters and can be combined. Layouts are in fact window procedures, so they are added with the
/// UTFWin::IWindow::AddWinProc() method.
/// - UTFWin::SimpleLayout: It makes the 'area' parameters be relative to the edges of the parent. This is equivalent to the
/// 'anchor' property in some UI designers. The SimpleLayout has a parameter that determines to which edges the area is anchored;
/// certain combinations can make the component align to the left/right/top/bottom of the parent or horizontally/vertically fill
/// the parent area.
/// - UTFWin::RelativeLayout: Similar to SimpleLayout, but it uses relative parameters that allow the window to fit proportions
/// of its parent area.
///
/// @section ui_tutorial5 Tutorial: Drawables and how windows are rendered
///
/// Windows have two basic parameters that control its appearance: the 'fill' and the 'shade' colors. The 'fill' color
/// is rendered in the background, filling all the area of the window. The 'area' color is a tint that changes how all
/// the window is rendered.
///
/// Additionally, windows can use drawables to render more advanced things. Classes that inherit from UTFWin::IDrawable can
/// be set as the drawable of a window using the UTFWin::IWindow::SetDrawable() method. Note that certain window classes only
/// support specific types of drawables. 
///
/// IDrawables can also be inherited in order to create new drawables. For example, the game minimap is a modified drawable that
/// renders an image generated in the code.
///
/// @section ui_tutorial6 Tutorial: Listening to UI events
///
/// Probably the most common use of the UTFWin module is listening to UI events. There are UI events (represented by the
/// UTFWin::Message class) for everything that can happen in the user interface: mouse/keyboard input, rendering, updating,
/// pressing buttons, writing in text fields, etc.
///
/// In order to listen to UI events, you need to create a class that inherits from UTFWin::IWinProc. Window procedures are
/// added to windows using the UTFWin::IWindow::AddWinProc() method; when a message is raised/received on that window, 
/// its window procedures. When inheriting the UTFWin::IWinProc class, there are two methods that must be overriden:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// class MyListener : public UTFWin::IWinProc
/// {
/// public:
///		virtual int GetEventFlags() const override; 
///		virtual bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;
/// ...
/// };
/// ~~~~~~~~~~~~~~~~~
///
/// You can use the "ModAPI Window Procedure" item template to create a basic IWinProc class.
///
/// - UTFWin::IWinProc::GetEventFlags() must return an integer, a combination of the flags in UTFWin::EventFlags. The procedure
/// will only receive messages of the types determined by the value returned in this method. For example, if you want to listen
/// to mouse/keyboard input and the 'paint' events, this method should return UTFWin::kEventFlagBasicInput | UTFWin::kEventFlagPaint.
///
/// - UTFWin::IWinProc::HandleUIMessage() is the method that is called every time a message is raised/received on a window that this
/// window procedure is listening. This method is only called if the type of the message is included in the GetEventFlags() method.
/// This method must return a boolean value, whether the message was handled or not; if the method returns true, no more window
/// procedures will receive the message. 
///
/// The Message class contains information about the message received. The general information includes the type of message
/// and the IWindow* that generated it. Then, there is a union of different structs that contain data for specific types of
/// messages. For example, if you received an UTFWin::kMsgMouseMove message, you would need to use the parameters in
/// the UTFWin::Message::Mouse member.
///
/// Usually, the first thing done in the HandleUIMessage() method is checking the type of message received and acting consequently.
/// Here is an example of a message handling method that reacts when a certain button is pressed (the GetEventFlags() must
/// return UTFWin::kEventFlagAdvanced in order to receive that).
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// bool MyListener::HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message)
/// {
///		if (message.mEventType == UTFWin::kMsgButtonClick)
///		{
///			// a button was pressed, was it the one with control ID 'ExitButton'
///			if (message.mpSource->GetControlID() == Hash::FNV("ExitButton"))
///			{
///				// do something and return true, since we did handle the message
///				return true;
///			}
///		}
///		// by default, just return false since we didn't handle the message
///		return false;
/// }
/// ~~~~~~~~~~~~~~~~~
///
/// In addition to window procedures, there are the UTFWin::InteractiveWinProc and UTFWin::InteractiveWindow classes. These classes
/// extend IWinProc and IWindow respectively, and define methods that allow to easily handle messages. Instead of handling everything in a big
/// HandleUIMessage() method, in those classes you can extend the method that listens to the type of event you want, for example 
/// UTFWin::InteractiveWinProc::OnMouseClick().
///
/// Finally, there's a function to programatically send a message in a window. This can be used to programatically activate buttons,
/// for example. If you have the IWindow*, you just have to use the UTFWin::IWindow::SendMsg() method:
/// ~~~~~~~~~~~~~~~~~{.cpp}
/// UTFWin::IWindow* pWindow = ...;
///
/// // We will raise a message in pWindow telling it was clicked. First, we must create the Message
/// UTFWin::Message message;
/// message.mpSource = pWindow;  // Which window generated this event?
/// message.mEventType = UTFWin::kMsgMouseDown;  // What type of event is it?
/// // Now we want to set the specific parameters (i.e. the position that was clicked,...).
/// message.Mouse.mMouseState = UTFWin::MouseState::kLeftButtonDown;  // Which button was clicked?
/// // The mouse coordinates are relative to the window that raised it, so this represents the top-left corner.
/// message.Mouse.mfMouseX = 0;
/// message.Mouse.mfMouseY = 0;
///
/// // Now just send the message
/// pWindow->SendMsg(message);
/// ~~~~~~~~~~~~~~~~~
///
/// @section more_info More information:
/// - UTFWin
/// - UTFWin::IWindow
/// - UTFWin::IWinProc
/// - UTFWin::IDrawable
/// - UTFWin::Window
/// - UTFWin::IWindowManager
/// - UTFWin::UILayout
/// - UTFWin::Message
///
