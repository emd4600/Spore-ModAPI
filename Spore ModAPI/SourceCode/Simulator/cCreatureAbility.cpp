#ifndef MODAPI_DLL_EXPORT
/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\Simulator\cCreatureAbility.h>

namespace Simulator
{
	auto_STATIC_METHOD(cCreatureAbility, bool, Parse,
		Args(cCreatureAbility* arg0, App::PropertyList* arg1),
		Args(arg0, arg1));

	auto_METHOD(cCreatureAbility, uint32_t, GetAnimationID, Args(int index), Args(index));
}
#endif
