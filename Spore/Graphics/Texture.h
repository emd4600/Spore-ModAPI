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

#include <Spore\RenderWare\Raster.h>
#include <Spore\ResourceKey.h>

#include <EASTL\intrusive_ptr.h>
#include <EASTL\vector.h>

using namespace eastl;
using RenderWare::Raster;

namespace Graphics
{
	class Texture
	{
	public:
		int AddRef();
		int Release();

	protected:
		/* 00h */	Raster* mpRaster;
		/* 04h */	int mnFlags;
		/* 08h */	int mnRefCount;   // ?
		/* 0Ch */	int field_0C;
		/* 10h */	ResourceKey mName;

	};

	typedef vector<intrusive_ptr<Texture>> TextureVector_t;

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	inline int Texture::AddRef()
	{
		return mnRefCount++;
	}
	inline int Texture::Release()
	{
		// for some reason, it does not delete itself
		if (mnRefCount-- < 1)
		{
			mnRefCount = 1;
		}

		return mnRefCount;
	}
}