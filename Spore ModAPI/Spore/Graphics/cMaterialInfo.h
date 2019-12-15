#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\cMITextureSet.h>
#include <EASTL\vector.h>

using namespace eastl;

namespace Graphics
{
	class cMaterialInfo
	{
	public:
		virtual ~cMaterialInfo();

	protected:
		int mnRefCount;

	public:
		vector<cMITextureSet> field_8;
	};

	ASSERT_SIZE(cMaterialInfo, 0x1C);
}