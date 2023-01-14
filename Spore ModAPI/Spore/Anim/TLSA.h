#pragma once

#include <EASTL\string.h>
#include <EASTL\vector.h>

namespace Anim
{
	struct TlsaAnimation
	{
		/* 00h */	float durationScale;
		/* 04h */	float duration;
		/* 08h */	uint32_t id;
		/* 0Ch */	eastl::string16 name;
	};

	struct TlsaAnimChoice
	{
		eastl::vector<TlsaAnimation> animations;
		float probabilityThreshold;
	};

	struct TlsaAnimGroup
	{
		/* 00h */	uint32_t id;
		/* 04h */	eastl::string16 name;
		/* 14h */	float priorityOverride;
		/* 18h */	float blendInTime;
		/* 1Ch */	bool idle;
		/* 1Dh */	bool allowLocomotion;
		/* 1Eh */	bool randomizeChoicePerLoop;
		/* 20h */	int matchVariantForToolMask;
		/* 24h */	int disableToolOverlayMask;
		/* 28h */	int endMode;
		/* 2Ch */	eastl::vector<TlsaAnimChoice> animations;
	};
}