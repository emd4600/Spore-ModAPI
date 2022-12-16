#pragma once

#include <Spore\Graphics\Model.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\Graphics\IAmbientOccluder.h>
#include <Spore\Editors\cCreatureDataResource.h>
#include <Spore\Editors\EditorRigblock.h>
#include <Spore\Clock.h>

namespace Editors
{
	class cEditorSkinMeshBase
		: public RefCountTemplateAtomic
	{
	public:
		bool FromRigblocks(EditorRigblock** pRigblocks, int count, eastl::vector<EditorRigblock*>* dstRigblocks = nullptr);

	public:
		/* 08h */	cCreatureDataResource* mpCreatureData;  //TODO intrusive_ptr?
		/* 0Ch */	eastl::vector<PropertyListPtr> mRigblockPropLists;
		/* 20h */	eastl::vector<int8_t> field_20;
		/* 34h */	int field_34;  // intrusive_ptr
		/* 38h */	int field_38;  // intrusive_ptr
		/* 3Ch */	float field_3C;
		/* 40h */	eastl::vector<int> field_40;  // size 34h
		/* 54h */	eastl::vector<int> field_54;  // size 08h
		/* 68h */	eastl::vector<Transform> field_68;
		/* 7Ch */	eastl::vector<int> field_7C;
		/* 90h */	eastl::vector<Math::Rectangle> mUVs;
		/* A4h */	eastl::vector<int> field_A4;
		/* B8h */	cMaterialInfoPtr mpMaterialInfo;
	};
	ASSERT_SIZE(cEditorSkinMeshBase, 0xBC);

	namespace Addresses(cEditorSkinMeshBase)
	{
		DeclareAddress(FromRigblocks);  // 0x4C6E90 0x4C7460
	}

	class cEditorSkinMesh
		: public cEditorSkinMeshBase
		, public Graphics::IAmbientOccluder
	{
	public:
		/* C0h */	eastl::vector<EditorRigblockPtr> mRigblocks;
		/* D4h */	MaterialPtr mpMaterial;
		/* D8h */	uint32_t mInstanceID;
		/* DCh */	uint32_t mGroupID;
		/* E0h */	ModelPtr mpModel;
		/* E4h */	eastl::vector<int> field_E4;
		/* F8h */	int field_F8;
		/* FCh */	TexturePtr mDiffuseTexture;
		/* 100h */	TexturePtr mNSpecTexture;
		/* 104h */	bool field_104;
		/* 105h */	bool field_105;
		/* 108h */	Clock mClock;
		/* 120h */	float mSkinResolutionRealtime;
		/* 124h */	float mSkinResolutionHQ;
		/* 128h */	float mSkinResolutionHQ2;
	};
	ASSERT_SIZE(cEditorSkinMesh, 0x130);
}