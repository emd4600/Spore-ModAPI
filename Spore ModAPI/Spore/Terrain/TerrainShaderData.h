#pragma once

#include <Spore\MathUtils.h>

namespace Terrain
{
	using namespace Math;

	struct TerrainState
	{
		/* 00h */	Vector4 vSunDir;
		/* 10h */	ColorRGBA waterColor;
		/* 20h */	Vector4 innerParms;
		/* 30h */	Vector4 vCamPos;
		/* 40h */	Vector4 sphereParms;
		/* 50h */	Vector4 camParms;
		/* 60h */	Vector4 illumParms;
		/* 70h */	Vector4 fogParms;
		/* 80h */	ColorRGBA nightLightTint;
		/* 90h */	ColorRGBA nightLightColor;
		/* A0h */	ColorRGBA duskLightColor;
		/* B0h */	ColorRGBA dayLightColor;
		/* C0h */	ColorRGBA nightShadowColor;
		/* D0h */	ColorRGBA duskShadowColor;
		/* E0h */	ColorRGBA dayShadowColor;
		/* F0h */	Vector4 duskDawnStartEnd;
		/* 100h */	Matrix4 viewTransform;
	};
	ASSERT_SIZE(TerrainState, 0x140);

	struct TerrainLighting
	{
		/* 00h */	Vector4 vSunDir;
		/* 10h */	ColorRGBA nightLightTint;
		/* 20h */	ColorRGBA nightLightColor;
		/* 30h */	ColorRGBA duskLightColor;
		/* 40h */	ColorRGBA dayLightColor;
		/* 50h */	ColorRGBA nightShadowColor;
		/* 60h */	ColorRGBA duskShadowColor;
		/* 70h */	ColorRGBA dayShadowColor;
		/* 80h */	Vector4 duskDawnStartEnd;
	};
	ASSERT_SIZE(TerrainLighting, 0x90);
}