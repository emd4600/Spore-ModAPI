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

#include <Spore\ResourceKey.h>
#include <Spore\Simulator\cScenarioAsset.h>

namespace Simulator
{
	class cScenarioPosseMember
	{
	public:
		/* 00h */	cScenarioAsset mAsset;
		/* 20h */	bool mbIsLocked;
		/* 24h */	ResourceKey mAssetKeyDEPRECATED;
		/* 30h */	uint64_t mServerIDDEPRECATED;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cScenarioPosseMember) == 0x38, "sizeof(cScenarioPosseMember) != 0x38");
}