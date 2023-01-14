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
#include <Spore\ArgScript\FormatParser.h>

#include <EASTL\functional.h>

namespace ArgScript
{

	class LambdaParser : public IParser
	{
	public:
		LambdaParser(ParseLine_t pParseLine);
		LambdaParser(ParseLine_t pParseLine, GetDescription_t pGetDescription);
		LambdaParser(ParseLine_t pParseLine, SetData_t pSetData);

		virtual void ParseLine(const Line& line) override;
		virtual const char* GetDescription(DescriptionMode mode) const override;
		virtual void SetData(FormatParser* pFormatParser, void* pData) override;

	protected:
		ParseLine_t mpParseLine;
		GetDescription_t mpGetDescription;
		SetData_t mpSetData;
	};
}
