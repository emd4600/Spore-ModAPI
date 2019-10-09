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

#include <Spore\UTFWin\UILayout.h>

namespace UTFWin
{
	UILayout::UILayout() :
		mResourceKey(),
		mpLayoutObjects(nullptr)
	{
	}

	auto_METHOD(UILayout, bool, Load,
		Args(const ResourceKey& name, bool arg_4, uint32_t arg_8),
		Args(name, arg_4, arg_8));

	auto_METHOD(UILayout, bool, LoadByName,
		Args(const wchar_t* name, uint32_t groupID, bool arg_4, uint32_t arg_8),
		Args(name, groupID, arg_4, arg_8));

	auto_METHOD(UILayout, IWindow*, FindWindowByID,
		Args(uint32_t name, bool recursive),
		Args(name, recursive));

	auto_METHOD(UILayout, bool, SetParentWindow,
		Args(IWindow* parent, bool arg_4, uint32_t arg_8),
		Args(parent, arg_4, arg_8));

	auto_METHOD(UILayout, bool, SetVisible, Args(bool value), Args(value));

	auto_METHOD_(UILayout, IWindow*, GetContainerWindow);
}