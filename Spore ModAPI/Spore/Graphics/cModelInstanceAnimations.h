#pragma once

#include <EASTL\vector.h>
#include <Spore\RenderWare\RenderWareFile.h>
#include <Spore\RenderWare\KeyframeAnim.h>
#include <Spore\RenderWare\SkeletonsInK.h>

#define cModelInstanceAnimationsPtr eastl::intrusive_ptr<Graphics::cModelInstanceAnimations>

namespace Graphics
{
	class cModelInstanceAnimations
	{
	public:
		enum Flags
		{
			kFlagMultiblenderEnabled = 0x20
		};

		virtual ~cModelInstanceAnimations();

		int AddRef();
		int Release();

	public:
		struct InternalRenderWareData
		{
			/* 00h */	int field_0;
			/* 04h */	bool field_4;
			/* 05h */	bool field_5;
			/* 08h */	void* mpData;  // pointer to RenderWare section data
		};
		ASSERT_SIZE(InternalRenderWareData, 0xC);
		// sub_742910 adds everything

		// sub_798360 process keyframe?
		// It converts from RWAnimChannel to fill SkinMatrixBuffer

		/* 04h */	int mnRefCount;
		/* 08h */	int mFlags;
		/* 0Ch */	int field_C;
		/* 10h */	int field_10;
		/* 14h */	eastl::vector<int> mAnimationGroups;  //TODO cAnimGroupInfo
		// related with SkinsInK, 08h is SkinsInK*
		/* 28h */	eastl::vector<int> field_28;
		// related with SkeletonsInK
		/* 3Ch */	eastl::vector<InternalRenderWareData> mSkeletonsInK;  //TODO cAnimInfo
		/* 50h */	eastl::vector<InternalRenderWareData> mBlendShapeConfig;
		// related with SkeletonsInK, used to process animations
		/* 64h */	eastl::vector<int> field_64;
		// related with morph handles
		/* 78h */	eastl::vector<eastl::pair<uint32_t, RenderWare::KeyframeAnim>> mAnimNames;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
		/* 98h */	RenderWareFilePtr mpRenderWare;
		/* 9Ch */	int field_9C;  // not initialized
	};
	ASSERT_SIZE(cModelInstanceAnimations, 0xA0);

	inline int cModelInstanceAnimations::AddRef() {
		++mnRefCount;
		return mnRefCount;
	}
	inline int cModelInstanceAnimations::Release() {
		--mnRefCount;
		if (mnRefCount == 0) {
			mnRefCount = 1;
			delete this;
			return 0;
		}
		return mnRefCount;
	}
}
