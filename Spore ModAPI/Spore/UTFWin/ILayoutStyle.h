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

#include <Spore\UTFWin\IWinProc.h>

namespace UTFWin
{
	///
	/// This class represents an object that can apply a certain layout to a given Rectangle area.
	/// Since this is used to apply layouts on windows, it has a method to convert this ILayoutStyle to a IWinProc, 
	/// that then can be added onto an IWindow.
	/// ILayoutStyle receives an area and a parent area, and transform the first accordingly.
	///
	class ILayoutStyle : public UTFWinObject
	{
	public:
		static const uint32_t TYPE = 0xCF3DF10B;


		///
		/// Returns the IWinProc representation of this ILayoutStyle, so that it can be used on an IWindow. 
		/// This is preferred to the Cast method.
		///
		/* 10h */	virtual IWinProc* ToWinProc() const = 0;

		///
		/// Applies this layout to the given area. The parent area of the window must also be specified as some layouts might use it;
		/// the resulting area will still be relative to the parent window position, however.
		/// @param[in, out] area The current area of the window. The result will be written here as well.
		/// @param[in] parentArea The area of the parent window, some layouts might use this. Even if this parameter
		/// is used, the resulting area will be relative to the parent window position.
		///
		/* 14h */	virtual void ApplyLayout(Math::Rectangle& area, const Math::Rectangle& parentArea) = 0;

		///
		/// Reverts this layout to the given area. The parent area of the window must also be specified as some layouts might use it;
		/// the resulting area will still be relative to the parent window position, however.
		/// This is the inverse of ApplyLayout().
		/// @param[in, out] area The current area of the window. The result will be written here as well.
		/// @param[in] parentArea The area of the parent window, some layouts might use this. Even if this parameter
		/// is used, the resulting area will be relative to the parent window position.
		/// @returns True if the layout was successfully reverted.
		///
		/* 18h */	virtual bool RevertLayout(Math::Rectangle& area, const Math::Rectangle& parentArea) = 0;

	};
}