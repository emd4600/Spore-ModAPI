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

#include <Spore\Graphics\ITextureManager.h>
#include <Spore\Object.h>
#include <Spore\Mutex.h>

#include <EASTL\intrusive_list.h>
#include <EASTL\hash_map.h>

namespace Graphics
{
	class TextureContainer 
		: public eastl::intrusive_list_node
		, public Texture
	{
	};

	///
	/// The implementation of ITextureManager; this should only be used for extending and detouring.
	///
	class cTextureManager 
		: public ITextureManager
		, public IVirtual
	{
	public:

		/* 08h */	int field_08;
		/* 0Ch */	bool field_0C;
		/* 10h */	RenderWare::Raster* mpDebugRaster;
		/* 14h */	RenderWare::Raster* mpLoadingRaster;
		/* 18h */	TexturePtr mpPlaceHolderNormalMap;
		/* 1Ch */	TexturePtr mpPlaceholderSpecGlossMap;
		/* 20h */	Mutex mTexturesMutex;
		/* 50h */	eastl::intrusive_list<TextureContainer> field_50;
		/* 58h */	eastl::hash_map<ResourceKey, TextureContainer*> mTextures;
		/* 78h */	eastl::hash_map<int, int> field_78;
		/* 98h */	Mutex field_98;
		/* C8h */	int field_C8;  // 0x0A
		/* CCh */	int mnMipLOD;
		/* D0h */	int field_D0;
		/* D4h */	//TODO: sub_7AC660 loadqueue
	};
}
