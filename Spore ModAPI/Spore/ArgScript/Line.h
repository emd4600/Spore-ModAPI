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

namespace ArgScript
{
	///
	/// A key-value pair (c-eastl::string, int) in an enumeration.
	///
	typedef eastl::pair<const char*, int> EnumValue;

	///
	/// An array of c-eastl::strings that are the arguments of a line or an option.
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
	/// All the elements in a line are separated by whitespaces; eastl::string literals that require whitespaces can be surrounded by "" or ().
	/// The first element is always considered the keyword; the words that follow it are arguments. If a word is preceded by '-',
	/// it is considered an option (for example, the option "-scale 1.2"). Options can be followed by arguments; if an option does
	/// not have any argument, it is considered a 'flag'.
	///
	class Line
	{
	public:

		static const size_t kMaxInt = 0x7FFFFFFF;

		Line();
		Line(const char* text);

		///
		/// Separates the given text into the arguments and options that form the line.
		/// By default, the keyword is considered as an argument; use the RemoveKeyword() method to change it.
		///
		void FromString(const char* text);

		///
		/// Removes the keyword (the first argument) from this line.
		///
		void RemoveKeyword();

		///
		/// Gets the specified number of arguments from this line.
		/// This does not include the keyword.
		/// If the number of arguments is not equal to the one required, an exception will be thrown.
		/// @param count The number of arguments this line must have.
		/// @returns An array of char* eastl::strings.
		///
		Arguments GetArguments(size_t count) const;

		///
		/// Gets the arguments from this line, which must be in the specified range.
		/// This does not include the keyword.
		/// If the number of arguments is less than nMin, or greater than nMax, an exception will be thrown.
		/// The number of arguments is returned in the parameter dstCount.
		/// Usage example:
		/// ~~~~{.cpp}
		/// size_t count;
		/// auto args = line.GetArgumentsRange(&count, 1, kMaxInt);
		/// ~~~~
		///
		/// @param dstCount The destination size_t where the number of arguments got will be written, or nullptr.
		/// @param nMin The minimum number of arguments this line can have.
		/// @param nMax The maximum number of arguments this line can have.
		/// @returns An array of char* eastl::strings.
		///
		Arguments GetArgumentsRange(size_t* dstCount, size_t nMin, size_t nMax = kMaxInt) const;

		///
		/// Gets the number of arguments this line contains. This includes the keyword.
		///
		size_t GetArgumentsCount() const;

		///
		/// Gets the argument at the given index.
		/// @param index The index of the argument.
		///
		const char* GetArgumentAt(size_t index) const;


		///
		/// Gets the specified number of arguments from an option with the given name.
		/// Options are optional values, which are set prefixing the option name with a '-', for example '-scale 2'.
		/// This does not include the keyword.
		/// If the number of arguments is not equal to the one required, an exception will be thrown.
		/// @param optionName The name of the option. In the line, it must be prefixed with a '-'.
		/// @param count The number of arguments this line must have.
		/// @returns An array of char* eastl::strings.
		///
		Arguments GetOption(const char* optionName, size_t count) const;

		///
		/// Gets the arguments from an option with the given name, which must be in the specified range.
		/// Options are optional values, which are set prefixing the option name with a '-', for example '-scale 2'.
		/// This does not include the keyword.
		/// If the number of arguments is less than nMin, or greater than nMax, an exception will be thrown.
		/// The number of arguments is returned in the parameter dstCount.
		/// Usage example:
		/// ~~~~{.cpp}
		/// size_t count;
		/// auto args = line.GetOptionRange("option", &count, 1, kMaxInt);
		/// ~~~~
		///
		/// @param optionName The name of the option. In the line, it must be prefixed with a '-'.
		/// @param dstCount The destination size_t where the number of arguments got will be written, or nullptr.
		/// @param nMin The minimum number of arguments this line can have.
		/// @param nMax The maximum number of arguments this line can have.
		/// @returns An array of char* eastl::strings.
		///
		Arguments GetOptionRange(const char* optionName, size_t* dstCount, size_t nMin, size_t nMax = kMaxInt) const;

		///
		/// Tells whether the line contains the given flag or not. A flag is an option with no values.
		/// @param flagName The name of the flag. In the line, it must be prefixed with a '-'.
		///
		bool HasFlag(const char* flagName) const;


		///
		/// Gets the integer value that corresponds to the given eastl::string in the specified enum.
		/// If the enum does not have any value assigned to that eastl::string, an exception will be thrown.
		/// @param valueString The eastl::string value of the enumeration.
		/// @param pEnum An array of eastl::pair<const char*, int> objects where the values will be checked.
		/// @returns The integer value assigned to that enumeration.
		///
		static int GetEnum(const char* valueString, const EnumValue* pEnum);

		///
		/// Gets the integer value that corresponds to the given eastl::string in the specified enum.
		/// This method does not throw an exception if the enumeration does not have any value assigned to that eastl::string.
		/// @param valueString The eastl::string value of the enumeration.
		/// @param pEnum An array of eastl::pair<const char*, int> objects where the values will be checked.
		/// @param dst The integer where the value will be set. If no value is found, it won't be modified.
		/// @returns Whether a value was found or not.
		///
		static bool GetOptionalEnum(const char* valueString, const EnumValue* pEnum, int& dst);


	protected:
		/* 00h */	eastl::vector<char>		mBuffer;
		/* 14h */	eastl::vector<char*>		mArguments;
		/* 28h */	eastl::vector<LineOption>	mOptions;
		/* 3Ch */	size_t mFirstArgIndex;
		/* 40h */	size_t mArgumentCount;
	};
	ASSERT_SIZE(Line, 0x44);

	namespace Addresses(Line)
	{
		DeclareAddress(GetArgumentsRange);
		DeclareAddress(GetArguments);
		DeclareAddress(GetArgumentAt);
		DeclareAddress(GetArgumentsCount);

		DeclareAddress(GetOption);
		DeclareAddress(GetOptionRange);
		DeclareAddress(HasFlag);

		DeclareAddress(GetEnum);
		DeclareAddress(GetOptionalEnum);

		DeclareAddress(FromString);
	}
}
