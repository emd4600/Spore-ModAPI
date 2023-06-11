#pragma once

#include <Spore\App\cViewer.h>
#include <Spore\ResourceID.h>
#include <Spore\Transform.h>

namespace Swarm
{
	class ICameraManager
	{
	public:
		/* 00h */	virtual ResourceID CameraIDFromName(const char* name) = 0;
		/* 04h */	virtual void UpdateCameraView(App::cViewer* viewer, int viewFlags) = 0;
		/* 08h */	virtual void UpdateCameraParams(float fov, float nearPlane, float farPlane, int viewFlags) = 0;
		/* 0Ch */	virtual int SetCamera(struct ResourceID) = 0;
		/* 10h */	virtual int GrabCamera(struct ResourceID) = 0;
		/* 14h */	virtual void ReleaseCamera(int index) = 0;
		/* 18h */	virtual void func18h() = 0;
		/* 1Ch */	virtual void CaptureViewToCubemap(int16_t, Transform*) = 0;
		/* 20h */	virtual ~ICameraManager() = 0;

		// field 0Ch is App::ICameraManager
	};
}