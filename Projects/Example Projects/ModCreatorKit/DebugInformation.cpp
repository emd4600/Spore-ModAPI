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
#include "DebugInformation.h"

DebugInformation::DebugInformation()
	: mDebugPath()
	, mFileNames()
	, mpPropList()
{
}

DebugInformation::~DebugInformation()
{

}

bool DebugInformation::GetFilePath(const ResourceKey& key, string16* pDst) const
{
	auto it = mFileNames.find(key);
	if (it != mFileNames.end())
	{
		if (pDst) {
			*pDst = mDebugPath + it->second;
		}
		return true;
	}
	else return false;
}

bool DebugInformation::Read(uint32_t instanceID, uint32_t groupID)
{
	if (PropManager.GetPropertyList(instanceID, groupID, mpPropList))
	{
		size_t nFileCount;
		ResourceKey* pFileKeys;
		string16* pFileNames;

		if (!App::Property::GetArrayKey(mpPropList.get(), id("modFileKeys"), nFileCount, pFileKeys)) return false;

		if (!App::Property::GetArrayString16(mpPropList.get(), id("modFilePaths"), nFileCount, pFileNames)) return false;

		if (!App::Property::GetString16(mpPropList.get(), id("modDebugPath"), mDebugPath)) return false;


		if (mDebugPath[mDebugPath.size() - 1] != '\\') {
			mDebugPath += '\\';
		}

		for (size_t i = 0; i < nFileCount; i++) {
			mFileNames[pFileKeys[i]] = pFileNames[i];
		}

		return true;
	}

	return false;
}