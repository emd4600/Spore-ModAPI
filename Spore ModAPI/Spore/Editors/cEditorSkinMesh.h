#pragma once

#include <Spore\Graphics\Model.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\Graphics\IAmbientOccluder.h>
#include <Spore\Editors\cCreatureDataResource.h>
#include <Spore\Clock.h>

namespace Editors
{
	class cEditorSkinMeshBase
		: public RefCountTemplateAtomic
	{
	public:
		/* 08h */	cCreatureDataResource* mpCreatureData;  //TODO intrusive_ptr?
		/* 0Ch */	eastl::vector<PropertyListPtr> mRigblockPropLists;
		/* 20h */	eastl::vector<int> field_20;
		/* 34h */	int field_34;
		/* 38h */	int field_38;
		/* 3Ch */	float field_3C;
		/* 40h */	eastl::vector<int> field_40;  // size 34h
		/* 54h */	eastl::vector<int> field_54;  // size 08h
		/* 68h */	eastl::vector<Transform> field_68;
		/* 7Ch */	eastl::vector<int> field_7C;
		/* 90h */	eastl::vector<Math::Rectangle> mUVs;
		/* A4h */	eastl::vector<int> field_A4;
		/* B8h */	int field_B8;
	};
	ASSERT_SIZE(cEditorSkinMeshBase, 0xBC);

	class cEditorSkinMesh
		: public cEditorSkinMeshBase
		, public Graphics::IAmbientOccluder
	{
	public:
		/* C0h */	eastl::vector<int> field_C0;
		/* D4h */	MaterialPtr mpMaterial;
		/* D8h */	uint32_t mInstanceID;
		/* DCh */	uint32_t mGroupID;
		/* E0h */	ModelPtr mpModel;
		/* E4h */	eastl::vector<int> field_E4;
		/* F8h */	int field_F8;
		/* FCh */	TexturePtr field_FC;
		/* 100h */	TexturePtr field_100;
		/* 104h */	bool field_104;
		/* 105h */	bool field_105;
		/* 108h */	Clock mClock;
		/* 120h */	float mSkinResolutionRealtime;
		/* 124h */	float mSkinResolutionHQ;
		/* 128h */	float mSkinResolutionHQ2;
	};
	ASSERT_SIZE(cEditorSkinMesh, 0x130);
}