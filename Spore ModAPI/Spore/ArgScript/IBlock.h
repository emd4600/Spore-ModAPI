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

#include <EASTL\hash_map.h>
#include <EASTL\string.h>
#include <EASTL\intrusive_ptr.h>

#define IBlockPtr eastl::intrusive_ptr<ArgScript::IBlock>

using namespace eastl;

namespace ArgScript
{
	///
	/// This parser represents a block of ArgScript lines. A block begins when a line with the keyword is read, and it ends when a line
	/// with the reserved keyword 'end' is found. The lines inside the block will be read using the parsers contained inside this IBlock,
	/// or using the parsers in the FormatParser.
	///
	class IBlock : public IParser
	{
	public:
		IBlock();

		///
		/// Sets the data and FormatParser of this parser. For blocks, this should be used to add any necessary parsers,
		/// since it is called when the IBlock is added to a FormatParser or another block.
		///
		/* 08h */	virtual void SetData(FormatParser* formatParser, void* data) override;

		///
		/// Event called when the 'end' keyword is found, and therefore the block is finished.
		///
		/* 14h */	virtual void OnBlockEnd(bool arg_0) {};

		///
		/// Maps the given IParser to the specified keyword. When a line with that keyword is found inside this block,
		/// the IParser given will be used.
		///
		/* 18h */	virtual void AddParser(const char* pKeyword, IParser* pParser);

		///
		/// Gets the IParser that is mapped to the given keyword.
		/// @param pKeyword The keyword string.
		///
		/* 1Ch */	virtual IParser* GetParser(const char* pKeyword);

		virtual ~IBlock() {};

	protected:
		hash_map<string, intrusive_ptr<IParser>> mParsers;
		void* field_30;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(IBlock) == 0x34, "sizeof(IBlock) != 34h");

	inline void IBlock::SetData(FormatParser* formatParser, void* data)
	{
		this->mpData = data;
		this->field_30 = data;  // ?
		this->mpFormatParser = formatParser;
	}

	namespace Addresses(IBlock)
	{
		DeclareAddress(AddParser);
		DeclareAddress(GetParser);
	}
}
