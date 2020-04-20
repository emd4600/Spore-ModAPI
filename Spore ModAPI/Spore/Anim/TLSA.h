#pragma once

#include <EASTL\string.h>
#include <EASTL\vector.h>

namespace Anim
{
	using namespace eastl;

	struct TlsaAnimation
	{
		/* 00h */	float durationScale;
		/* 04h */	float duration;
		/* 08h */	uint32_t id;
		/* 0Ch */	string16 name;
	};

	struct TlsaAnimChoice
	{
		float probabilityThreshold;
		vector<TlsaAnimation> animations;
	};

	struct TlsaAnimGroup
	{
		/* 00h */	uint32_t id;
		/* 04h */	string16 name;
		/* 14h */	float priorityOverride;
		/* 18h */	float blendInTime;
		/* 1Ch */	bool idle;
		/* 1Dh */	bool allowLocomotion;
		/* 1Eh */	bool randomizeChoicePerLoop;
		/* 20h */	int matchVariantForToolMask;
		/* 24h */	int disableToolOverlayMask;
		/* 28h */	int endMode;
		/* 2Ch */	vector<TlsaAnimChoice> animations;
	};
}