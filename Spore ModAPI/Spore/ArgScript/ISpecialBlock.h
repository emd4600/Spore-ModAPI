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

#include <Spore\ArgScript\IParser.h>

#define ISpecialBlockPtr intrusive_ptr<ArgScript::ISpecialBlock>

namespace ArgScript
{
	///
	/// This is a special kind of block that can process every line individually, and that uses its own end keywords.
	/// Unlike IBlock objects, ISpecialBlock cannot have its own parsers. Also, ISpecialBlock does not end when the 'end'
	/// keyword is reached; instead, the end keyword must be specified in the FormatParser::AddSpecialBlock() method.
	///
	/// A good example of the use of special blocks are conditionals: in the ISpecialBlock::OnLine() event, we can decide 
	/// which lines get parsed and executed (the ones inside the condition met), and which don't, as well as detect special lines
	/// (for example, 'else'). 
	///
	class ISpecialBlock : public IParser
	{
	public:
		virtual void SetData(FormatParser* pFormatParser, void* pData) override;

		///
		/// A method caled every time a line is read inside this block.
		/// If the method returns true, the line will be considered processed and it won't be parsed
		/// like it normally would.
		/// @param lineText The text of the line.
		/// @returns Whether the line was processed or not.
		///
		virtual bool OnLine(LexerString& lineText) = 0;

		///
		/// Method called when an end keyword is reached. For special blocks, end keywords are not 'end';
		/// instead, they must be explictly specified using the FormatParser::AddSpecialBlock() method.
		///
		virtual void OnEndReached(int) = 0;

		virtual ~ISpecialBlock() {};
	};
}