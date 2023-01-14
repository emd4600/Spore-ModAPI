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
#include <Spore\Resource\IKeyFilter.h>
#include <EASTL\intrusive_ptr.h>
#include <EASTL\list.h>

namespace Resource
{
	/// An interface that is used to cache loaded resources for fast access.
	class ICache
	{
	public:
		/* 00h */	virtual ~ICache() = 0;
		/* 04h */	virtual bool Initialize() = 0;
		/* 08h */	virtual bool Dispose() = 0;
		/* 0Ch */	virtual uint32_t GetCacheType() = 0;
		/* 10h */	virtual IKeyFilter* GetKeyFilter() = 0;
		/* 14h */	virtual void SetKeyFilter(IKeyFilter* filter) = 0;
		/* 18h */	virtual bool GetResource(ResourceKey& key, ResourceObjectPtr* dst = nullptr) = 0;
		/* 1Ch */	virtual bool CacheResource(ResourceObject* resource, bool) = 0;
		/* 20h */	virtual bool CanCacheResource(ResourceObject* resource) = 0;
		/* 24h */	virtual size_t GetResourceList(eastl::list<ResourceObjectPtr>& dst, IKeyFilter* filter) = 0;
		/* 28h */	virtual void Flush(IKeyFilter* filter) = 0;
	};
}