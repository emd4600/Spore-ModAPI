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
		virtual void PutCamera(uint32_t cameraID, ICamera* pCamera, const char16_t* pName) override;
		virtual void ParseCameras() override;
		virtual void Update(int nDeltaTime) override;
		virtual bool SetActiveCameraByKey(const char16_t* pKeyString) override;
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
		/* 20h */	hash_map<string16, int> field_20;
		/* 40h */	hash_map<uint32_t, CameraFactoryFunction_t> mTypeFactories;
		/* 60h */	hash_map<uint32_t, size_t> mCameraIndices;
		/* 80h */	vector<intrusive_ptr<ICamera>> mpCameras;
		/* 94h */	vector<string16> mCameraNames;
		/* A8h */	int mnActiveIndex;  // -1
		/* ACh */	int field_AC;
		/* B0h */	cViewer* mpViewer;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cCameraManager) == 0xB4, "sizeof(cCameraManager) != B4h");

	namespace Addresses(cCameraManager)
	{
		DeclareAddress(HandleMessage);
		DeclareAddress(AddRef);
		DeclareAddress(Release);
		DeclareAddress(Initialize);
		DeclareAddress(Dispose);
		DeclareAddress(SetViewer);
		DeclareAddress(GetViewer);
		DeclareAddress(AddCameraType);
		DeclareAddress(PutCamera);
		DeclareAddress(ParseCameras);
		DeclareAddress(Update);
		DeclareAddress(SetActiveCameraByKey);
		DeclareAddress(SetActiveCameraByID);
		DeclareAddress(GetActiveCamera);
		DeclareAddress(GetActiveCameraID);
		DeclareAddress(GetCamera);
		DeclareAddress(GetCameraID);
		DeclareAddress(GetCamerasCount);
		DeclareAddress(GetCameraAt);
		DeclareAddress(GetCameraIDAt);
		DeclareAddress(SetActiveCamera);
		DeclareAddress(GetActiveCameraIndex);
		DeclareAddress(RemoveCameras);
	}
}