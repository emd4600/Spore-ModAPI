#pragma once

#include <EASTL\vector.h>
#include <Spore\RenderWare\RenderWareFile.h>

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

	public:
		// sub_742910 adds everything

		/* 04h */	int mnRefCount;
		/* 08h */	int mFlags;
		/* 0Ch */	int field_C;
		/* 10h */	int field_10;
		/* 14h */	vector<int> field_14;
		/* 28h */	vector<int> field_28;
		// related with SkeletonsInK
		/* 3Ch */	vector<int> field_3C;
		/* 50h */	vector<int> field_50;
		/* 64h */	vector<int> field_64;
		/* 78h */	vector<int> field_78;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
		/* 98h */	intrusive_ptr<RenderWareFile> mpRenderWare;
		/* 9Ch */	int field_9C;  // not initialized
	};

	static_assert(sizeof(Animations) == 0xA0, "sizeof(Animations) != A0h");
}