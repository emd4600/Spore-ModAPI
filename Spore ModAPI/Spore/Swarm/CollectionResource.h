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

#include <Spore\Resource\ResourceObject.h>
#include <Spore\Swarm\EffectDirectory.h>

#define CollectionResourcePtr eastl::intrusive_ptr<Swarm::CollectionResource>

namespace Swarm
{
	///
	/// A Resource object used to retrieve an effect collection (that is, an EffectDirectory, .effdir file).
	///
	class CollectionResource : public Resource::ResourceObject
	{
	public:
		EffectDirectory* GetCollection();

	protected:
		/* 14h */	intrusive_ptr<EffectDirectory> mpCollection;
	};

	static_assert(sizeof(CollectionResource) == 0x18, "sizeof(CollectionResource) != 18h");

	inline EffectDirectory* CollectionResource::GetCollection()
	{
		return mpCollection.get();
	}
}