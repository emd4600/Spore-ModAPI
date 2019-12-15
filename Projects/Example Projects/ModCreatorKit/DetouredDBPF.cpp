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
#include "DetouredDBPF.h"

#include "Debugging.h"
#include "FilePFRecord.h"

#include <Spore\App\ICheatManager.h>
#include <Spore\Resource\cResourceManager.h>

using namespace Resource;

bool DBPF_detour::DETOUR(
	const ResourceKey& name, IPFRecord** ppDst, int nDesiredAccess, int nCreateDisposition, bool arg_10, DBPFItem* pDstInfo)
{
	DebugInformation* pDebugInformation = nullptr;
	string16 filePath;

	if (nDesiredAccess == IO::kAccessFlagRead  // we only accept reading
		&& ppDst != nullptr  // no point on doing this if we are not going to get the file
		&& Debugging::Get()
		&& Debugging::Get()->GetDebugInformation(this, &pDebugInformation)  // if we have debug information
		&& pDebugInformation->GetFilePath(name, &filePath))  // if this file has a path to debug
	{
		if (App::ICheatManager::Get())  // It's possible that the console does not exist yet, don't take risks
		{
			string16 dstName;
			ResourceManager.GetFileName(name, dstName);
			App::ConsolePrintF("File %ls accessed.", dstName.c_str());
		}

		bool result = false;
		FilePFRecord* pRecord = nullptr;

		mIndexMutex.Lock(Mutex::kDefaultWait);

		DBPFItem* info = mpIndex->GetFileInfo(name);
		if (info != nullptr)
		{
			if (pDstInfo != nullptr) *pDstInfo = *info;

			if (nCreateDisposition == IO::kCDDefault)
			{
				nCreateDisposition = IO::kCDOpenExisting;
			}


			auto it = field_2E8.find(name);
			if (it != field_2E8.end())
			{
				if (it->second->GetType() == FilePFRecord::kType)
				{
					pRecord = new (mpAllocator, "FilePFRecord") FilePFRecord((FilePFRecord*)it->second, name, this);
				}
			}
			else
			{
				pRecord = new (mpAllocator, "FilePFRecord") FilePFRecord(*info, name, this);
			}

			if (pRecord)
			{
				pRecord->SetPath(filePath.c_str());
				pRecord->AddRef();

				if (mnFileAccess & IO::kAccessFlagWrite) {
					field_2E8[name] = pRecord;
				}
			}

			if (ppDst != nullptr) *ppDst = pRecord;

		}

		mIndexMutex.Unlock();

		if (pRecord)
		{
			pRecord->AddRef();
			result = true;
		}

		return result;
	}
	else
	{
		return original_function(this, name, ppDst, nDesiredAccess, nCreateDisposition, arg_10, pDstInfo);
	}
}

