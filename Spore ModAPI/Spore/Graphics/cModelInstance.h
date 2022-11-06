#pragma once

#include <Spore\Internal.h>
#include <Spore\MathUtils.h>
#include <Spore\Transform.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\Graphics\cMaterialInfo.h>
#include <Spore\Graphics\cModelInstanceAnimations.h>
#include <Spore\RenderWare\RenderWareFile.h>
#include <EASTL\vector.h>
#include <EASTL\vector_map.h>

#define cModelInstancePtr eastl::intrusive_ptr<Graphics::cModelInstance>

namespace Graphics
{
	class cModelInstance
		: public RefCountTemplate
	{
	public:
		cModelInstance();
		virtual ~cModelInstance();

	public:
		/* 08h */	vector<RenderWare::Mesh*> mMeshes;
		/* 1Ch */	vector<int> mBoneRanges;  // cBoneRange
		/* 30h */	vector<Material*> mMaterials;
		/* 44h */	vector<cMaterialInfoPtr> mMaterialInfos;
		/* 58h */	vector_map<int, cMaterialInfoPtr> mRegionMaterialInfos;
		/* 70h */	Transform field_70;
		/* A8h */	BoundingBox mBoundingBox;
		/* C0h */	float mBoundingRadius;
		/* C4h */	RenderWareFilePtr mpRenderWare;
		/* C8h */	short field_C8;
		/* CCh */	ObjectPtr field_CC;  // related with TriangleKDTreeProcedural
		/* D0h */	int** field_D0;
		/* D4h */	BoundingBox field_D4;  // possibly? uses min and max float
		/* ECh */	ObjectPtr field_EC;  //TODO cIDynamicDraw
		/* F0h */	cModelInstanceAnimationsPtr mpAnimations;
		/* F4h */	int field_F4;  // not initialized
		/* F8h */	int field_F8;  // -1
		/* FCh */	int field_FC;  // -1
	};
	ASSERT_SIZE(cModelInstance, 0x100);
}