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

#include <EASTL\vector.h>
#include <EASTL\fixed_vector.h>
#include <Spore\Graphics\IRenderable.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Object.h>
#include <Spore\UI\cSPUILayeredObject.h>

namespace UI 
{
	using namespace Graphics;

	class cLayerManager 
		: public IRenderable
		, DefaultRefCounted
	{
	public:
		enum {
			/// Message sent when the layer rendering starts (with parameter bool=true) and when it finishes (with parameter bool=false)
			kLayerRender = 0x24E5E7F
		};
	
	public:
		/* 0Ch */	vector<intrusive_ptr<cSPUILayeredObject>> mLayeredObjects;
		/* 20h */	vector<intrusive_ptr<DefaultRefCounted>> field_20;
		/* 34h */	bool field_34;
		/* 38h */	int field_38;  // -1
		/* 3Ch */	intrusive_ptr<Object> field_3C;
		/* 40h */	fixed_vector<intrusive_ptr<IModelWorld>, 15> field_40;
		/* 94h */	bool field_94;

	public:
		static cLayerManager* Get();
	};

	inline cLayerManager* LayerManager() {
		return cLayerManager::Get();
	}

	static_assert(sizeof(cLayerManager) == 0x98, "sizeof() != 98h");

	namespace Addresses(cLayerManager) {
		DeclareAddress(Get, SelectAddress(0x67CC20,, 0x67CA90));
	}
}