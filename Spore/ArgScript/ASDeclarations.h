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

#include <EASTL\string.h>

namespace ArgScript
{
	class FormatParser;
	class IParser;
	class ICommand;
	class IBlock;
	class ISpecialBlock;
	class IFunction;

	///
	/// A standard ArgScript exception, which is just a string.
	///
	typedef eastl::string& ArgScriptException;

	///
	/// The type of description required by 'GetDescription' functions; it can be either basic or complete.
	///
	enum DescriptionMode
	{
		kDescriptionBasic = 0,
		kDescriptionComplete = 1
	};

	typedef const char* LexerString;
}