/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\App\DefaultCamera.h>
#include <Spore\App\cCameraManager.h>

#if defined(EA_HAVE_CPP11_INITIALIZER_LIST)
//#error
#endif

#if defined(__cplusplus) && defined(_YVALS)
//#error "CAMERA error"
#endif

namespace App
{
	DefaultCamera::DefaultCamera()
		: mnRefCount(0)
	{
	}

	int DefaultCamera::AddRef()
	{
		return ++mnRefCount;
	}

	int DefaultCamera::Release()
	{
		if (--mnRefCount == 0)
		{
			delete this;
		}
		return mnRefCount;
	}

	void* DefaultCamera::Cast(uint32_t typeID) const
	{
		if (typeID == ICamera::TYPE)
		{
			return (ICamera*) this;
		}
		else if (typeID == Object::TYPE)
		{
			return (Object*) this;
		}
		else
		{
			return nullptr;
		}

	}

	void DefaultCamera::func54h(Vector3& dst)
	{
		dst.x = 0;
		dst.y = 0;
		dst.z = 0;
	}


	cCameraManager::cCameraManager()
		: mnRefCount(0)
		, field_0C()
		, mCheatKeyword()
		, field_20()
		, mTypeFactories()
		, mCameraIndices()
		, mpCameras()
		, mCameraNames()
		, mnActiveIndex(-1)
		, field_AC()
		, mpViewer(nullptr)
	{
	}

	auto_METHOD_VIRTUAL(cCameraManager, ICameraManager, bool, HandleMessage, Args(uint32_t messageID, void* pMessage), Args(messageID, pMessage));
	auto_METHOD_VIRTUAL_(cCameraManager, ICameraManager, int, AddRef);
	auto_METHOD_VIRTUAL_(cCameraManager, ICameraManager, int, Release);
	auto_METHOD_VIRTUAL(cCameraManager, ICameraManager, bool, Initialize, Args(const char* pCheatName), Args(pCheatName));
	auto_METHOD_VIRTUAL_(cCameraManager, ICameraManager, bool, Dispose);
	auto_METHOD_VIRTUAL_VOID(cCameraManager, ICameraManager, SetViewer, Args(cViewer* pViewer), Args(pViewer));
	auto_METHOD_VIRTUAL_(cCameraManager, ICameraManager, cViewer*, GetViewer);
	auto_METHOD_VIRTUAL_VOID(cCameraManager, ICameraManager, AddCameraType, Args(uint32_t typeID, CameraFactoryFunction_t function), Args(typeID, function));
	auto_METHOD_VIRTUAL_VOID(cCameraManager, ICameraManager, PutCamera, Args(uint32_t cameraID, ICamera* pCamera, const wchar_t* pName), Args(cameraID, pCamera, pName));
	auto_METHOD_VIRTUAL_VOID_(cCameraManager, ICameraManager, ParseCameras);
	auto_METHOD_VIRTUAL_VOID(cCameraManager, ICameraManager, Update, Args(int nDeltaTime), Args(nDeltaTime));
	auto_METHOD_VIRTUAL(cCameraManager, ICameraManager, bool, SetActiveCameraByKey, Args(const wchar_t* pKeyString), Args(pKeyString));
	auto_METHOD_VIRTUAL(cCameraManager, ICameraManager, bool, SetActiveCameraByID, Args(uint32_t cameraID), Args(cameraID));
	auto_METHOD_VIRTUAL_(cCameraManager, ICameraManager, ICamera*, GetActiveCamera);
	auto_METHOD_VIRTUAL_(cCameraManager, ICameraManager, uint32_t, GetActiveCameraID);
	auto_METHOD_VIRTUAL(cCameraManager, ICameraManager, ICamera*, GetCamera, Args(uint32_t cameraID), Args(cameraID));
	auto_METHOD_VIRTUAL(cCameraManager, ICameraManager, uint32_t, GetCameraID, Args(const char* pName), Args(pName));
	auto_METHOD_VIRTUAL_(cCameraManager, ICameraManager, size_t, GetCamerasCount);
	auto_METHOD_VIRTUAL(cCameraManager, ICameraManager, ICamera*, GetCameraAt, Args(int nIndex), Args(nIndex));
	auto_METHOD_VIRTUAL(cCameraManager, ICameraManager, uint32_t, GetCameraIDAt, Args(int nIndex), Args(nIndex));
	auto_METHOD_VIRTUAL(cCameraManager, ICameraManager, bool, SetActiveCamera, Args(int nIndex), Args(nIndex));
	auto_METHOD_VIRTUAL_(cCameraManager, ICameraManager, int, GetActiveCameraIndex);
	auto_METHOD_VIRTUAL_VOID_(cCameraManager, ICameraManager, RemoveCameras);

}