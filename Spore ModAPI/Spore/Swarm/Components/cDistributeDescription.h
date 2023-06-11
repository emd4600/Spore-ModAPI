#pragma once

#include <Spore\ResourceID.h>
#include <Spore\Swarm\cSurfaceInfo.h>
#include <Spore\Swarm\Components\cDescription.h>
#include <Spore\Swarm\Components\cTextureSlot.h>
#include <Spore\Transform.h>
#include <EASTL\vector.h>

namespace Swarm
{
	class cDistributeDescription
		: public cDescription
	{
	public:
		/* 08h */	int flags;
		/* 0Ch */	int density;
		/* 10h */	int field_10;  //  effect?
		/* 14h */	int8_t sourceType;
		/* 18h */	int sourceSize;
		/* 1Ch */	int8_t field_1C;
		/* 20h */	int field_20;  // start?
		/* 24h */	Transform field_24;
		/* 60h */	eastl::vector<float> size;
		/* 74h */	float sizeVary;
		/* 78h */	eastl::vector<float> pitch;
		/* 8Ch */	eastl::vector<float> roll;
		/* A0h */	eastl::vector<float> yaw;
		/* B4h */	float pitchVary;
		/* B8h */	float rollVary;
		/* BCh */	float yawVary;
		/* C0h */	float pitchOffset;
		/* C4h */	float rollOffset;
		/* C8h */	float yawOffset;
		/* CCh */	eastl::vector<Math::ColorRGB> color;
		/* E0h */	Math::ColorRGB colorVary;
		/* ECh */	eastl::vector<float> alpha;
		/* 100h */	float alphaVary;
		/* 104h */	eastl::vector<cSurfaceInfo> surfaces;
		/* 118h */	ResourceID emitMap;
		/* 120h */	ResourceID colorMap;
		/* 128h */	ResourceID pinMap;
		/* 130h */	float altitudeRange[2];
		/* 138h */	cTextureSlot textureSlot;
		/* 158h */	int8_t overrideSet;
		/* 15Ch */	uint32_t messageID;
		/* 160h */	float field_160;
		/* 164h */	float field_164;
		/* 168h */	float field_168;  // rotateVary?
		/* 16Ch */	eastl::vector<float> rotate;
	};
	ASSERT_SIZE(cDistributeDescription, 0x180);
}