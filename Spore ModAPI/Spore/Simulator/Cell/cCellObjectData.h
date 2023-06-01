#pragma once

#include <Spore\Simulator\Cell\cCellResource.h>
#include <Spore\Simulator\cObjectPool.h>
#include <Spore\MathUtils.h>
#include <Spore\Transform.h>

namespace Simulator
{
	namespace Cell
	{
		struct cCellQueryLinkedPool;

		struct cCellObjectData 
			: public cObjectPoolClass
		{
			//TODO 224h 230h 238h are related with chaseTime; check sub_E57E90 

			/* 04h */	bool mIsIdle;
			/// Target position, changing this moves the cell towards the target
			/* 08h */	Math::Vector3 mTargetPosition;
			/* 14h */	Math::Quaternion mTargetOrientation;
			/* 24h */	Math::Vector3 field_24;
			/* 30h */	Math::Vector3 field_30;
			/* 3Ch */	int field_3C;
			/* 40h */	int field_40;
			/* 44h */	float field_44;
			/* 48h */	Transform mTransform;
			/// Elevation of the cell relative to the current level
			/* 80h */	float mRelativeElevation;
			/* 84h */	Math::Vector3 field_84;
			/* 90h */	Math::Vector3 field_90;
			/* 9Ch */	int field_9C;
			/* A0h */	float mOpacity;
			/* A4h */	float mTargetOpacity;  // changed by sub_E7C510
			/* A8h */	float field_A8;
			/* ACh */	float field_AC;
			/* B0h */	int field_B0;
			/* B4h */	float mTargetSize;
			/* B8h */	float field_B8;
			/* BCh */	float field_BC;
			/* C0h */	Transform field_C0;
			/* F8h */	int field_F8;
			/* FCh */	ResourceKey mModelKey;
			/* 108h */	cCellDataReference<cCellCellResource>* mCellResource;
			/* 10Ch */	int field_10C;
			/* 110h */	bool field_110;
			/* 111h */	bool mIsInvulnerable;
			/* 112h */	bool field_112;
			/* 113h */	bool field_113;
			/* 114h */	int field_114;
			/* 118h */	int field_118;
			/* 11Ch */	int field_11C;
			/* 120h */	int field_120;
			/* 124h */	int field_124;
			/* 128h */	int field_128;
			/* 12Ch */	Math::Vector3 field_12C;
			/* 138h */	Math::Vector3 field_138;
			/* 144h */	int field_144;
			/* 148h */	int field_148;
			/* 14Ch */	int field_14C;
			/* 150h */	float field_150;
			/* 154h */	int field_154;  // probably float
			/* 158h */	int field_158;
			/* 15Ch */	float field_15C;
			/* 160h */	int field_160;
			/* 164h */	int field_164;
			/* 168h */	int field_168;
			/* 16Ch */	int field_16C;
			/* 170h */	int field_170;
			/* 174h */	int field_174;
			/* 178h */	int field_178;
			/* 17Ch */	int field_17C;
			/* 180h */	int field_180;
			/* 184h */	int field_184;
			/* 188h */	int field_188;
			/* 18Ch */	int field_18C;
			/* 190h */	int field_190;
			/* 194h */	int field_194;
			/* 198h */	int field_198;
			/* 19Ch */	int field_19C;
			/* 1A0h */	int field_1A0;
			/* 1A4h */	int field_1A4;
			/* 1A8h */	int field_1A8;
			/* 1ACh */	int field_1AC;
			/* 1B0h */	int field_1B0;
			/* 1B4h */	int field_1B4;
			/* 1B8h */	int field_1B8;
			/* 1BCh */	int field_1BC;
			/* 1C0h */	float field_1C0;
			/* 1C4h */	int field_1C4;
			/* 1C8h */	int field_1C8;
			/* 1CCh */	int field_1CC;
			/* 1D0h */	float field_1D0;
			/* 1D4h */	int field_1D4;
			/* 1D8h */	int field_1D8;
			/* 1DCh */	int field_1DC;
			/* 1E0h */	int field_1E0;
			/* 1E4h */	int field_1E4;
			/* 1E8h */	int field_1E8;
			/* 1ECh */	int field_1EC;
			/* 1F0h */	int field_1F0;
			/* 1F4h */	int field_1F4;
			/* 1F8h */	int field_1F8;
			/* 1FCh */	Math::Vector3 field_1FC;
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
			/* 234h */	float mSpawnTime;
			/* 238h */	int field_238;
			/* 23Ch */	int field_23C;
			/* 240h */	int field_240;
			/// Current health points of the cell, the maximum is 6.
			/* 244h */	int mHealthPoints;
			/// Index to the object in cCellGFX::mCellGFXObjects that visually represents this cell (its model, animated creature, etc.)
			/* 248h */	cObjectPoolIndex mGFXObjectIndex;
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
			/* 2A8h */	int field_2A8;
			/* 2ACh */	int field_2AC;
			/* 2B0h */	int field_2B0;
			/* 2B4h */	int field_2B4;
			/* 2B8h */	int field_2B8;
			/* 2BCh */	int field_2BC;
			/* 2C0h */	int field_2C0;
			/* 2C4h */	int field_2C4;
			/* 2C8h */	int field_2C8;
			/* 2CCh */	int field_2CC;
			/* 2D0h */	int field_2D0;
			/* 2D4h */	int field_2D4;
			/* 2D8h */	int field_2D8;
			/* 2DCh */	int field_2DC;
			/* 2E0h */	int field_2E0;
			/* 2E4h */	int field_2E4;
			/* 2E8h */	int field_2E8;
			/* 2ECh */	int field_2EC;
			/* 2F0h */	int field_2F0;
			/* 2F4h */	int field_2F4;
			/* 2F8h */	int field_2F8;
			/* 2FCh */	int field_2FC;
			/* 300h */	int field_300;
			/* 304h */	int field_304;
			/* 308h */	int field_308;
			/* 30Ch */	int field_30C;
			/* 310h */	int field_310;
			/* 314h */	int field_314;
			/* 318h */	int field_318;
			/* 31Ch */	int field_31C;
			/* 320h */	int field_320;
			/* 324h */	int field_324;
			/* 328h */	int field_328;
			/* 32Ch */	int field_32C;
			/* 330h */	int field_330;
			/* 334h */	int field_334;
			/* 338h */	int field_338;
			/* 33Ch */	int field_33C;
			/* 340h */	int field_340;
			/* 344h */	int field_344;
			/* 348h */	int field_348;
			/* 34Ch */	int field_34C;
			/* 350h */	int field_350;
			/* 354h */	bool field_354;
			/// Level of the cell, -1 for the player
			/* 358h */	CellStageScale mScale;
			/* 35Ch */	cCellQueryLinkedPool* mpQuery;
			/* 360h */	void* field_360;
			/* 364h */	int field_364;
			/* 368h */	float field_368;
			/* 36Ch */	int field_36C;
			/* 370h */	int field_370;
			/* 374h */	float field_374;
			/* 378h */	int field_378;
			/* 37Ch */	int field_37C;
			/* 380h */	int field_380;
			/* 384h */	int field_384;
			/* 388h */	int field_388;
			/* 38Ch */	int field_38C;
			/* 390h */	int field_390;
			/* 394h */	int field_394;
		};
		ASSERT_SIZE(cCellObjectData, 0x398);
	}
}