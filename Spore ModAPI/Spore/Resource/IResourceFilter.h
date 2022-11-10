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
#include <Spore\ResourceKey.h>

namespace Resource
{
	///
	/// A generic interface used to filter ResourceKey objects. 
	///
	class IResourceFilter
	{
	public:
		virtual ~IResourceFilter() {};

		/// A method used to determine whether a file with this ResourceKey name is accepted.
		/// @param name
		/// @returns True if the file is accepted, false otherwise.
		virtual bool IsValid(const ResourceKey& name) = 0;
	};

	///
	/// The standard file filter which filters resources depending on the ResourceKey. 
	/// This filter accepts ResourceKey values if they match certain
	/// instanceIDs, typeIDs or groupIDs, allowing to use wildcardss (i.e. accept all) on each of them.
	/// Additionally, a mask can be specified for groupIDs, so only certain parts of the groupID are required to match.
	///
	class StandardFileFilter : public IResourceFilter
	{
	public:
		StandardFileFilter(
			uint32_t instanceID = ResourceKey::kWildcardID,
			uint32_t groupID = ResourceKey::kWildcardID,
			uint32_t typeID = ResourceKey::kWildcardID,
			uint32_t groupMask = ResourceKey::kWildcardID);

		virtual ~StandardFileFilter() {}

		virtual bool IsValid(const ResourceKey& name);

	public:
		/* 04h */	uint32_t instanceID;
		/* 08h */	uint32_t groupID;
		/* 0Ch */	uint32_t typeID;
		/* 10h */	uint32_t groupMask;
	};

	///////////////////////////////////
	//// INTERNAL IMPLEMENENTATION ////
	///////////////////////////////////

	namespace Addresses(StandardFileFilter) {
		DeclareAddress(IsValid);
	}

	inline auto_METHOD(StandardFileFilter, bool, IsValid, Args(const ResourceKey& name), Args(name));

	inline StandardFileFilter::StandardFileFilter(
		uint32_t nInstanceID,
		uint32_t nGroupID,
		uint32_t nTypeID,
		uint32_t nGroupMask)
		: instanceID(nInstanceID)
		, groupID(nGroupID)
		, typeID(nTypeID)
		, groupMask(nGroupMask)
	{

	}
}
