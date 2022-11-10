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

#include <Spore\Graphics\IModelManager.h>
#include <Spore\Object.h>

#include <EASTL\vector.h>
#include <EASTL\map.h>

namespace Graphics
{

	///
	/// The implementation of IModelManager; this should only be used for extending and detouring.
	///
	class cModelManager 
		: public IModelManager
		, public IVirtual
	{
	public:

	protected:
		/* 08h */	int mnRefCount;
		/* 0Ch */	eastl::map<uint32_t, IModelWorldPtr> mModelWorlds;
		/* 28h */	eastl::map<int, int> field_28;
		/* 44h */	int field_44;
		/* 48h */	ObjectPtr field_48;
		/* 4Ch */	eastl::vector<int> field_4C;
	};
	ASSERT_SIZE(cModelManager, 0x60);
}