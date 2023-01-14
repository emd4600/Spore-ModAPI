/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModCreatorKit.
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
#include "stdafx.h"
#include "Debugging.h"
#include "DetouredDBPF.h"
#include "DetouredResourceManager.h"

#include <Spore\Hash.h>
#include <Spore\App\IPropManager.h>
#include <Spore\Resource\IResourceManager.h>
#include <Spore\Resource\DatabasePackedFile.h>
#include <Spore\Resource\PFIndexModifiable.h>

#include <EASTL\string.h>

using namespace IO;

intrusive_ptr<Debugging> Debugging::sMain = nullptr;

Debugging::Debugging()
	: mPackageMap()
{
}

Debugging::~Debugging()
{
}

long Debugging::AttachDetour()
{
	long result = 0;
	result |= DBPF_detour::attach(GetAddress(Resource::DatabasePackedFile, GetFile));
	result |= ResourceManager_detour::attach(GetAddress(Resource::cResourceManager, GetResource));
	return result;
}

bool Debugging::GetDebugInformation(Database* database, DebugInformation** ppDst) const
{
	auto it = mPackageMap.find(database);
	if (it != mPackageMap.end())
	{
		if (ppDst) *ppDst = it->second.get();
		return true;
	}
	else return false;
}

void Debugging::Initialize()
{
	sMain = new Debugging();
	sMain->DetectDBPFs();
}

void Debugging::Dispose()
{
	sMain = nullptr;
}

void Debugging::DetectDBPFs()
{
	uint32_t groupID = id("_SporeModder");

	vector<uint32_t> propNames;
	if (PropManager.GetPropertyListIDs(groupID, propNames))
	{
		for (uint32_t name : propNames) {
			intrusive_ptr<DebugInformation> pInfo = new DebugInformation();
			if (pInfo->Read(name, groupID))
			{
				auto database = ResourceManager.FindDatabase({ name, TypeIDs::prop, groupID });
				mPackageMap[database] = pInfo;
			}
		}
	}
}
