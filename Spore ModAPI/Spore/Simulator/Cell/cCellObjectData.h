#pragma once

#include <Spore\Simulator\Cell\cCellResource.h>
#include <Spore\Simulator\cObjectPool.h>
#include <Spore\MathUtils.h>
#include <Spore\Transform.h>

namespace Simulator
{
	namespace Cell
	{
		struct cCellObjectData : public cObjectPoolClass
		{
			//TODO 224h 230h 238h are related with chaseTime; check sub_E57E90 

			/* 04h */	bool mIsIdle;
			/* 08h */	Math::Vector3 mTargetPosition;
			/* 14h */	Math::Quaternion mTargetOrientation;
			/* 24h */	char padding_24[0x48 - 0x24];
			/* 48h */	Transform mTransform;
			/* 80h */	float field_80;
			/* 84h */	char padding_84[0x90 - 0x84];
			/* 90h */	Math::Vector3 field_90;
			/* 9Ch */	int field_9C;
			/* A0h */	float field_A0;
			/* A4h */	float field_A4;
			/* A8h */	float field_A8;
			/* ACh */	float field_AC;
			/* B0h */	int field_B0;
			/* B4h */	float mSize;
			/* B8h */	float field_B8;
			/* BCh */	float field_BC;
			/* C0h */	Transform field_C0;
			/* F8h */	int field_F8;
			/* FCh */	ResourceKey mModelKey;
			/* 108h */	cCellDataReference<cCellCellResource>* mCellResource;
			/* 10Ch */	int field_10C;
			/* 110h */	bool field_110;
			/* 111h */	bool field_111;
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
			/* 154h */	int field_154;
			/* 158h */	int field_158;
			/* 15Ch */	int field_15C;
			/* 160h */	char padding_160[0x1C0 - 0x160];
			/* 1C0h */	float field_1C0;
			/* 1C4h */	char padding_1C4[0x1D0 - 0x1C4];
			/* 1D0h */	float field_1D0;
			/* 1D4h */	char padding_1D4[0x1FC - 0x1D4];
			/* 1FCh */	Math::Vector3 field_1FC;
			/* 208h */	char padding_208[0x234 - 0x208];
			/* 234h */	float mSpawnTime;
			/* 238h */	char padding_238[0x244 - 0x238];
			/* 244h */	int mHealthPoints;
			/* 248h */	int field_248;
			/* 24Ch */	int field_24C;
			/* 250h */	int field_250;
			/* 254h */	char padding_254[0x354 - 0x254];
			/* 354h */	bool field_354;
			/// Level of the cell, -1 for the player
			/* 358h */	CellStageScale mScale;
			/* 35Ch */	int field_35C;
			/* 360h */	char padding_360[0x368 - 0x360];
			/* 368h */	float field_368;
			/* 36Ch */	int field_36C;
			/* 370h */	int field_370;
			/* 374h */	float field_374;
			/* 378h */	char padding_378[0x398 - 0x378];
		};
		ASSERT_SIZE(cCellObjectData, 0x398);
	}
}