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

#include <EASTL\vector_map.h>
#include "MaterialConfig.h"
#include "..\Spore\ArgScript\FormatParser.h"

using namespace eastl;

namespace ModAPI
{
	class MaterialParser
	{
	public:

		MaterialParser(ArgScript::FormatParser* formatParser);
		~MaterialParser();

	public:
		struct cmp_str
		{
			bool operator()(const char *a, const char *b) const
			{
				return std::strcmp(a, b) < 0;
			}
		};
		vector_map<const char*, intrusive_ptr<MaterialConfig>, cmp_str> mMaterials;
		ArgScript::FormatParser* mFormatParser;

		void ConfigureFormatParser();

	protected:
		//static std::map<const char*, int> states;
		static ArgScript::EnumValue states[];

		static int ParseState(ArgScript::FormatParser* formatParser, const char* state);
	};
}