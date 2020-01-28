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

#include <Spore\ArgScript\FormatParser.h>
#include <Spore\ArgScript\Lexer.h>

namespace ArgScript
{
	///
	/// Represents an ArgScript function. These functions can return bool, float or int values, and can receive any quantity of
	/// parameters. The parameters must be separated and processed inside the function. 
	///
	class IFunction
	{
	public:
		///
		/// Calls this function expecting a float value to be returned. 
		/// The received string contains the arguments with no processing, with the parenthesis included; 
		/// the variables are replaced, however. 
		/// Boolean functions might throw an exception here.
		/// @param ppString The string that contains the parameters, for example '(1.0, "Vista")'.
		/// @param lexer The lexer that can be used for parsing the parameters.
		///
		/* 00h */	virtual float GetFloat(LexerString& ppString, Lexer& lexer) = 0;

		///
		/// Calls this function expecting an int value to be returned. 
		/// The received string contains the arguments with no processing, with the parenthesis included; 
		/// the variables are replaced, however. 
		/// Boolean functions can use this function as well, returning 1 for true and 0 for false.
		/// @param ppString The string that contains the parameters, for example '(1.0, "Vista")'.
		/// @param lexer The lexer that can be used for parsing the parameters.
		///
		/* 04h */	virtual int GetInt(LexerString& ppString, Lexer& lexer) = 0;

		///
		/// Calls this function expecting a bool value to be returned. 
		/// The received string contains the arguments with no processing, with the parenthesis included; 
		/// the variables are replaced, however. 
		/// @param ppString The string that contains the parameters, for example '(1.0, "Vista")'.
		/// @param lexer The lexer that can be used for parsing the parameters.
		///
		/* 08h */	virtual bool GetBool(LexerString& ppString, Lexer& lexer) { return GetInt(ppString, lexer) == 0 ? false : true; };

		///
		/// Returns a basic or complete description of what this function does. This usually includes information about
		/// how to use it, i.e. the arguments required.
		/// @param mode Whether the basic or complete description must be returned, in the DescriptionMode enum.
		///
		/* 0Ch */	virtual const char* GetDescription(DescriptionMode mode = DescriptionMode::Basic) const { return nullptr; };
	};
}