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
#include <Spore\ArgScript\Line.h>
#include <Spore\Internal.h>

#define IParserPtr intrusive_ptr<ArgScript::IParser>

namespace ArgScript
{

	///
	/// This interface represents a command or block that can be parsed in ArgScript. Parsers are mapped to keywords using the
	/// FormatParser::AddParser() method.
	///
	class IParser
	{
	public:
		IParser();

		/* 00h */	virtual void ParseLine(const Line& line) = 0;

		///
		/// Returns a basic or complete description of what this parser does. This usually includes information about
		/// how to use it, i.e. the arguments required, possible options, etc
		/// @param mode Whether the basic or complete description must be returned, in the DescriptionMode enum.
		///
		/* 04h */	virtual const char* GetDescription(DescriptionMode mode = DescriptionMode::Basic) const;

		///
		/// Sets the data and FormatParser of this parser. This method is called when FormatParser::AddParser() or IBlock::AddParser()
		/// are used.
		///
		/* 08h */	virtual void SetData(FormatParser* pFormatParser, void* pData) = 0;

		/* 0Ch */	virtual int AddRef();
		/* 10h */	virtual int Release();

	protected:
		/* 04h */	FormatParser* mpFormatParser;
		/* 08h */	int mnRefCount;
		/* 0Ch */	void* mpData;

	};
}
