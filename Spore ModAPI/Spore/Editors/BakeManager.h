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

#include <Spore\ResourceKey.h>

/// Access the active bake manager.
#define BakeManager (*Editors::IBakeManager::Get())

namespace Editors
{
	struct BakeParameters
	{
		BakeParameters(int16_t field_04, int16_t field_06 = 4, uint32_t defaultID = 0x2EA8FB98);

		uint32_t mDefaultID;
		int16_t field_04;
		int16_t field_06;
	};

	class IBakeManager
	{
	public:

		/* 00h */	virtual void func00h();
		/* 04h */	virtual void func04h();
		/* 08h */	virtual void func08h();
		/* 0Ch */	virtual void func0Ch();
		/* 10h */	virtual void func10h();
		/* 14h */	virtual void func14h();
		/* 18h */	virtual void func18h();
		/* 1Ch */	virtual void func1Ch();
		/* 20h */	virtual void func20h();
		/* 24h */	virtual void func24h();
		/* 28h */	virtual void func28h();
		/* 2Ch */	virtual void func2Ch();
		/* 30h */	virtual void func30h();
		/* 34h */	virtual void func34h();
		/* 38h */	virtual void func38h();
		/* 3Ch */	virtual void func3Ch();
		/* 40h */	virtual void func40h();
		/* 44h */	virtual void func44h();
		/* 48h */	virtual void func48h();
		/* 4Ch */	virtual void func4Ch(const ResourceKey& nameKey, const BakeParameters& params);  // bake?

		static IBakeManager* Get();
	};

	namespace Addresses(IBakeManager)
	{
		DeclareAddress(Get);
	}

	inline BakeParameters::BakeParameters(int16_t _field_04, int16_t _field_06, uint32_t defaultID)
		: field_04(_field_04)
		, field_06(_field_06)
		, mDefaultID(defaultID)
	{

	}
}
