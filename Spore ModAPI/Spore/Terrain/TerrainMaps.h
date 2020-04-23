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

#include <EASTL\intrusive_ptr.h>

#define cTerrainMapPtr eastl::intrusive_ptr<Terrain::cTerrainMap>

namespace Terrain
{
	class cTerrainMap
	{
	public:
		virtual ~cTerrainMap();
		virtual void* GetData();

		int AddRef();
		int Release();

	protected:
		int mnRefCount;
		char _padding[0x1C];
	};

	static_assert(sizeof(cTerrainMap) == 0x24, "sizeof(cTerrainMap) != 24h");

	inline int cTerrainMap::AddRef()
	{
		++mnRefCount;
		return mnRefCount;
	}
	inline int cTerrainMap::Release()
	{
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}
}