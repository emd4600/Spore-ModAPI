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

#include <Spore\Internal.h>

#include <EASTL\vector.h>

using namespace eastl;

namespace ArgScript
{
	///
	/// A key-value pair (c-string, int) in an enumeration.
	///
	typedef pair<const char*, int> EnumValue;

	///
	/// An array of c-strings that are the arguments of a line or an option.
	///
	typedef const char* const* Arguments;

	///
	/// An option of an ArgScript line. Option keywords are preceded with a '-'. Options can have none or multiple arguments;
	/// if it has no arguments, it is considered a 'flag'.
	///
	struct LineOption {
		char**	mpStrings;
		size_t	mnFirstArgument;
		size_t	mnArgumentCount;
		bool	mbIsFlag;
	};

	///
	/// This class represents a line of ArgScript data. A line is made up by a keyword, multiple or none arguments, and multiple or 
	/// none options. For example: "keyword argument1 argument2 -option1 -option2 optionArgument".
	/// All the elements in a line are separated by whitespaces; string literals that require whitespaces can be surrounded by "" or ().
	/// The first element is always considered the keyword; the words that follow it are arguments. If a word is preceded by '-',
	/// it is considered an option (for example, the option "-scale 1.2"). Options can be followed by arguments; if an option does
	/// not have any argument, it is considered a 'flag'.
	///
	class Line
	{
	public:

		static const size_t kMaxInt = 0x7FFFFFFF;

		Line();
		Line(const char* pText);

		///
		/// Separates the given text into the arguments and options that form the line.
		/// By default, the keyword is considered as an argument; use the RemoveKeyword() method to change it.
		///
		void FromString(const char* pText);

		///
		/// Removes the keyword (the first argument) from this line.
		///
		void RemoveKeyword();

		///
		/// Gets the specified number of arguments from this line.
		/// This does not include the keyword.
		/// If the number of arguments is not equal to the one required, an exception will be thrown.
		/// @param nCount The number of arguments this line must have.
		/// @returns An array of char* strings.
		///
		Arguments GetArguments(size_t nCount) const;

		///
		/// Gets the arguments from this line, which must be in the specified range.
		/// This does not include the keyword.
		/// If the number of arguments is less than nMin, or greater than nMax, an exception will be thrown.
		/// The number of arguments is returned in the parameter dstCount.
		/// @param dstCount The destination size_t where the number of arguments got will be written, or nullptr.
		/// @param nMin The minimum number of arguments this line can have.
		/// @param nMax The maximum number of arguments this line can have.
		/// @returns An array of char* strings.
		///
		Arguments GetArgumentsRange(size_t* dstCount, size_t nMin, size_t nMax = kMaxInt) const;

		///
		/// Gets the number of arguments this line contains. This does not include the keyword.
		///
		size_t GetArgumentsCount() const;

		///
		/// Gets the argument at the given index.
		/// @param nIndex The index of the argument.
		///
		const char* GetArgumentAt(size_t nIndex) const;


		///
		/// Gets the specified number of arguments from an option with the given name.
		/// Options are optional values, which are set prefixing the option name with a '-', for example '-scale 2'.
		/// This does not include the keyword.
		/// If the number of arguments is not equal to the one required, an exception will be thrown.
		/// @param pOptionName The name of the option. In the line, it must be prefixed with a '-'.
		/// @param nCount The number of arguments this line must have.
		/// @returns An array of char* strings.
		///
		Arguments GetOption(const char* pOptionName, size_t nCount) const;

		///
		/// Gets the arguments from an option with the given name, which must be in the specified range.
		/// Options are optional values, which are set prefixing the option name with a '-', for example '-scale 2'.
		/// This does not include the keyword.
		/// If the number of arguments is less than nMin, or greater than nMax, an exception will be thrown.
		/// The number of arguments is returned in the parameter dstCount.
		/// @param pOptionName The name of the option. In the line, it must be prefixed with a '-'.
		/// @param dstCount The destination size_t where the number of arguments got will be written, or nullptr.
		/// @param nMin The minimum number of arguments this line can have.
		/// @param nMax The maximum number of arguments this line can have.
		/// @returns An array of char* strings.
		///
		Arguments GetOptionRange(const char* pOptionName, size_t* dstCount, size_t nMin, size_t nMax = kMaxInt) const;

		///
		/// Tells whether the line contains the given flag or not. A flag is an option with no values.
		/// @param pFlagName The name of the flag. In the line, it must be prefixed with a '-'.
		///
		bool HasFlag(const char* pFlagName) const;


		///
		/// Gets the integer value that corresponds to the given string in the specified enum.
		/// If the enum does not have any value assigned to that string, an exception will be thrown.
		/// @param pValueString The string value of the enumeration.
		/// @param pEnum An array of pair<const char*, int> objects where the values will be checked.
		/// @returns The integer value assigned to that enumeration.
		///
		static int GetEnum(const char* pValueString, const EnumValue* pEnum);

		///
		/// Gets the integer value that corresponds to the given string in the specified enum.
		/// This method does not throw an exception if the enumeration does not have any value assigned to that string.
		/// @param pValueString The string value of the enumeration.
		/// @param pEnum An array of pair<const char*, int> objects where the values will be checked.
		/// @param dst The integer where the value will be set. If no value is found, it won't be modified.
		/// @returns Whether a value was found or not.
		///
		static bool GetOptionalEnum(const char* pValueString, const EnumValue* pEnum, int& dst);


	protected:
		/* 00h */	vector<char*>		mStrings;
		/* 14h */	vector<char**>		mArguments;
		/* 28h */	vector<LineOption*> mOptions;

		/* 3Ch */	size_t mnFirstArgIndex;
		/* 40h */	size_t mnArgumentCount;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(Line), "sizeof(Line) != 44h");

	namespace InternalAddressList(Line)
	{
		DefineAddress(GetArgumentsRange, GetAddress(0x838880, 0x838080, 0x838100));
		DefineAddress(GetArguments, GetAddress(0x838B80, 0x838380, 0x838400));
		DefineAddress(GetArgumentAt, GetAddress(0x838780, 0x837F80, 0x838000));
		DefineAddress(GetArgumentsCount, GetAddress(0x838790, 0x837F90, 0x838010));

		DefineAddress(GetOption, GetAddress(0x838B90, 0x838390, 0x838410));
		DefineAddress(GetOptionRange, GetAddress(0x838990, 0x838190, 0x838210));
		DefineAddress(HasFlag, GetAddress(0x838910, 0x838110, 0x838190));

		DefineAddress(GetEnum, GetAddress(0x841470, 0x840C00, 0x840C80));
		DefineAddress(GetOptionalEnum, GetAddress(0x841080, 0x840810, 0x840890));

		DefineAddress(FromString, GetAddress(0x838C20, 0x838420, 0x8384A0));
	}
}
