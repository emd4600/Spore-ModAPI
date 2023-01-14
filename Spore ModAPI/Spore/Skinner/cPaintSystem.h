#pragma once

#include <Spore\Skinner\cSkinPainter.h>
#include <Spore\Editors\cEditorSkinMesh.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\cJob.h>
#include <Spore\MathUtils.h>
#include <EASTL\fixed_vector.h>

#define PaintSystem (*Skinner::cPaintSystem::Get())

namespace Skinner
{
#ifndef SDK_TO_GHIDRA
	Math::ColorRGB* GetCurrentColors();
#else
	Math::ColorRGB sCurrentColors[3];
#endif

	struct cSkinpaintInfo
	{
		/* 00h */	Math::Vector3 field_0;
		/* 0Ch */	Math::Vector3 field_C;
		/* 18h */	float field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	int mDelay;
		/* 24h */	int mLife;
		/* 28h */	uint32_t mSeed;
		/* 2Ch */	ObjectPtr mData;
		/* 30h */	int field_30;
		/* 34h */	int field_34;
	};
	ASSERT_SIZE(cSkinpaintInfo, 0x38);

	class cPaintSystem
		: public App::IMessageListener
		, public RefCountTemplate
	{
	public:
		static cPaintSystem* Get();

		cSkinPainter* GetPainter();

		Editors::cEditorSkinMesh* GetSkinMesh();

	public:
		/* 0Ch */	cSkinPainter* mpPainter;
		/* 10h */	int field_10;
		/* 14h */	int mpMeshAORender;
		/* 18h */	int field_18;
		/* 1Ch */	int field_1C;
		/* 20h */	Editors::cEditorSkinMesh* mpSkinMesh;  // not initialized
		/* 24h */	Math::BoundingBox field_24;
		/* 3Ch */	eastl::vector<cSkinpaintInfo> mSkinpaintInfos;
		/* 50h */	char padding_50[0x80 - 0x50]; //TODO 54h is RNG?  //TODO 7Dh ambient occlusion run?
		/* 80h */	eastl::vector<int> field_80;
		/* 94h */	eastl::fixed_vector<int, 16> field_94;
		/* ECh */	int field_EC;  // not initialized
		/* F0h */	int field_F0;
		/* F4h */	int field_F4;
		/* F8h */	cJobPtr field_F8;
		/* FCh */	cJobPtr mpUVUnwrapJob;
		/* 100h */	int field_100;
		/* 104h */	int field_104;
	};
	ASSERT_SIZE(cPaintSystem, 0x108);

	namespace Addresses(cPaintSystem)
	{
		DeclareAddress(Get);  // 0x401080 0x401080
	}

	inline cSkinPainter* cPaintSystem::GetPainter()
	{
		return mpPainter;
	}

	inline Editors::cEditorSkinMesh* cPaintSystem::GetSkinMesh()
	{
		return mpSkinMesh;
	}
}

namespace Addresses(Skinner)
{
	DeclareAddress(GetCurrentColors);  // 0x15E3370 0x15DF0F0
}