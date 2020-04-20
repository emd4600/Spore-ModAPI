#pragma once

#include <EASTL\vector.h>
#include <Spore\RenderWare\RenderWareFile.h>
#include <Spore\RenderWare\KeyframeAnim.h>

namespace Graphics
{
	using namespace eastl;
	using namespace RenderWare;

	// Theorically inside ModelManager, but it's used by Model so...
	class Animations
	{
	public:
		enum Flags
		{
			kFlagMultiblenderEnabled = 0x20
		};

		virtual ~Animations();

		int AddRef();
		int Release();

	public:
		// sub_742910 adds everything

		// sub_798360 process keyframe?
		// It converts from RWAnimChannel to fill SkinMatrixBuffer

		/* 04h */	int mnRefCount;
		/* 08h */	int mFlags;
		/* 0Ch */	int field_C;
		/* 10h */	int field_10;
		/* 14h */	vector<int> field_14;
		// related with SkinsInK, 08h is SkinsInK*
		/* 28h */	vector<int> field_28;
		// related with SkeletonsInK
		/* 3Ch */	vector<int> field_3C;
		/* 50h */	vector<int> field_50;
		// related with SkeletonsInK, used to process animations
		/* 64h */	vector<int> field_64;
		// related with morph handles
		/* 78h */	vector<pair<uint32_t, KeyframeAnim>> mAnimNames;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
		/* 98h */	intrusive_ptr<RenderWareFile> mpRenderWare;
		/* 9Ch */	int field_9C;  // not initialized
	};

	static_assert(sizeof(Animations) == 0xA0, "sizeof(Animations) != A0h");

	inline int Animations::AddRef() {
		++mnRefCount;
		return mnRefCount;
	}
	inline int Animations::Release() {
		--mnRefCount;
		if (mnRefCount == 0) {
			mnRefCount = 1;
			delete this;
			return 0;
		}
		return mnRefCount;
	}
}
