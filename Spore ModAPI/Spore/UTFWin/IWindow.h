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

#include <Spore\Object.h>
#include <Spore\MathUtils.h>
#include <Spore\UTFWin\Constants.h>
#include <Spore\UTFWin\UTFWinObject.h>

#include <EASTL\list.h>
#include <EASTL\intrusive_list.h>
#include <EASTL\vector.h>

#define IWindowPtr eastl::intrusive_ptr<UTFWin::IWindow>

namespace UTFWin
{
	class IDrawable;
	class IWinProc;
	class IWindowManager;

	class WindowChildren;
	class WindowProcedures;
	class Message;

	enum WindowFlags
	{
		/// Flag indicating that this window is visible
		kWinFlagVisible = 0x1,
		/// Flag to put the window into an interactive state
		kWinFlagEnabled = 0x2,
		/// If true, window will move to front when clicked
		kWinFlagClickToFront = 0x4,
		/// Flag indicating that this window can't recieve mouse events
		kWinFlagIgnoreMouse = 0x10,
		/// If true, window will always be in front of windows that don't have this flag
		kWinFlagAlwaysInFront = 0x40,
		/// Flag indicating whether child windows should be clipped.
		kWinFlagClip = 0x400,
		/// Flag indicating that this window's children can't recieve mouse events
		kWinFlagIgnoreMouseChildren = 0x1000,
	};

	enum
	{
		kStateEnabled = 1,
		kStateClicked = 2,

		kStateHover = 8,
	};

	// Just so it can be used by the debuggger natvis
	struct Window_intrusive_list_node : public eastl::intrusive_list_node {};

	//typedef intrusive_list<IWindow> IWindowList_t;
	// Otherwise children() won't work
	typedef eastl::intrusive_list<Window_intrusive_list_node> IWindowList_t;

	class IWindow;
	typedef eastl::function<bool(IWindow*, const Message&)> HandleUILambda_t;

	///
	/// An interface that represents a component in the user interface. Windows occupy a rectangle in the screen and
	/// are fit inside a hierarchy: a window can have multiple children and only one parent. For more information,
	/// check the @ref ui "User Interface page".
	///
	class IWindow 
		: public UTFWinObject
		, public Window_intrusive_list_node
	{
	public:

		static const uint32_t TYPE = 0xEEEE8218;
		
		///
		/// Returns the parent IWindow of this window, or nullptr if it has no parent window.
		/// @returns A pointer to the IWindow parent of this window, or nullptr if there is none.
		///
		/* 10h */	virtual IWindow* GetParent() const = 0;

		///
		/// Returns the WindowManager that is operating on this window.
		/// @returns A pointer to the WindowManager being used in this window.
		///
		/* 14h */	virtual IWindowManager* GetWindowManager() const = 0;

		/* 18h */	virtual int func6() const = 0;
		
		///
		/// Sets the unique ID of this object. This ID is used to identfy windows, as it is the one used by FindWindowByID().
		/// This ID can also be used on message handling, to check what window raised the message.
		/// @returns The value of the 'controlID' property.
		///
		/* 1Ch */	virtual uint32_t GetControlID() const = 0;

		///
		/// Get the message ID sent by this window.
		/// @returns The value of the 'commandID' property.
		///
		/* 20h */	virtual uint32_t GetCommandID() const = 0; 

		/// Returns the ID which assigns a cursor to this window.
		/* 24h */	virtual uint32_t GetCursorID() const = 0;

		///
		/// Gets the current window flags. This can be used, for example, to check if a window is visible:
		/// ~~~~~~~~~~~~~~~~~~~~{.cpp}
		/// IWindow* pWindow = ....;
		///
		/// if (pWindow->GetFlags() & kWinFlagVisible) ...
		/// ~~~~~~~~~~~~~~~~~~~~
		/// @returns The value of the 'flags' property.
		///
		/* 28h */	virtual WindowFlags GetFlags() const = 0;

		///
		/// Gets the current state (selected, pressed, mouse hover, etc) of this window. Only certain types use this, like buttons.
		/// @returns The value of the 'state' property.
		///
		/* 2Ch */	virtual int GetState() const = 0;

		///
		/// Returns the color modulation value. This color acts as a tint: after the window is painted, it gets multiplied by this color.
		/// @returns The integer color representation of the value of the 'shadeColor' property.
		///
		/* 30h */	virtual Math::Color GetShadeColor() const = 0;

		///
		/// Gets the rectangular extent of this window, relative to the window's parent. Note this is the 'area' property, 
		/// but the real area of the window might be different depending on its parent and the IWinProcs operating in this window.
		/// @returns The area of this window, in screen coordinates.
		///
		/* 34h */	virtual const Math::Rectangle& GetArea() const = 0;

		///
		/// Gets the real rectangular extent of this window, in window coordinates. This has all the IWinProcs and parent position applied,
		/// so this is the real area of the window that gets painted onto the screen.
		/// @returns The real Math::Rectangle area of this window, in screen coordinates.
		///
		/* 38h */	virtual const Math::Rectangle& GetRealArea() const = 0;
		
		///
		/// Returns the text contents or title of the window. This value might be used or not depending on the implementation
		/// and type of window.
		/// @returns The char16_t* caption used in this window.
		///
		/* 3Ch */	virtual const char16_t* GetCaption() const = 0;

		///
		/// Returns the text font style ID used in this window. This value might be used or not depending on the implementation
		/// and type of window.
		/// @returns The text font ID used in this window.
		///
		/* 40h */	virtual uint32_t GetTextFontID() const = 0;

		/* 44h */	virtual const char16_t* func17() const = 0;

		/* 48h */	virtual int func18() const = 0;  // GetStyle?
		/* 4Ch */	virtual int func19() const = 0;

		///
		/// Sets the unique ID of this object. This ID is used to identfy windows, as it is the one used by FindWindowByID().
		/// This ID can also be used on message handling, to check what window raised the message.
		/// @param controlID The new value of the 'controlID' property.
		///
		/* 50h */	virtual void SetControlID(uint32_t controlID) = 0;
		
		///
		/// Set the message ID sent by this window.
		/// @param commandID The new value of the 'commandID' property.
		///
		/* 54h */	virtual void SetCommandID(uint32_t commandID) = 0;

		///
		/// Sets the current state (selected, pressed, mouse hover, etc) of this window. Only certain types use this, like buttons.
		/// This will generate a StateChanged message.
		/// @param state The new value of the 'state' property.
		///
		/* 58h */	virtual void SetState(int state) = 0;

		///
		/// Returns the color modulation value. This color acts as a tint: after the window is painted, it gets multiplied by this color.
		/// @param color The color to use as the 'shadeColor' property.
		///
		/* 5Ch */	virtual void SetShadeColor(Math::Color color) = 0;

		///
		/// Sets the rectangular extent of this window. Note that this will only affect the 'area' property of the window;
		/// the real area might use these values differently depending on the IWinProc objects operating on this window (e.g. SimpleLayout).
		/// Calling this method effectively calls the Revalidate() method, which ensures the real area of the window is updated using the new values.
		/// @param area The new value of the 'area' property.
		///
		/* 60h */	virtual void SetArea(const Math::Rectangle& area) = 0;

		///
		/// Sets the location of this window, relative to its parent. Note that this will only affect the 'area' property of the window;
		/// the real area might use these values differently depending on the IWinProc objects operating on this window (e.g. SimpleLayout).
		/// Calling this method effectively calls the Revalidate() method, which ensures the real area of the window is updated using the new values.
		/// @param fX The X coordinate to use in the 'area' property.
		/// @param fY The Y coordinate to use in the 'area' property.
		///
		/* 64h */	virtual void SetLocation(float fX, float fY) = 0;

		///
		/// Assigns the width and height of this window. Note that this will only affect the 'area' property of the window;
		/// the real area might use these values differently depending on the IWinProc objects operating on this window (e.g. SimpleLayout).
		/// Calling this method effectively calls the Revalidate() method, which ensures the real area of the window is updated using the new values.
		/// @param fWidth The width to use in the 'area' property.
		/// @param fHeight The height to use in the 'area' property.
		///
		/* 68h */	virtual void SetSize(float fWidth, float fHeight) = 0;

		///
		/// Sets the area that this component should have, relative to its parent window, after all layout styles are applied.
		/// This will call the ILayoutStyle::RevertLayout() method on all the layout styles in this window, starting with the last one
		/// (so the first layout applied will be the last one to be reverted), and then SetArea is called. 
		/// This ensures that the given layoutArea parameter will be the real area of this window, but relative to the parent.
		/// @param layoutArea The area this window should have.
		///
		/* 6Ch */	virtual void SetLayoutArea(const Math::Rectangle& layoutArea) = 0;

		///
		/// Assigns the location, relative to the parent window, that this window should have after all layouts are applied. 
		/// This will call the ILayoutStyle::RevertLayout() method on all the layout styles in this window, starting with the last one
		/// (so the first layout applied will be the last one to be reverted), and then SetArea is called. 
		/// This ensures that the given location parameters will be the real loctions of this window (relative to its parent).
		/// Calling this method effectively calls the Revalidate() method, which ensures the real area of the window is updated using the new values.
		/// @param fX The X coordinate, relative to the parent, that this window's location should have.
		/// @param fY The Y coordinate, relative to the parent, that this window's location should have.
		///
		/* 70h */	virtual void SetLayoutLocation(float fX, float fY) = 0;

		///
		/// Assigns the width and height that this window should have after all layouts are applied. 
		/// This will call the ILayoutStyle::RevertLayout() method on all the layout styles in this window, starting with the last one
		/// (so the first layout applied will be the last one to be reverted), and then SetArea is called. 
		/// This ensures that the given width and height parameters will be the real dimensions of this window.
		/// Calling this method effectively calls the Revalidate() method, which ensures the real area of the window is updated using the new values.
		/// @param fWidth The width this window should have.
		/// @param fHeight The height this window should have.
		///
		/* 74h */	virtual void SetLayoutSize(float fWidth, float fHeight) = 0;

		/// Sets the ID which assigns a cursor to this window. 
		/// The ID must have been loaded with cCursorManager::LoadCursor()
		/* 78h */	virtual void SetCursorID(uint32_t id) = 0;

		///
		/// Assigns the given value to the specified window flag. This can be used, for example, to toggle visibility:
		/// ~~~~~~~~~~~~~~~~~~~~{.cpp}
		/// IWindow* pWindow = ....;
		///
		/// pWindow->SetFlag(kWinFlagVisible, false);  // hide this window
		/// ~~~~~~~~~~~~~~~~~~~~
		/// @param nFlag The window flag whose value will be changed.
		/// @param bValue The value that will be assigned to the flag.
		///
		/* 7Ch */	virtual void SetFlag(WindowFlags nFlag, bool bValue) = 0;  // sets property EEC1B000 ?
		
		///
		/// Assigns the text contents or title of the window. This value might be used or not depending on the implementation
		/// and type of window.
		/// @param pCaption The text to be used as caption.
		///
		/* 80h */	virtual void SetCaption(const char16_t* pCaption) = 0;

		///
		/// Sets the text font style ID used in this window. This value might be used or not depending on the implementation
		/// and type of window. This method will not update the current text font.
		/// @param styleID The ID of the text font to use.
		///
		/* 84h */	virtual void SetTextFontID(uint32_t styleID) = 0;
		/* 88h */	virtual void func34(int) = 0;
		/* 8Ch */	virtual void func35(int) = 0;
		/* 90h */	virtual int Invalidate() = 0;  // sets needs repaint?

		///
		/// Updates the real area of this window and all its children, using the 'area' property and applying all the ILayoutStyle
		/// objects (added as IWinProc) in this window.
		///
		/* 94h */	virtual void Revalidate() = 0;
		/* 98h */	virtual int InvalidateTransform() = 0;
		/* 9Ch */	virtual int func39() = 0;
		/* A0h */	virtual int func40() = 0;
		
		///
		/// Returns the fill color of this window. The fill color acts as a background color: when rendering the window,
		/// the area will be filled with the fill color and then the fill drawable will be drawn on top of it.
		/// @returns The integer color representation of the value of the 'fillColor' property.
		///
		/* A4h */	virtual Math::Color GetFillColor() const = 0;
		
		///
		/// Returns the fill drawable of this window. When rendering the window,
		/// the area will be filled with the fill color and then the fill drawable will be drawn on top of it.
		/// @returns The drawable used in this window.
		///
		/* A8h */	virtual IDrawable* GetDrawable() const = 0;
		
		///
		/// Sets the fill color of this window. The fill color acts as a background color: when rendering the window,
		/// the area will be filled with the fill color and then the fill drawable will be drawn on top of it.
		/// @param color The color to use as the 'fillColor' property.
		///
		/* ACh */	virtual void SetFillColor(Math::Color color) = 0;

		///
		/// Sets the fill drawable of this window. When rendering the window,
		/// the area will be filled with the fill color and then the fill drawable will be drawn on top of it.
		///
		/* B0h */	virtual void SetDrawable(IDrawable* drawable) = 0;

		/* B4h */	virtual int func45(int) = 0;
		/* B8h */	virtual int func46(int, int) = 0;
		/* BCh */	virtual bool ContainsPoint(struct Math::Point localCoords) = 0;
		/* C0h */	virtual Math::Point ToGlobalCoordinates(struct Math::Point localCoords) = 0;
		/* C4h */	virtual Math::Point ToLocalCoordinates(struct Math::Point globalPos) = 0;
		/* C8h */	virtual bool ToLocalCoordinates2(struct Math::Point globalPos, Math::Point& dstLocal) = 0;

		///
		/// Returns the begin iterator of the list of children windows contained in this window. 
		/// Pair it with GetChildrenEnd() to iterate through the children.
		/// Children windows are listed according to their Z-index; that is, the first children is the one on front, and the last 
		/// children is the one on the bottom.
		///
		// If we make them const, it returns const_iterator and we can't modify the children
		/* CCh */	virtual IWindowList_t::iterator GetChildrenBegin() = 0;

		///
		/// Returns the end iterator of the list of children windows contained in this window. 
		/// Pair it with GetChildrenBegin() to iterate through the children.
		/// Children windows are listed according to their Z-index; that is, the first children is the one on front, and the last 
		/// children is the one on the bottom.
		///
		// If we make them const, it returns const_iterator and we can't modify the children
		/* D0h */	virtual IWindowList_t::iterator GetChildrenEnd() = 0;

		///
		/// Converts a pointer to a child window in the list back to an iterator, or returns end() if it is not part of the children list.
		/// This can be used to check if a window is a direct child of this window, using "LocateChild(pChild) != GetChildrenEnd()
		/// @param pChild The IWindow whose next sibling will be returned.
		/// @returns The iterator to the next sibling of pChild.
		///
		/* D4h */	virtual IWindowList_t::iterator LocateChild(const IWindow* pChild) const = 0;

		///
		/// Adds the given window to this IWindow's children. The window will be added last, so it will have the lowest Z-index.
		/// The parent of pWindow will be set to this object.
		/// @param pWindow The window to add to this object's children.
		///
		/* D8h */	virtual void AddWindow(IWindow* pWindow) = 0;

		///
		/// Removes the given window from this IWindow's children. pWindow will be removed from its parent hierarchy even if
		/// its parent is not this object.
		/// The parent of pWindow will be set to nullptr.
		/// @param pWindow The window to remove from this object's children.
		///
		/* DCh */	virtual void RemoveWindow(IWindow* pWindow) = 0;

		///
		/// Disposes the given window and all its hierarchy. If pChildWindow is a child of this window, it will be removed from it.
		/// The pChildWindow hierarchy will be disposed even if it is not a child of this window.
		/// @param pChildWindow The IWindow to dispose.
		///
		/* E0h */	virtual void DisposeWindowFamily(IWindow* pChildWindow) = 0;

		///
		/// Disposes all the children windows and all their hierarchy. After this method is called, this window will not have any children.
		///
		///
		/* E4h */	virtual void DisposeAllWindowFamilies() = 0;

		///
		/// Moves the specified child window at the front of the rest of its siblings, so it is the last one to be rendered.
		/// This is the equivalent to setting the Z-index to the highest. Note that the window will remain behind of windows
		/// with the flag kWinFlagAlwaysInFront set to true.
		/// @param pWindow The child window to bring to the front.
		///
		/* E8h */	virtual void BringToFront(IWindow* pWindow) = 0;

		///
		/// Moves the specified child window at the back of the rest of its siblings, so it is the first one to be rendered.
		/// This is the equivalent to setting the Z-index to the lowest. Note that the window will remain behind of windows
		/// with the flag kWinFlagAlwaysInFront set to true.
		/// @param pWindow The child window to send to the back.
		///
		/* ECh */	virtual void SendToBack(IWindow* pWindow) = 0;

		///
		/// Returns the first child window that has the given controlID. By default, this also checks on the children' children,
		/// so the controlID is searched in all the window hierarchy.
		/// @param controlID The controlID of the window to find.
		/// @param bRecursive Whether the children hierarchy should be checked as well, true by default.
		/// @returns The first window in the hierarchy that has the given controlID, or nullptr if there is no match.
		///
		/* F0h */	virtual IWindow* FindWindowByID(uint32_t controlID, bool bRecursive = true) = 0;

		///
		/// Returns the first child window that has the given controlID and is of the given type.
		/// The type is something like WinButton::TYPE, so it is safe to assume that the returned type will be a WinButton in this case.
		/// If a window with the given controlID is found but calling Cast(type) on it returns nullptr, nullptr will be returned
		/// (so it will stop searching).
		/// By default, this also checks on the children' children, so the controlID is searched in all the window hierarchy.
		/// @param controlID The controlID of the window to find.
		/// @param type The type of the window to find. It will be used calling Cast(type) on the match.
		/// @param bRecursive Whether the children hierarchy should be checked as well, true by default.
		/// @returns The first window in the hierarchy that has the given controlID and type, or nullptr if there is no match.
		///
		/* F4h */	virtual IWindow* FindWindowTypeByID(uint32_t controlID, uint32_t type, bool bRecursive = true) = 0;

		///
		/// Checks if the given window is contained in the component hierarchy of this IWindow.
		/// All the hierarchy will be checked, so the function can return true even if this window is not a direct parent
		/// of pChildWindow.
		/// @param pChildWindow The child window to check.
		/// @returns True if pChildWindow is contained in the hierarchy of this window, false otherwise.
		///
		/* F8h */	virtual bool IsAncestorOf(const IWindow* pChildWindow) = 0;

		/* FCh */	virtual bool func63(int index) = 0;
		/* 100h */	virtual bool func64(int index) = 0;

		///
		/// Adds the given IWinProc at the end of this window's list. IWinProcs are called when a message is received in the window.
		/// Also some of them might be called on layout-related methods. Some IWinProcs can also act as effects.
		/// @param pWinProc The IWinProc to add.
		///
		/* 104h */	virtual void AddWinProc(IWinProc* pWinProc) = 0;

		///
		/// Removes the given IWinProc from this window's list. IWinProcs are called when a message is received in the window.
		/// Also some of them might be called on layout-related methods. Some IWinProcs can also act as effects.
		/// @param pWinProc The IWinProc to remove from this window.
		///
		/* 108h */	virtual void RemoveWinProc(IWinProc* pWinProc) = 0;

		///
		/// Gets the IWinProc in this window that follows the given procedure. If pWinProc is not included in this window, 
		/// nullptr will be returned. If pWinProc is nullptr, the first IWinProc in this window will be returned.
		/// @param pWinProc The IWinProc that comes after this one will be returned. nullptr to return the first one.
		/// @returns The next IWinProc, or nullptr if there's none.
		///
		/* 10Ch */	virtual IWinProc* GetNextWinProc(const IWinProc* pWinProc = nullptr) const = 0;  // returns the IWinProc* that comes after the given one (pass nullptr to get the first IWinProc)

		/* 110h */	virtual int func68(int) = 0;

		///
		/// Sends the given message through this window, using this window as the source.
		/// @param msg The message.
		/// @returns True if the message was handled successfully.
		///
		/* 114h */	virtual bool SendMsg(Message& msg) = 0;

		///
		/// Returns the name of this component type (e.g. "Window", "WinButton").
		///
		/* 118h */	virtual const char* GetComponentName() const = 0;
		

		///
		/// Returns an structure that allows to iterate through the children of this window. Example usage:
		/// ~~~~~~~~~~~~~~~~~~~~{.cpp}
		/// IWindow* pWindow = ...;
		///
		/// for (IWindow* pChild : children())
		/// {
		///		...
		/// }
		/// ~~~~~~~~~~~~~~~~~~~~
		///
		WindowChildren children();

		///
		/// Returns an structure that allows to iterate through the IWinProc objects of this window. Example usage:
		/// ~~~~~~~~~~~~~~~~~~~~{.cpp}
		/// IWindow* pWindow = ...;
		///
		/// for (IWinProc* pProcedure : pWindow->procedures())
		/// {
		///		...
		/// }
		/// ~~~~~~~~~~~~~~~~~~~~
		///
		WindowProcedures procedures();

		///
		/// Adds an event listener, defined using a lambda function or by referencing a static function. 
		/// This listener will be called for the messages that are accepted by the event flags given; by default, this listens
		/// to basic input events and advanced events, defined by the kEventFlagBasicInput | kEventFlagAdvanced flags.
		/// The priority can also be specified, with 0 being default priority.
		///
		/// The method returns an IWinProc that can be used to remove this listener, by using IWindow::RemoveWinProc();
		/// @param function The lambda function that is called when a message is received.
		/// @param eventFlags [Optional] A combination of kEventFlag... that defines which messages are received.
		/// @param priority [Optional] The priority of this event listener.
		/// @returns The generated IWinProc object, that can be used to remove this listener.
		///
		eastl::intrusive_ptr<IWinProc> AddWinProc(HandleUILambda_t pFunction, int eventFlags = kEventFlagBasicInput | kEventFlagAdvanced, int priority = 0);

		///
		/// Adds an even listener that only handles the specified message types. The listener is defined using a lambda function
		/// or by referencing a static function. This listener will be called for the specified message types.
		/// The priority can also be specified, with 0 being default priority.
		///
		/// The method returns an IWinProc that can be used to remove this listener, by using IWindow::RemoveWinProc();
		/// @param function The lambda function that is called when a message is received.
		/// @param types A vector of message types that this procedure receives.
		/// @param priority [Optional] The priority of this event listener.
		/// @returns The generated IWinProc object, that can be used to remove this listener.
		eastl::intrusive_ptr<IWinProc> AddWinProcFilter(HandleUILambda_t function, const eastl::vector<MessageType> types, int priority = 0);

		///
		/// Tells whether the window is visible. This is equivalent to GetFlags() & kWinFlagVisible.
		///
		inline bool IsVisible() const
		{
			return GetFlags() & kWinFlagVisible;
		}
		///
		/// Switches the visibility of this window. This is equivalent to SetFlag(kWinFlagVisible, bVisible).
		///
		inline void SetVisible(bool bVisible)
		{
			SetFlag(kWinFlagVisible, bVisible);
		}

		///
		/// Tells whether the window is visible. This is equivalent to GetFlags() & kWinFlagEnabled.
		///
		inline bool IsEnabled() const
		{
			return GetFlags() & kWinFlagEnabled;
		}
		///
		/// Switches the visibility of this window. This is equivalent to SetFlag(kWinFlagEnabled, bEnabled).
		///
		inline void SetEnabled(bool bEnabled)
		{
			SetFlag(kWinFlagEnabled, bEnabled);
		}


		///
		/// Sets the given UTFWin::IWindow to fit the entire area of its parent.
		/// @param pWindow
		///
		static void FitParentArea(IWindow* pWindow);

		///
		/// Creates a new window with standard properties, and adds it to fit the given window (if any is given).
		/// The properties are the following:
		/// - ControlID = 0
		/// - CommandID = 0
		/// - ShadeColor = 0xFFFFFFFF
		/// - FillColor = 0x00FFFFFF
		/// - Area = (0, 0, 100, 100), except if a parent is given; then it fits the parent.
		/// - kWinFlagVisible = true
		/// - kWinFlagEnabled = true
		/// - kWinFlagIgnoreMouse = false
		/// @param pParent The parent window where the new window will be added. It can be nullptr.
		static IWindow* CreatePanel(IWindow* pParent);

		///
		/// Changes the opacity (opposite of transparency) of a window, which is done modifying the 'alpha' value of
		/// the shade color.
		/// @param pWindow The component whose opacity must be changed.
		/// @param fOpacity How opaque the window must be. This follows the rule alpha = 1 - fOpacity.
		///
		static void SetOpacity(IWindow* pWindow, float fOpacity);

		/// Executes a function for all the hierarchy of the given function. 
		/// The function must be static and take two parameters: the window for which it is being executed,
		/// and an optional parameter. It must return a boolean: if it returns false, the execution stops.
		/// This function is called "in-depth", that is, for a given child its whole hierarchy is executed
		/// before moving to the next child.
		/// @param pWindow The first window of the hierarchy, the method will be executed for it and its children.
		/// @param pFunction The function to execute
		/// @param parameter An optional parameter that is passed to the window
		static void ExecuteHierarchy(IWindow* pWindow, bool(*pFunction)(IWindow*, void*), void* parameter = nullptr);

		/// Adds the given procedure to all the hierarchy of the given window, inclusive.
		/// This is done by calling ExecuteHierarchy().
		/// @param pWindow The first window of the hierarchy, the procedure will be added for it and its children.
		/// @param pWinProc The procedure to add.
		static void AddWinProcHierarchy(IWindow* pWindow, IWinProc* pWinProc);

		/// Removes the given procedure from all the hierarchy of the given window, inclusive.
		/// This is done by calling ExecuteHierarchy().
		/// @param pWindow The first window of the hierarchy, the procedure will be removed from it and its children.
		/// @param pWinProc The procedure to remove.
		static void RemoveWinProcHierarchy(IWindow* pWindow, IWinProc* pWinProc);
	};

}

