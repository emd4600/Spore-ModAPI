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

#include <Spore\App\ICameraManager.h>
#include <Spore\Object.h>

#include <EASTL\hash_map.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>

using namespace eastl;

namespace App
{
	///
	/// The implementation of ICameraManager; this should only be used for extending and detouring.
	///
	class cCameraManager : public ICameraManager, public IVirtual
	{
	public:
		cCameraManager();

		virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;
		virtual int AddRef() override;
		virtual int Release() override;
		virtual bool Initialize(const char* pCheatName) override;
		virtual bool Dispose() override;
		virtual void SetViewer(cViewer* pViewer) override;
		virtual cViewer* GetViewer() override;
		virtual void AddCameraType(uint32_t typeID, CameraFactoryFunction_t function) override;
		virtual void PutCamera(uint32_t cameraID, ICamera* pCamera, const wchar_t* pName) override;
		virtual void ParseCameras() override;
		virtual void Update(int nDeltaTime) override;
		virtual bool SetActiveCameraByKey(const wchar_t* pKeyString) override;
		virtual bool SetActiveCameraByID(uint32_t cameraID) override;
		virtual ICamera* GetActiveCamera() override;
		virtual uint32_t GetActiveCameraID() override;
		virtual ICamera* GetCamera(uint32_t cameraID) override;
		virtual uint32_t GetCameraID(const char* pName) override;
		virtual size_t GetCamerasCount() override;
		virtual ICamera* GetCameraAt(int nIndex) override;
		virtual uint32_t GetCameraIDAt(int nIndex) override;
		virtual bool SetActiveCamera(int nIndex) override;
		virtual int GetActiveCameraIndex() override;
		virtual void RemoveCameras() override;


	protected:
		/* 08h */	int mnRefCount;
		/* 0Ch */	bool field_0C;
		/* 10h */	string mCheatKeyword;
		/* 20h */	hash_map<wstring, int> field_20;
		/* 40h */	hash_map<uint32_t, CameraFactoryFunction_t> mTypeFactories;
		/* 60h */	hash_map<uint32_t, size_t> mCameraIndices;
		/* 80h */	vector<intrusive_ptr<ICamera>> mpCameras;
		/* 94h */	vector<wstring> mCameraNames;
		/* A8h */	int mnActiveIndex;  // -1
		/* ACh */	int field_AC;
		/* B0h */	cViewer* mpViewer;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cCameraManager) == 0xB4, "sizeof(cCameraManager) != B4h");

	namespace InternalAddressList(cCameraManager)
	{
		DefineAddress(HandleMessage, GetAddress(0x7C6D40, 0x7C6650, 0x7C66B0));
		DefineAddress(AddRef, GetAddress(0xAE9150, 0xC6AAD0, 0xC6AB00));
		DefineAddress(Release, GetAddress(0x5BF860, 0x7B8750, 0x7B87B0));
		DefineAddress(Initialize, GetAddress(0x7C77E0, 0x7C70F0, 0x7C7150));
		DefineAddress(Dispose, GetAddress(0x7C7540, 0x7C6DF0, 0x7C6E50));
		DefineAddress(SetViewer, GetAddress(0x7C6770, 0x7C6140, 0x7C61A0));
		DefineAddress(GetViewer, GetAddress(0x7C6780, 0xA21000, 0xA21090));
		DefineAddress(AddCameraType, GetAddress(0x7C7620, 0x7C6ED0, 0x7C6F30));
		DefineAddress(PutCamera, GetAddress(0x7C79A0, 0x7C72B0, 0x7C7310));
		DefineAddress(ParseCameras, GetAddress(0x7C72B0, 0x7C6BC0, 0x7C6C20));
		DefineAddress(Update, GetAddress(0x7C6B00, 0x7C63E0, 0x7C6440));
		DefineAddress(SetActiveCameraByKey, GetAddress(0x7C6790, 0x7C6150, 0x7C61B0));
		DefineAddress(SetActiveCameraByID, GetAddress(0x7C6DE0, 0x7C66F0, 0x7C6750));
		DefineAddress(GetActiveCamera, GetAddress(0x7C6820, 0x7C61E0, 0x7C6240));
		DefineAddress(GetActiveCameraID, GetAddress(0x7C67D0, 0x7C6190, 0x7C61F0));
		DefineAddress(GetCamera, GetAddress(0x7C6E30, 0x7C6740, 0x7C67A0));
		DefineAddress(GetCameraID, GetAddress(0x7C6C40, 0x7C6520, 0x7C6580));
		DefineAddress(GetCamerasCount, GetAddress(0x7C6840, 0x7C6200, 0x7C6260));
		DefineAddress(GetCameraAt, GetAddress(0x7C6850, 0x7C6210, 0x7C6270));
		DefineAddress(GetCameraIDAt, GetAddress(0x7C6BE0, 0x7C64C0, 0x7C6520));
		DefineAddress(SetActiveCamera, GetAddress(0x7C6B80, 0x7C6460, 0x7C64C0));
		DefineAddress(GetActiveCameraIndex, GetAddress(0xE464D0, 0x98F870, 0x98F870));
		DefineAddress(RemoveCameras, GetAddress(0x7C7640, 0x7C6EF0, 0x7C6F50));

	}
}