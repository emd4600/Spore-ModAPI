#pragma once

#include <Spore\Swarm\cGlobalParams.h>
#include <Spore\Swarm\Components\cDistributeDescription.h>
#include <Spore\Swarm\IComponent.h>
#include <Spore\Swarm\IEffectMap.h>
#include <Spore\Swarm\ISurface.h>
#include <Spore\Swarm\ParticleStreamers.h>

namespace Swarm
{
	class cDistributeEffect
		/* 00h */	: public cComponentBase
		/* 0Ch */	, public ITextureParticleStreamer
		/* 10h */	, public IModelParticleStreamer
	{
	public:
		/* 14h */	cDistributeDescription* mpDescription;
		/* 18h */	int field_18;
		/* 1Ch */	IEffectsWorld* mpEffectsWorld;
		/* 20h */	cGlobalParams* mpGlobalParams;
		/* 24h */	cEffectParams* mpEffectParams;
		/* 28h */	int field_28;
		/* 2Ch */	Transform field_2C;
		/* 64h */	Transform field_64;
		/* 9Ch */	int field_9C;
		/* A0h */	float mAltitudeRange[2];  // -10000.0, 10000.0
		/* A8h */	eastl::vector<int> field_A8;
		/* BCh */	eastl::vector<int> field_BC;
		/* D0h */	int field_D0;
		/* D4h */	int field_D4;
		/* D8h */	eastl::vector<int> field_D8;
		/* ECh */	int field_EC;  // -1
		/* F0h */	int field_F0;  // -1
		/* F4h */	int field_F4;  // -1
		/* F8h */	bool field_F8;
		/* FCh */	int field_FC;  // not initialized
		/* 100h */	Math::BoundingBox field_100;
		/* 118h */	int field_118;
		/* 11Ch */	eastl::vector<cSurfaceRec> mSurfaces;
		/* 130h */	eastl::vector<uint8_t> field_130;
		/* 144h */	eastl::vector<int> field_144;
		/* 158h */	int field_158;
		/* 15Ch */	IEffectMapPtr mpEmitMap;
		/* 160h */	IEffectMapPtr mpColorMap;
		/* 164h */	IEffectMapPtr mpPinMap;
		/* 168h */	int mEmitMapModificationCount;
		/* 16Ch */	int field_16C;  // not initialized
		/* 170h */	float field_170;  // 1.0
		/* 174h */	float field_174;  // 1.0
		/* 178h */	float field_178;  // 1.0
		/* 17Ch */	float field_17C;  // 1.0
		/* 180h */	float field_180;  // 1.0
		/* 184h */	float field_184;  // 1.0
		/* 188h */	float field_188;  // 1.0
		/* 18Ch */	float field_18C;  // 1.0
		/* 190h */	int field_190;
		/* 194h */	int field_194;  // 1
		/* 198h */	int field_198;  // not initialized
		/* 19Ch */	eastl::vector<int> field_19C;
	};
	ASSERT_SIZE(cDistributeEffect, 0x1B0);
}