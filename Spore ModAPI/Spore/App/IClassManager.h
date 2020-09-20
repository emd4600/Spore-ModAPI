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
#include <Spore\ICoreAllocator.h>

/// Access the active class manager
#define ClassManager (*App::IClassManager::Get())

namespace App
{

	class ISPClassFactory
	{
	public:
		virtual ~ISPClassFactory() {};
		virtual size_t GetTypes(uint32_t* pDstTypes, size_t count) const = 0;
		virtual Object* Create(uint32_t type, ICoreAllocator* pAllocator = nullptr) = 0;
		virtual const char* GetName(uint32_t type) const = 0;

	protected:
		int field_4;
		int field_8;
		bool field_C;
	};

	class IClassManager
	{
	public:
		virtual ~IClassManager();

		/* 04h */	virtual bool AddFactory(ISPClassFactory* pFactory, int=0) = 0;
		/* 08h */	virtual bool RemoveFactory(ISPClassFactory* pFactory) = 0;
		/* 0Ch */	virtual int func0Ch(int) = 0;
		/* 10h */	virtual int func10h(int, int) = 0;
		/* 14h */	virtual ISPClassFactory* GetFactory(uint32_t type) = 0;
		/* 18h */	virtual int func18h(int, int, int, int) = 0;
		/* 1Ch */	virtual int func1Ch(int, int, int) = 0;
		/* 20h */	virtual void* CreateCasted(uint32_t classID, uint32_t type, ICoreAllocator* pAllocator = nullptr, ISPClassFactory* pFactory = nullptr) = 0;
		/* 24h */	virtual Object* Create(uint32_t classID, ICoreAllocator* pAllocator = nullptr, ISPClassFactory* pFactory = nullptr) = 0;

		static IClassManager* Get();
	};

	namespace Addresses(IClassManager)
	{
		DeclareAddress(Get);
	}
}