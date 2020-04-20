#pragma once

#include <Spore\Internal.h>
#include <Spore\Graphics\cMITextureSet.h>
#include <EASTL\vector.h>

#define cMaterialInfoPtr intrusive_ptr<Graphics::cMaterialInfo>

namespace Graphics
{
	class cMaterialInfo
	{
	public:
		virtual ~cMaterialInfo();

		int AddRef();
		int Release();

	protected:
		int mnRefCount;

	public:
		vector<cMITextureSet*> field_8;
	};

	ASSERT_SIZE(cMaterialInfo, 0x1C);
}