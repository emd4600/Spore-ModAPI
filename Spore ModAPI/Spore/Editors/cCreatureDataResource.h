#pragma once

#include <Spore\Resource\ResourceObject.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

namespace Editors
{
	class cCreatureDataResource
		: public Resource::ResourceObject
	{
	public:
		static const uint32_t TYPE = 0x3E1C247;

	public:
		struct UnkStruct
		{
			/* 00h */	int field_0;
			/* 04h */	int field_4;
			/* 08h */	int16_t field_8;
			char padding_0A[0x8C - 0xA];
		};
		ASSERT_SIZE(UnkStruct, 0x8C);

		/* 14h */	int field_14;
		/* 18h */	int field_18[0x20];
		///* 38h */	Math::Vector3 field_38[3];

		/* 98h */	eastl::vector<UnkStruct> field_98;
		/* ACh */	eastl::vector<int> field_AC;
		/* C0h */	eastl::vector<int> field_C0;
		/* D4h */	eastl::vector<int> field_D4;
		/* E8h */	eastl::vector<int> field_E8;
		/* FCh */	eastl::vector<int> field_FC;
		/* 110h */	int field_110;
		/* 114h */	eastl::vector<int> field_114;
	};
	ASSERT_SIZE(cCreatureDataResource, 0x128);
}