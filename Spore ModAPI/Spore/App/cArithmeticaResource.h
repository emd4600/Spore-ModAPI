#pragma once

#include <Spore\Resource\ResourceObject.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>

namespace App
{
	class cArithmeticaResource
		: public Resource::CachedResourceObject
	{
	public:
		static const uint32_t TYPE = 0x355D6F5;

	public:
		struct OperationDefinition
		{
			/* 00h */	int field_0;  // 9
			/* 04h */	float field_4;
			/* 08h */	int field_8;  // -1, index to mVariableNames
			/* 0Ch */	int field_C;  // not initialized
		};
		ASSERT_SIZE(OperationDefinition, 0x10);

		struct ArithmeticaState
		{
			/* 00h */	eastl::vector<float> mStack;
			/* 14h */	eastl::vector<int> field_6C;
		};
		ASSERT_SIZE(ArithmeticaState, 0x28);

		/* 18h */	eastl::vector<eastl::string> mVariableNames;
		/* 2Ch */	eastl::vector<float> mVariableValues;
		/* 40h */	eastl::vector<OperationDefinition> mOperators;
		/* 54h */	int field_54;  // not initialized
		/* 58h */	ArithmeticaState mState;
		/* 80h */	eastl::vector<Math::Vector2> field_80;
	};
	ASSERT_SIZE(cArithmeticaResource, 0x94);
}
