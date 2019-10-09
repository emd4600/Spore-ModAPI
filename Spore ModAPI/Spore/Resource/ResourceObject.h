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

#include <Spore\Object.h>

namespace Resource
{
	///
	/// A type of object that is used as a resource. This object contains a ResourceKey used to identify it.
	///
	class ResourceObject : public Object
	{
	public:
		ResourceObject();

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t typeID) const override;
		virtual int GetReferenceCount();

		static const uint32_t TYPE = 0x2269ED1;

	protected:
		/* 04h */	int mnRefCount;
		/* 08h */	ResourceKey		mNameKey;
	};


	class SpecialResourceObject : public ResourceObject
	{
	public:
		SpecialResourceObject();

		virtual int AddRef();
		virtual int Release();
		virtual void* Cast(uint32_t typeID) const;
		virtual int GetReferenceCount();

		static const uint32_t TYPE = 0x355D6F5;

	protected:
		// I have no idea of what this is
		class Manager
		{
		public:
			virtual void Delete(ResourceObject* object) = 0;
		};

	protected:
		/* 14h */	Manager*		mpManager;
	};


	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	inline ResourceObject::ResourceObject()
		: mnRefCount(0)
		, mNameKey()
	{

	}

	inline SpecialResourceObject::SpecialResourceObject()
		: mpManager(nullptr)
	{

	}
}