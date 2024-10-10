#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cHitSphere.h>

#define cTribeHutPtr eastl::intrusive_ptr<Simulator::cTribeHut>

namespace Simulator
{
	class cTribe;

	class cTribeHut
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
		/* 108h */	, public cBehaviorList
		/* 120h */	, public cCombatant
	{
	public:
		static const uint32_t TYPE = 0xEE02C7;
		static const uint32_t NOUN_ID = 0x1E4DAAE;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/* 54h */	virtual void SetTribe(cTribe* tribe);
		/* 58h */	virtual cTribe* GetTribe();
		/* 5Ch */	virtual cTribe* GetTribe2();
		/* 60h */	virtual void func60h(int);

	public:
		/* 1E8h */	ResourceKey mDestructModelLo;
		/* 1F4h */	ResourceKey mDestructModelMd;
		/* 200h */	ResourceKey mDestructModelHi;
		/* 20Ch */	ResourceKey mUndamagedModel;
		/* 218h */	bool mbEmitHarpMusic;
		/// values above 0 make the hut emit a 'zzz' sleeping effect
		/* 21Ch */	int mIsSleeping; 
		/* 220h */	bool field_220;
		/* 221h */	bool field_221;
		/* 224h */	int field_224;  // not initialized
		/* 228h */	int field_228;
		/* 22Ch */	int field_22C;
		/* 230h */	eastl::intrusive_ptr<cTribe> mpTribe;
		/* 234h */	cHitSpherePtr mpHitSphere;
		/* 238h */	int field_238;
		/* 240h */	cGonzagoTimer field_240;
	};
	ASSERT_SIZE(cTribeHut, 0x260);
}