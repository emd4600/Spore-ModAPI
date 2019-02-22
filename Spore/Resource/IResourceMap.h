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

#include <Spore\Resource\IResourceContainer.h>
#include <Spore\Resource\ResourceObject.h>

#include <EASTL\intrusive_ptr.h>

using namespace eastl;

namespace Resource
{
	///
	/// An interface that is used to store resources in the cache.
	///
	class IResourceMap : public IResourceContainer
	{
	public:
		/* 0Ch */	virtual uint32_t GetType() = 0;
		/* 10h */	virtual int func10h() = 0;
		/* 14h */	virtual void func14h(int) = 0;
		/* 18h */	virtual bool GetResource(ResourceKey& key, intrusive_ptr<ResourceObject>* dst = nullptr) = 0;
		/* 1Ch */	virtual bool func1Ch(int, int) = 0;
		/* 20h */	virtual bool func20h(int) = 0;
		/* 24h */	virtual size_t func24h(int, int) = 0;
		/* 28h */	virtual void func28h(SpecialResourceObject*) = 0;
	};
}