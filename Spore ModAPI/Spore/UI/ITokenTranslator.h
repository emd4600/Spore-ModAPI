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

#include <Spore\Object.h>
#include <EASTL\string.h>

#define IUITokenTranslatorPtr eastl::intrusive_ptr<UI::ITokenTranslator>

namespace UI
{
	class ITokenTranslator
		: public DefaultRefCounted
	{
	public:
		virtual bool TranslateToken(uint32_t tokenID, eastl::string16& dst) = 0;
		virtual void func14h(int) = 0;
	};
}