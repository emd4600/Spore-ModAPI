#pragma once

#include <Spore\ResourceID.h>
#include <Spore\Swarm\Components\cDescription.h>
#include <EASTL\vector.h>

namespace Swarm
{
	class cCameraDescription
		: public cDescription
	{
	public:
		/* 08h */	int flags;
		/* 0Ch */	int viewFlags;  // only & 0xFFFF
		/* 10h */	float lifeTime;
		/* 14h */	eastl::vector<float> yaw;
		/* 28h */	eastl::vector<float> pitch;
		/* 3Ch */	eastl::vector<float> roll;
		/* 50h */	eastl::vector<float> distance;
		/* 64h */	eastl::vector<float> fov;
		/* 78h */	eastl::vector<float> nearClip;
		/* 8Ch */	eastl::vector<float> farClip;
		/* A0h */	ResourceID cameraID;
		/* A8h */	int16_t cubemapResource;
	};
	ASSERT_SIZE(cCameraDescription, 0xB0);
}