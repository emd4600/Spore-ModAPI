#pragma once

#include <Spore\App\PropertyList.h>
#include <Spore\Swarm\IEffectsWorld.h>
#include <Spore\Graphics\Texture.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

namespace Terrain
{
	class ITerrain;
	class cTerrainMapSet;

	struct cTerrainStateMgr
	{
		struct TerrainMaterial
		{
			TerrainMaterial();

			/* 00h */	char padding_00[0x14];  // not initialized
			/* 14h */	float kMinMaxAlt;
			/* 18h */	float kMidMaxAlt;
			/* 1Ch */	float kMaxMaxAlt;
			/* 20h */	int field_20;  // not initialized
			/* 24h */	float mAtmosphereReciprocalScore;  // not initialized, 1 - atmosphereScore
			/* 28h */	float mTemperatureScore;  // not initialized
			/* 2Ch */	int field_2C;  // not initialized
			/* 30h */	float field_30;  // related with minmaxalt and midmaxalt and planet height?
			/* 34h */	char padding_34[0xC];  // not initialized
			// 38h is a Matrix4, 2C is sun pos ? check sub_FBB460
			/* 40h */	float kMinCliffGradient;
			/* 44h */	float kMaxCliffGradient;
			/* 48h */	char padding_48[0x30];  // not initialized
			/* 78h */	uint32_t mLightingState;
			/* 7Ch */	Math::Vector2 kEffectAtmosphereLowRange;
			/* 84h */	Math::Vector2 kEffectAtmosphereMedRange;
			/* 8Ch */	Math::Vector2 kEffectAtmosphereHighRange;
			/* 94h */	Math::Vector2 kEffectTemperatureLowRange;
			/* 9Ch */	Math::Vector2 kEffectTemperatureMedRange;
			/* A4h */	Math::Vector2 kEffectTemperatureHighRange;
			/* ACh */	Math::Vector4 kNightLightingTint;  // last value is kNightLumBlend
			/* BCh */	int field_BC;  // not initialized
			/* C0h */	Math::Vector3 kDayLightColor;
			/* CCh */	Math::Vector3 kDayShadowColor;
			/* D8h */	Math::Vector3 kDuskLightColor;
			/* E4h */	Math::Vector3 kDuskShadowColor;
			/* F0h */	Math::Vector3 kNightLightColor;
			/* FCh */	Math::Vector3 kNightShadowColor;
			/* 108h */	Math::Vector4 kDuskDawnStartEnd;
			/* 118h */	float kAboveColorRampSeaScaleBaseVal;
			/* 11Ch */	float kAboveColorRampSeaScaleScaleVal;
			/* 120h */	eastl::vector<Math::Vector2> kAtmThicknessByAtmosphereScore;
			/* 134h */	Math::Vector2 kAtmLuminenceRange;
			/* 13Ch */	float kAboveDetailLowTiling;
			/* 140h */	float kAboveDetailHighTiling;
			/* 144h */	float kFogMinDensity;
			/* 148h */	float kFogMaxDensity;
			/* 14Ch */	float kFogMinDistance;
			/* 150h */	eastl::vector<Math::Vector3> kFogByElevCreature;
			/* 164h */	eastl::vector<Math::Vector3> kFogByElevTribe;
			/* 178h */	eastl::vector<Math::Vector3> kFogByElevCiv;
			/* 18Ch */	eastl::vector<Math::Vector3> kFogByElevSpace;
			/* 1A0h */	eastl::vector<Math::Vector2> kFogDistBiasByTimeOfDay;
			/* 1B4h */	eastl::vector<Math::Vector3> kFogDistBiasByAtmosphereScore;
			/* 1C8h */	eastl::vector<Math::Vector2> kFogBiasByElev;
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
			/* 204h */	ResourceObjectPtr mAtmosphereMap;  // depends on mAtmosphereType, 5359C50, 8bit image
			/* 208h */	ResourceObjectPtr field_208;  // bit image
			/* 20Ch */	ResourceObjectPtr field_20C;  // 8bit image
			/* 210h */	ResourceObjectPtr field_210;  // 8bit image
			/* 214h */	Math::Vector3 kP1Phase;
			/* 220h */	Math::Vector3 kP1Brightness;
			/* 22Ch */	Math::Vector3 kP2Phase;
			/* 238h */	Math::Vector3 kP2Brightness;
			/* 244h */	Math::Vector3 kP3Phase;
			/* 250h */	Math::Vector3 kP3Brightness;
			/* 25Ch */	bool userColorBeachEnabled;  // not initialized
			/* 260h */	Math::ColorRGB factoredTerrainUserColorBeach;  // not initialized
			/* 26Ch */	Math::ColorRGB factoredTerrainUserColorCliff;  // not initialized
			/* 278h */	Math::ColorRGB factoredTerrainUserColorWater;  // not initialized
			/* 284h */	Math::ColorRGB factoredTerrainUserColorAtmosphere;  // not initialized
			/* 290h */	eastl::vector<float> factoredTerrainUserColorElevations;
			/* 2A4h */	eastl::vector<Math::ColorRGB> factoredTerrainUserColorElevationColors;
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
			TerrainTextures();

			/// From texture `0x9D8D0398.rw4`
			/* 00h */	TexturePtr mpWaterFoamCutMap;
			/// From texture `0x11B5EE6F.rw4`
			/* 04h */	TexturePtr mpWaterPCAComponent0;
			/// From texture `0x11B5EE6E.rw4`
			/* 08h */	TexturePtr mpWaterPCAComponent1;
			/// From texture `0x84613AC8.rw4`
			/* 0Ch */	TexturePtr mpTextureAboveDetail2;
			/// From texture `0xC66C3FCD.rw4`
			/* 10h */	TexturePtr mpTextureBelow;
			/// From texture `lava_detail.rw4`
			/* 14h */	TexturePtr mpLavaDetail;
			/// From texture `lava_ramp.rw4`
			/* 18h */	TexturePtr mpLavaRamp;
			/// From texture `0xA5AB24F5.rw4`
			/* 1Ch */	TexturePtr mpIceDetailNear;
			/// From texture `0x3CEF83D5.rw4`
			/* 20h */	TexturePtr mpIceDetailMid;
			/// From texture `ice_ramp.rw4`
			/* 24h */	TexturePtr mpIceRamp;
			/// From texture `0x9D64F524.rw4`
			/* 28h */	TexturePtr mpTextureBeach;
			/// From texture `0x3F05C913.rw4`
			/* 2Ch */	TexturePtr mpTextureCliff;
			/// From texture `atmosphere_packed_curves.rw4`
			/* 30h */	TexturePtr mpAtmospherePackedCurves;
			/// Texture created in code with ID `AboveColorRamp`
			/* 34h */	TexturePtr mpAboveColorRamp;
			/// From bitmap `0xC5D262E4.8bitImage`
			/* 38h */	ResourceObjectPtr field_38;
			/// From bitmap `0x362AC39E.32bitImage`
			/* 3Ch */	ResourceObjectPtr field_3C;
			/// From bitmap `0x2EC45F93.32bitImage`
			/* 40h */	ResourceObjectPtr field_40;
			/// From bitmap `0x7C6B9FD9.32bitImage`
			/* 44h */	ResourceObjectPtr field_44;
			/// From bitmap `0x88566056.32bitImage`
			/* 48h */	ResourceObjectPtr field_48;
			/// From bitmap `0xF30D0A76.32bitImage`
			/* 4Ch */	ResourceObjectPtr field_4C;
			/// From bitmap `0xC71EF96A.32bitImage`
			/* 50h */	ResourceObjectPtr field_50;
			/// `pcawater.pcaw`
			/* 54h */	ResourceObjectPtr field_54;
			/* 58h */	Math::ColorRGBA nightLightTint;
			/* 68h */	Math::ColorRGBA dayLightColor;
			/* 78h */	Math::ColorRGBA duskLightColor;
			/* 88h */	Math::ColorRGBA nightLightColor;
			/* 98h */	Math::ColorRGBA dayShadowColor;
			/* A8h */	Math::ColorRGBA duskShadowColor;
			/* B8h */	Math::ColorRGBA nightShadowColor;
			/* C8h */	Math::Vector4 duskDawnStartEnd;
			/* D8h */	char padding_D8[0x60];
			/* 138h */	Math::Vector4 waterColor;
			/* 148h */	Math::Vector4 innerParms;
			/* 158h */	Math::Vector4 field_158;
			/* 168h */	Math::Vector4 field_168;
			/* 178h */	Math::Vector4 sunDir;
			/* 188h */	Math::Matrix4 viewTransform;
			/* 1C8h */	Math::Vector4 sphereParms;
			/* 1D8h */	Math::Vector4 camParms;
			/* 1E8h */	Math::Vector4 illumParms;
			/* 1F8h */	Math::Vector4 fogParms;
			/* 208h */	int field_208;
			/* 20Ch */	int field_20C;
			/* 210h */	int field_210;
			/* 214h */	int field_214;
			/* 218h */	int field_218;
			/* 21Ch */	int field_21C;
			/* 220h */	int field_220;
			/* 224h */	int field_224;
			/* 228h */	int field_228;
			/* 22Ch */	int field_22C;
			/* 230h */	int field_230;
			/* 234h */	int field_234;
			/* 238h */	int field_238;
			/* 23Ch */	int field_23C;
			/* 240h */	int field_240;
			/* 244h */	int field_244;
			/* 248h */	int field_248;
			/* 24Ch */	int field_24C;
			/* 250h */	int field_250;
			/* 254h */	int field_254;
			/* 258h */	int field_258;
			/* 25Ch */	int field_25C;
			/* 260h */	int field_260;
			/* 264h */	int field_264;
			/* 268h */	int field_268;
			/* 26Ch */	int field_26C;
			/* 270h */	int field_270;
			/* 274h */	int field_274;
			/* 278h */	int field_278;
			/* 27Ch */	int field_27C;
			/* 280h */	int field_280;
			/* 284h */	int field_284;
			/* 288h */	int field_288;
			/* 28Ch */	int field_28C;
			/* 290h */	int field_290;
			/* 294h */	int field_294;
			/* 298h */	int field_298;
			/* 29Ch */	int field_29C;
			/* 2A0h */	int field_2A0;
			/* 2A4h */	int field_2A4;
			/* 2A8h */	Math::Vector4 field_2A8;
		};
		ASSERT_SIZE(TerrainTextures, 0x2B8);

		cTerrainStateMgr(ITerrain*);

		/* 00h */	ITerrain* mpTerrain;
		/* 04h */	cTerrainMapSet* mpMapSet;
		/* 08h */	TerrainMaterial mMaterial;
		/* 2F4h */	TerrainTextures mTextures;
		/* 5ACh */	bool field_5AC;  // true
		/* 5ADh */	bool field_5AD;
		/* 5B0h */	PropertyListPtr mpMaterialPropList;
		/* 5B4h */	int field_5B4;
		/* 5B8h */	int field_5B8;
		/* 5BCh */	int field_5BC;  // not initialized
		/* 5C0h */	int mAtmosphereType;
		/* 5C4h */	int mWaterType;
		/* 5C8h */	Math::Vector4 field_5C8;
		/* 5D8h */	Math::Vector4 field_5D8;
		/* 5E8h */	Math::Vector4 field_5E8;
		/* 5F8h */	IEffectsWorldPtr field_5F8;
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