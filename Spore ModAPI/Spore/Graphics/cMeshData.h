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
		/* 08h */	eastl::vector<int> mElementsArray;  // cMDElementArray
		/* 1Ch */	eastl::vector<int> mSections;  // cMDSection
		/* 30h */	eastl::vector<int> mPrimitives;  // cMDPrimitive
		/* 44h */	eastl::vector<int> field_44;  // ObjectPtr
	};
	ASSERT_SIZE(cMeshData, 0x58);
}