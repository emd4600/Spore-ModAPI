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

#include <Spore\MathUtils.h>
#include <EASTL\map.h>
#include <EASTL\string.h>

#define cIdentityColorablePtr eastl::intrusive_ptr<Simulator::cIdentityColorable>

namespace Simulator
{
	enum class IdentityColors : uint32_t
	{
		Player = 0x053dbcf1,
		Neutral = 0x053dbcf2,
		Brown = 0x053dbcf3,
		Pink = 0x053dbcf4,
		Cyan = 0x053dbcf5,
		Green = 0x053dbcf6,
		Lavender = 0x053dbcf7,
		Orange = 0x053dbcf8,
		Yellow = 0x053dbcf9,
		Red = 0x053dbcfa,
		Blue = 0x053dbcfb,
		Forest = 0x053dbcfc,
		Crimson = 0x053dbcfd,
		Purple = 0x053dbcfe,
	};

	///
	/// A Simulator class inherited by all those classes that can have an identity color, such as 
	/// empires, tribes, etc
	///
	/// The following attributes are saved:
	/// - mIDColorID
	/// - mCachedColor
	///
	class cIdentityColorable
	{
	public:
		static const uint32_t TYPE = 0x5593A1A;

		virtual ~cIdentityColorable();

		/* 04h */	virtual uint32_t GetType();
		/* 08h */	virtual int AddRef() = 0;
		/* 0Ch */	virtual int Release() = 0;
		/* 10h */	virtual void* Cast(uint32_t typeID);
		/* 14h */	virtual void Write(void*);
		/* 18h */	virtual void Read(void*);

		/// Generates the identity name according to the color, and the names for all its entities.
		/// @param speciesName
		void AssignNames(const eastl::string16& speciesName);

	public:
		/* 04h */	uint32_t mIDColorID;  // 0x53DBCF1
		/// Names for different entities such as buildings, vehicles, etc. Check `Identity.locale`
		/* 08h */	eastl::map<int, eastl::string16> mEntityNames;
		/* 24h */	Math::ColorRGB mCachedColor;
	};
	ASSERT_SIZE(cIdentityColorable, 0x30);

	namespace Addresses(cIdentityColorable) 
	{
		DeclareAddress(AssignNames);  // 0xB6F040 0xB6F480
	}

	const Math::ColorRGB& GetCachedColorFromId(uint32_t colorId);

	eastl::map<uint32_t, Math::ColorRGB>& GetCachedColorIdMap();
}

namespace Addresses(Simulator) {
	DeclareAddress(GetCachedColorFromId);  // 0xB6ED80 0xB6F1C0
	DeclareAddress(sCachedColorIdMap__ptr);  // 0x156F098 0x156B0B8
}