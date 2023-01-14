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
#include <EASTL\intrusive_ptr.h>

#define cTerrainMapPtr eastl::intrusive_ptr<Terrain::cTerrainMap>

namespace Terrain
{
	class cTerrainMap
	{
	public:
		cTerrainMap();
		virtual ~cTerrainMap() {};
		virtual void* GetData() = 0;

		int AddRef();
		int Release();

	protected:
		/* 04h */	int mnRefCount;

	public:
		/* 08h */	int size;
		/* 0Ch */	int field_0C;
	};
	ASSERT_SIZE(cTerrainMap, 0x10);

	class cTerrainMap16
		: public cTerrainMap
	{
	public:
		cTerrainMap16();
		virtual ~cTerrainMap16() {}
		virtual void* GetData() override;

		/* 10h */	eastl::vector<uint16_t> data;
	};
	class cTerrainMap32
		: public cTerrainMap
	{
	public:
		cTerrainMap32();
		virtual ~cTerrainMap32() {}
		virtual void* GetData() override;

		/* 10h */	eastl::vector<uint32_t> data;
	};
}