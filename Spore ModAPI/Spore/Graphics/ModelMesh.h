#pragma once

#include <Spore\Internal.h>
#include <Spore\MathUtils.h>
#include <Spore\Transform.h>
#include <Spore\Graphics\IMaterialManager.h>
#include <Spore\Graphics\cMaterialInfo.h>
#include <Spore\Graphics\Animations.h>
#include <Spore\RenderWare\RenderWareFile.h>
#include <EASTL\vector.h>
#include <EASTL\vector_map.h>

#define ModelMeshPtr intrusive_ptr<Graphics::ModelMesh>

namespace Graphics
{
	class ModelMesh
	{
	public:
		ModelMesh();
		virtual ~ModelMesh();

		int AddRef();
		int Release();

	protected:
		/* 04h */	int mnRefCount;

	public:
		/* 08h */	vector<RenderWare::Mesh*> mMeshes;
		/* 1Ch */	vector<int> field_1C;
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
		/* ECh */	ObjectPtr field_EC;
		/* F0h */	intrusive_ptr<Animations> mpAnimations;
		/* F4h */	int field_F4;  // not initialized
		/* F8h */	int field_F8;  // -1
		/* FCh */	int field_FC;  // -1
	};

	ASSERT_SIZE(ModelMesh, 0x100);

	inline int ModelMesh::AddRef() {
		return ++mnRefCount;
	}

	inline int ModelMesh::Release() {
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}
}