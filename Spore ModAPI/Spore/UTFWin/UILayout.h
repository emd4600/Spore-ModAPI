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

#include <Spore\UTFWin\UILayoutObjects.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\ResourceKey.h>

#define UILayoutPtr eastl::intrusive_ptr<UTFWin::UILayout>

namespace UTFWin
{
	///
	/// An object used to load and contain user interfaces. An instance of this object can be used to load
	/// SPUI interfaces into the game UI. Example usage:
	/// ~~~~~~~~~~~~~~~~{.cpp}
	/// UILayout layout;
	/// layout.Load(u"EditorCameraUI");
	/// ~~~~~~~~~~~~~~~~
	///
	class UILayout : public DefaultRefCounted
	{
	public:
		UILayout();
		~UILayout();

		///
		/// Loads a user interface from a file. The user interface is expected to be in the SPUI format or an
		/// (undocumented) .xml format. A new IWindow will be created and added to the main window; the main windows
		/// of the user interface loaded will be added as children of that new container window.
		/// @param resourceKey The ResourceKey of the file that must be loaded. The groupID should be UILayout::kDefaultGroup, 
		/// and the typeID UILayout::kDefaultType.
		///
		bool Load(const ResourceKey& resourceKey, bool = true, uint32_t = kDefaultParameter);

		///
		/// An easier version of the UILayout::Load() method; this verison only requires the instance ID of the 
		/// layout file, although other parameters can be specified.
		///
		bool LoadByID(uint32_t instanceID, uint32_t groupID = kDefaultGroup, uint32_t typeID = kDefaultType, bool = true, uint32_t = kDefaultParameter);

		///
		/// Loads a user interface from a file. The user interface is expected to be in the SPUI format or an
		/// (undocumented) .xml format. A new IWindow will be created and added to the main window; the main windows
		/// of the user interface loaded will be added as children of that new container window.
		/// This method will just process the resource name and call UILayout::Load().
		/// @param pResourceName The name of the layour file (no extension or group needed).
		/// @param groupID [Optional] The ID of the group where the file is stored, usually UILayout::kDefaultGroup.
		///
		bool LoadByName(const char16_t* pLayoutName, uint32_t groupID = kDefaultGroup, bool = true, uint32_t = kDefaultParameter);

		///
		/// Returns the first child window that has the given controlID. By default, this also checks on the children' children,
		/// so the controlID is searched in all the window hierarchy.
		/// @param controlID The controlID of the window to find.
		/// @param bRecursive Whether the children hierarchy should be checked as well, true by default. If false, only the main
		/// windows will be checked.
		/// @returns The first window in the hierarchy that has the given controlID, or nullptr if there is no match.
		///
		IWindow* FindWindowByID(uint32_t controlID, bool bRecursive = true);
		
		// the two args are usually true, 05B598FA (kDefaultParameter)
		bool SetParentWindow(IWindow* pParent, bool = true, uint32_t = kDefaultParameter);

		///
		/// Switches the visibility of all the layout.
		/// @param value
		///
		bool SetVisible(bool value);

		///
		/// Returns the window that contains the UI layout.
		///
		IWindow* GetContainerWindow();



		enum
		{
			kDefaultGroup = 0x40464100,
			kDefaultType = 0x510A95B,
			kDefaultParameter = 0x5B598FA
		};

	protected:
		void Delete(int);

		/* 08h */	ResourceKey			mResourceKey;
		/* 14h */	UILayoutObjectsPtr	mpLayoutObjects;
	};
	ASSERT_SIZE(UILayout, 0x18);

	namespace Addresses(UILayout)
	{
		DeclareAddress(Delete);
		DeclareAddress(Load);
		DeclareAddress(LoadByName);

		DeclareAddress(FindWindowByID);

		DeclareAddress(SetParentWindow);
		DeclareAddress(SetVisible);
		DeclareAddress(GetContainerWindow);
	}

	inline bool	UILayout::LoadByID(uint32_t instanceID, uint32_t groupID, uint32_t typeID, bool arg1, uint32_t arg2)
	{
		return Load(ResourceKey(instanceID, typeID, groupID), arg1, arg2);
	}

}

