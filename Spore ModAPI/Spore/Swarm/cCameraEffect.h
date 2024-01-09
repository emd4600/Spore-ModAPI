#pragma once

#include <Spore\Swarm\Components\cCameraDescription.h>
#include <Spore\Swarm\IComponent.h>
#include <Spore\Swarm\ICameraManager.h>
#include <Spore\Transform.h>

namespace Swarm
{
	class cCameraEffect
		: public cComponentBase
	{
	public:
		/* 0Ch */	cCameraDescription* mpDescription;
		/* 10h */	ICameraManager* mpCameraMgr;
		/* 14h */	bool mIsRunning;
		/* 18h */	float mInvLifeTime;
		/// Between 0.0 and 1.0
		/* 1Ch */	float mLifeTimeProgress;
		/* 20h */	float field_20;
		/* 24h */	Transform mTransform;
		/* 5Ch */	float mFOV;  // -1.0
		/* 60h */	float mNearClip;  // -1.0
		/* 64h */	float mFarClip;  // -1.0
		/* 68h */	int mGrabbedCameraIndex;  // -1
	};
	ASSERT_SIZE(cCameraEffect, 0x6C);
}