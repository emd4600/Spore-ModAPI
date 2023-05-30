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
		struct UnkStruct1
		{
			/* 00h */	Math::Vector3 field_0;  // usualy just position, except for Vertebra and Unk3 rigblock types
			/* 0Ch */	void* field_C;
			/* 10h */	void* field_10;
			/* 14h */	void* field_14;
			/* 18h */	int field_18;
			/* 1Ch */	void* field_1C;
			/* 20h */	int field_20;
			/* 24h */	int field_24;
			/* 28h */	int field_28;
			/* 2Ch */	int field_2C;
			/* 30h */	int field_30;
		};
		ASSERT_SIZE(UnkStruct1, 0x34);

		struct UnkStruct2
		{
			/* 00h */	int field_0;
			/* 04h */	int field_4;
		};
		ASSERT_SIZE(UnkStruct2, 0x8);

		struct UnkStruct3
		{
			/* 00h */	int field_0;
			/* 04h */	float field_4;
			/* 08h */	int field_8;
			/* 0Ch */	int field_C;
			/* 10h */	int field_10;
		};
		ASSERT_SIZE(UnkStruct3, 0x14);
		//TODO check sub_4CA180

		/* 08h */	cCreatureDataResource* mpCreatureData;  //TODO intrusive_ptr?
		/* 0Ch */	eastl::vector<PropertyListPtr> mRigblockPropLists;
		/* 20h */	eastl::vector<int8_t> field_20;
		/* 34h */	int field_34;  // intrusive_ptr, constructor in sub_5078B0
		/* 38h */	int field_38;  // intrusive_ptr, SkinnerSurface? constructor in sub_4F7F70
		/* 3Ch */	float field_3C;
		/* 40h */	eastl::vector<UnkStruct1> field_40;  // size 34h, modified by 4CA3D5
		/* 54h */	eastl::vector<UnkStruct2> field_54;  // size 08h, they are ints
		/* 68h */	eastl::vector<Transform> field_68;
		/* 7Ch */	eastl::vector<UnkStruct3> field_7C;  // size 14h, modified in sub_4CA180
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