#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\App\ICameraManager.h>
#include <Spore\App\PropertyList.h>
#include <Spore\Swarm\IEffectsManager.h>
#include <Spore\Graphics\IModelWorld.h>

#define cWeatherManagerPtr eastl::intrusive_ptr<Terrain::cWeatherManager>

namespace Terrain
{
	class ITerrain;
	struct cTerrainStateMgr;
	class cTerrainMapSet;

	class UnkWeatherManager
	{
	public:
		virtual ~UnkWeatherManager();

		int field_4;
	};

	class cWeatherManager
		: public UnkWeatherManager
		, public App::IMessageListener
	{
	public:
		static const uint32_t WORLD_ID = 0x611C912;

		template <typename T>
		struct PropertyContainer
		{
			T value;
			PropertyListPtr propList;
			uint32_t id;
			int operationsCount;
		};

		/* 0Ch */	IEffectsWorldPtr mpEffectWorld;
		/* 10h */	int field_10;
		/* 14h */	IVisualEffectPtr mpLowAtmoEffect;
		/* 18h */	IVisualEffectPtr mpMidAtmoEffect;
		/* 1Ch */	IVisualEffectPtr mpHighAtmoEffect;
		/* 20h */	IVisualEffectPtr mpLoopBoxAtmoEffect;
		/* 24h */	IVisualEffectPtr mpLoopBoxGroundEffect;
		/* 28h */	IVisualEffectPtr field_28;
		/* 2Ch */	IVisualEffectPtr field_2C;
		/* 30h */	IVisualEffectPtr field_30;
		/* 34h */	IVisualEffectPtr field_34;
		/* 38h */	uint32_t mLowAtmoEffectID;
		/* 3Ch */	uint32_t mMidAtmoEffectID;
		/* 40h */	uint32_t mHighAtmoEffectID;
		/* 44h */	int field_44;  // not initialized
		/* 48h */	uint32_t mLoopBoxAtmoEffectID;
		/* 4Ch */	uint32_t mLoopBoxGroundEffectID;
		/* 50h */	int field_50;
		/* 54h */	uint32_t mColdStormLoopboxID;
		/* 58h */	uint32_t mWarmStormLoopboxID;
		/* 5Ch */	uint32_t mHotStormLoopboxID;
		/* 60h */	uint32_t mIceAmbientEffectID;
		/* 64h */	uint32_t mColdAmbientEffectID;
		/* 68h */	uint32_t mAmbientLoopboxID;  // 0x39FAA0F in init method, depends on weatherAmbientLoopboxType
		/* 6Ch */	uint32_t mHotAmbientEffectID;
		/* 70h */	uint32_t mLavaAmbientEffectID;
		/* 74h */	int field_74;
		/* 78h */	uint32_t mColdStormEffectID;
		/* 7Ch */	uint32_t mWarmStormEffectID;
		/* 80h */	uint32_t mHotStormEffectID;
		/* 84h */	int field_84;
		/* 88h */	uint32_t mColdLocalStormEffectID;
		/* 8Ch */	uint32_t mWarmLocalStormEffectID;
		/* 90h */	uint32_t mHotLocalStormEffectID;
		/* 94h */	int field_94;
		/* 98h */	int mRainRampMS;  // 3000
		/* 9Ch */	float mRainDarkness;  // 0.3
		/* A0h */	int field_A0;
		/* A4h */	uint32_t mEvaporationEffectID;
		/* A8h */	uint32_t mFreezeEffectID;
		/* ACh */	bool mEffectsAreLoaded;
		/* ADh */	bool mInitialized;
		/* B0h */	PropertyContainer<int> mWeatherLevel;
		/* C0h */	PropertyContainer<bool> mWeatherOn;
		/* D0h */	int field_D0;
		/* D4h */	IModelWorldPtr mpModelWorld;
		/* D8h */	IEffectsManagerPtr mpEffectsMgr;
		/* DCh */	ICameraManagerPtr mpCameraMgr;
		/* E0h */	ITerrain* mpTerrain;
		/* E4h */	cTerrainStateMgr* mpTerrainStateMgr;
		/* E8h */	cTerrainMapSet* mpTerrainMapSet;
		/* ECh */	float field_EC;
		/* F0h */	float field_F0;
		/* F4h */	float field_F4;
		/* F8h */	float field_F8;
		/* FCh */	float field_FC;
		/* 100h */	ColorRGB mIceCloudColor;  // 0.95
		/* 10Ch */	ColorRGB mColdCloudColor;  // 0.95
		/* 118h */	ColorRGB mWarmCloudColor;  // 0.95
		/* 124h */	ColorRGB mHotCloudColor;  // 0.625, 0.525, 0.475
		/* 130h */	ColorRGB mLavaCloudColor;  // 0.3, 0.1, 0.95
		/* 13Ch */	int field_13C;  // 9
		/* 140h */	int field_140;  // 9
		/* 144h */	int field_144;  // not initialized
		/* 148h */	ResourceID mCloudID;  // init functions sets to 599EC0AB, depends on weatherCloudType
		/* 150h */	int field_150;  // 5
		/* 154h */	int field_154;  // 5
		/* 158h */	int field_158;  // 3
		/* 15Ch */	int field_15C;  // 3
		/* 160h */	int field_160;  // 5
		/* 164h */	int mJetStreamMidRes;  //PLACEHOLDER
		/* 168h */	int field_168;
		/* 16Ch */	bool field_16C;  // not initialized
		/* 16Dh */	bool field_16D;  // not initialized
		/* 170h */	eastl::vector<IVisualEffectPtr> field_170;
		/* 184h */	RandomNumberGenerator mRNG;
		/* 188h */	PropertyListPtr mpPropList;
		/* 18Ch */	int mPropOpCount;  // -1
		/* 190h */	float mAtmoTempChange;  // 0.1
		/* 194h */	float mCloudTrailDecay;  // 0.1
		/* 198h */	float mWriteForceDecay;  // 0.1
		/* 19Ch */	int mMaxNumStorms;  // 5
	};
	
	ASSERT_SIZE(cWeatherManager, 0x1A0);
}