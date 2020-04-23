#pragma once

#include <Spore\App\PropertyList.h>
#include <Spore\Swarm\IEffectWorld.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

namespace Terrain
{
	using namespace eastl;
	using namespace Math;

	class ITerrain;
	class cTerrainMapSet;

	class cTerrainStateMgr
	{
	public:
		struct TerrainMaterial
		{
			/* 00h */	char padding_00[0x14];  // not initialized
			/* 14h */	float kMinMaxAlt;
			/* 18h */	float kMidMaxAlt;
			/* 1Ch */	float kMaxMaxAlt;
			/* 20h */	char padding_20[0x10];  // not initialized
			/* 30h */	float field_30;  // related with minmaxalt and midmaxalt and planet height?
			/* 34h */	char padding_34[0xC];  // not initialized
			/* 40h */	float kMinCliffGradient;
			/* 44h */	float kMaxCliffGradient;
			/* 48h */	char padding_48[0x30];  // not initialized
			/* 78h */	uint32_t mLightingState;
			/* 7Ch */	Vector2 kEffectAtmosphereLowRange;
			/* 84h */	Vector2 kEffectAtmosphereMedRange;
			/* 8Ch */	Vector2 kEffectAtmosphereHighRange;
			/* 94h */	Vector2 kEffectTemperatureLowRange;
			/* 9Ch */	Vector2 kEffectTemperatureMedRange;
			/* A4h */	Vector2 kEffectTemperatureHighRange;
			/* ACh */	Vector4 kNightLightingTint;  // last value is kNightLumBlend
			/* BCh */	int field_BC;  // not initialized
			/* C0h */	Vector3 kDayLightColor;
			/* CCh */	Vector3 kDayShadowColor;
			/* D8h */	Vector3 kDuskLightColor;
			/* E4h */	Vector3 kDuskShadowColor;
			/* F0h */	Vector3 kNightLightColor;
			/* FCh */	Vector3 kNightShadowColor;
			/* 108h */	Vector4 kDuskDawnStartEnd;
			/* 118h */	float kAboveColorRampSeaScaleBaseVal;
			/* 11Ch */	float kAboveColorRampSeaScaleScaleVal;
			/* 120h */	vector<Vector2> kAtmThicknessByAtmosphereScore;
			/* 134h */	Vector2 kAtmLuminenceRange;
			/* 13Ch */	float kAboveDetailLowTiling;
			/* 140h */	float kAboveDetailHighTiling;
			/* 144h */	float kFogMinDensity;
			/* 148h */	float kFogMaxDensity;
			/* 14Ch */	float kFogMinDistance;
			/* 150h */	vector<Vector3> kFogByElevCreature;
			/* 164h */	vector<Vector3> kFogByElevTribe;
			/* 178h */	vector<Vector3> kFogByElevCiv;
			/* 18Ch */	vector<Vector3> kFogByElevSpace;
			/* 1A0h */	vector<Vector2> kFogDistBiasByTimeOfDay;
			/* 1B4h */	vector<Vector3> kFogDistBiasByAtmosphereScore;
			/* 1C8h */	vector<Vector2> kFogBiasByElev;
			/* 1DCh */	int field_1DC;  // not initialized
			/* 1E0h */	float kWaterFogMaxDepth;
			/* 1E4h */	float kWaterPCAAnimationFPS;
			/* 1E8h */	float kLavaPCAAnimationFPS;
			/* 1ECh */	ResourceObjectPtr mWaterMap;  // depends on mAtmosphereType, bit image
			/* 1F0h */	float kParticleMaxDistance;
			/* 1F4h */	float kTerrainBrightness;
			/* 1F8h */	float kP1ScaleDensity;
			/* 1FCh */	float kP2ScaleDensity;
			/* 200h */	float kP3ScaleDensity;
			/* 204h */	ResourceObjectPtr field_204;  // 5359C50, 8bit image
			/* 208h */	ResourceObjectPtr mAtmosphereMap;  // depends on mAtmosphereType, bit image
			/* 20Ch */	ResourceObjectPtr field_20C;  // 8bit image
			/* 210h */	ResourceObjectPtr field_210;  // 8bit image
			/* 214h */	Vector3 kP1Phase;
			/* 220h */	Vector3 kP1Brightness;
			/* 22Ch */	Vector3 kP2Phase;
			/* 238h */	Vector3 kP2Brightness;
			/* 244h */	Vector3 kP3Phase;
			/* 250h */	Vector3 kP3Brightness;
			/* 25Ch */	char padding_25C[0x34];  // not initialized
			/* 290h */	vector<int> field_290;
			/* 2A4h */	vector<int> field_2A4;
			/* 2B8h */	float terrainUserColorRockSaturationFactor;
			/* 2BCh */	float terrainUserColorBeachSaturationFactor;
			/* 2C0h */	float terrainUserColorCliffSaturationFactor;
			/* 2C4h */	float terrainUserColorWaterSaturationFactor;
			/* 2C8h */	float terrainUserColorAtmosphereSaturationFactor;
			/* 2CCh */	float terrainUserColorElevationMapSaturationFactor;
			/* 2D0h */	float terrainUserColorRockValueFactor;
			/* 2D4h */	float terrainUserColorBeachValueFactor;
			/* 2D8h */	float terrainUserColorCliffValueFactor;
			/* 2DCh */	float terrainUserColorWaterValueFactor;
			/* 2E0h */	float terrainUserColorAtmosphereValueFactor;
			/* 2E4h */	float terrainUserColorElevationMapValueFactor;
			/* 2E8h */	float terrainUserColorAutoGradientThreshold;
		};
		ASSERT_SIZE(TerrainMaterial, 0x2EC);

		struct TerrainTextures
		{
			/* 00h */	TexturePtr field_00;
			/* 04h */	TexturePtr field_04;
			/* 08h */	TexturePtr field_08;
			/* 0Ch */	TexturePtr pTextureAboveDetail2;
			/* 10h */	TexturePtr pTextureBelow;
			/* 14h */	TexturePtr field_14;
			/* 18h */	TexturePtr field_18;
			/* 1Ch */	TexturePtr field_1C;
			/* 20h */	TexturePtr field_20;
			/* 24h */	TexturePtr field_24;
			/* 28h */	TexturePtr pTextureBeach;
			/* 2Ch */	TexturePtr pTextureCliff;
			/* 30h */	TexturePtr field_30;
			/* 34h */	TexturePtr field_34;
			/* 38h */	ResourceObjectPtr field_38;  // 8 bit image?
			/* 3Ch */	ResourceObjectPtr field_3C;
			/* 40h */	ResourceObjectPtr field_40;
			/* 44h */	ResourceObjectPtr field_44;
			/* 48h */	ResourceObjectPtr field_48;
			/* 4Ch */	ResourceObjectPtr field_4C;
			/* 50h */	ResourceObjectPtr field_50;
			/* 54h */	ResourceObjectPtr field_54;  // pcaw file?
			/* 58h */	ColorRGBA nightLightTint;
			/* 68h */	ColorRGBA dayLightColor;
			/* 78h */	ColorRGBA duskLightColor;
			/* 88h */	ColorRGBA nightLightColor;
			/* 98h */	ColorRGBA dayShadowColor;
			/* A8h */	ColorRGBA duskShadowColor;
			/* B8h */	ColorRGBA nightShadowColor;
			/* C8h */	Vector4 duskDawnStartEnd;
			/* D8h */	char padding_D8[0x60];
			/* 138h */	Vector4 waterColor;
			/* 148h */	Vector4 innerParms;
			/* 158h */	Vector4 field_158;
			/* 168h */	Vector4 field_168;
			/* 178h */	Vector4 sunDir;
			/* 188h */	Matrix4 viewTransform;
			/* 1C8h */	Vector4 sphereParms;
			/* 1D8h */	Vector4 camParms;
			/* 1E8h */	Vector4 illumParms;
			/* 1F8h */	Vector4 fogParms;
			/* 208h */	char padding_208[0xB0];
		};
		ASSERT_SIZE(TerrainTextures, 0x2B8);

		/* 00h */	ITerrain* mpTerrain;
		/* 04h */	cTerrainMapSet* mpMapSet;
		/* 08h */	TerrainMaterial field_08;
		/* 2F4h */	TerrainTextures mTextures;
		/* 5ACh */	bool field_5AC;  // true
		/* 5ADh */	bool field_5AD;
		/* 5B0h */	PropertyListPtr mpMaterialPropList;
		/* 5B4h */	int field_5B4;
		/* 5B8h */	int field_5B8;
		/* 5BCh */	int field_5BC;  // not initialized
		/* 5C0h */	int mAtmosphereType;
		/* 5C4h */	int mWaterType;
		/* 5C8h */	Vector4 field_5C8;
		/* 5D8h */	Vector4 field_5D8;
		/* 5E8h */	Vector4 field_5E8;
		/* 5F8h */	IEffectWorldPtr field_5F8;
		/* 5FCh */	int field_5FC;
		/* 600h */	float field_600;  // -1
		/* 604h */	float mWaterLevel;  // 0.5
		/* 608h */	float field_608;
		/* 60Ch */	float field_60C;  // 1.0
		/* 610h */	float mWaveFreq;  // 1.0
		/* 614h */	float mWaveAmp;
		/* 618h */	float field_618;
		/* 61Ch */	float field_61C;
		/* 620h */	float field_620;
		/* 624h */	float field_624;
		/* 628h */	char field_628[0x194];
		/* 7BCh */	bool field_7BC;
		/* 7C0h */	char field_7C0[0x180];
		/* 940h */	char field_940[0x180];
		/* AC0h */	char field_AC0[0x180];
	};
	ASSERT_SIZE(cTerrainStateMgr, 0xC40);
}