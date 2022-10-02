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

#include <Spore\ArgScript\ASDeclarations.h>
#include <Spore\Internal.h>

#include <EASTL\hash_map.h>
#include <EASTL\string.h>

using namespace eastl;

namespace ArgScript
{
	///
	/// This class is used to read and process expressions in ArgScript. It contains a map of functions that can
	/// be used on expressions (for example, one could have 'sin', 'cos', etc).
	///
	class Lexer
	{
	public:
		///
		/// Adds a function to this lexer, that will be used when processing expresions.
		/// @param pFunctionName The name that will be used to call the function.
		/// @param pFuncion The IFunction that gets executed when the function is called.
		///
		void AddFunction(const char* pFunctionName, IFunction* pFunction);

		///
		/// Reads one character in the lexer string, which is expected to be the one specified. If it is not, 
		/// an exception is thrown.
		/// @throws ArgScriptException If the current character in the string is not the one required.
		/// @param lexerString The string pointer where the character will be read.
		/// @param c The character expected.
		///
		void ExpectChar(LexerString& lexerString, char c);

		/// 
		/// Reads one character in the lexer string, only if the end of the string has not been reached.
		/// The character is expected to be the one specified, otherwise an exception is thrown.
		/// @throws ArgScriptException If the current character in the string is not the one required.
		/// @param lexerString The string pointer where the character will be read.
		/// @param c The character expected.
		/// @returns True if the character was read, false if the end of the string was reached.
		bool OptionalExpectChar(LexerString& lexerString, char c);

		///
		/// Reads the next parameter in the string, which is all the characters until a comma, a space, or a closing parenthesis is found.
		/// A parameter can also be surrounded by parenthesis.
		/// @throws ArgScriptException If the format is incorrect (i.e. '(' with no ')', '"' with no closing '"', etc).
		///
		void NextParameter(LexerString& lexerString, string& dst);

	protected:
		hash_map<string, IFunction*> mFunctions;
	};

	namespace Addresses(Lexer)
	{
		DeclareAddress(AddFunction);
		DeclareAddress(ExpectChar);
		DeclareAddress(OptionalExpectChar);
		DeclareAddress(NextParameter);
	}
}