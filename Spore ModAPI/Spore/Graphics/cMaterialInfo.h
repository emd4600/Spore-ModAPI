#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\cMITextureSet.h>
#include <EASTL\vector.h>

#define cMaterialInfoPtr eastl::intrusive_ptr<Graphics::cMaterialInfo>

namespace Graphics
{
	class cMaterialInfo
		: public RefCountTemplateAtomic
	{
	public:
		virtual ~cMaterialInfo();

	public:
		//TODO this is actually just generic data, can be anything
		eastl::vector<cMITextureSet*> mData;
	};
	ASSERT_SIZE(cMaterialInfo, 0x1C);
}