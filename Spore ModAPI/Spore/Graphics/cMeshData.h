#pragma once

#include <Spore\RenderWare\RWMath.h>
#include <Spore\Object.h>
#include <EASTL\vector.h>

#define cMeshDataPtr eastl::intrusive_ptr<Graphics::cMeshData>

namespace Graphics
{
	class cMeshData
		: public IVirtual
	{
	public:
		/* 04h */	int mnRefCount;
		/* 08h */	vector<int> mElementsArray;  // cMDElementArray
		/* 1Ch */	vector<int> mSections;  // cMDSection
		/* 30h */	vector<int> mPrimitives;  // cMDPrimitive
		/* 44h */	vector<int> field_44;  // ObjectPtr
	};
	ASSERT_SIZE(cMeshData, 0x58);
}