#pragma once

#include <Spore\Resource\ResourceObject.h>
#include <Spore\Graphics\cMaterialInfo.h>

namespace Graphics
{
	//TODO cGameModelResource
	class GmdlRenderAsset
		: public Resource::ResourceObject
	{
		static const uint32_t TYPE = 0xE6BCE5;  // gmdl

		/* F4h */	vector<intrusive_ptr<cMaterialInfo>> mMaterialInfos;
	};
}