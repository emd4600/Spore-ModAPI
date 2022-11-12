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
#pragma once

#include <EASTL\string.h>
#include <EASTL\hash_map.h>

#include <Spore\ResourceKey.h>
#include <Spore\App\PropertyList.h>

class DebugInformation
	: public DefaultRefCounted
{
public:
	DebugInformation();
	~DebugInformation();

	bool GetFilePath(const ResourceKey& key, string16* pDst = nullptr) const;

	bool Read(uint32_t instanceID, uint32_t groupID);

protected:
	string16 mDebugPath;
	hash_map<ResourceKey, string16> mFileNames;
	PropertyListPtr mpPropList;
};