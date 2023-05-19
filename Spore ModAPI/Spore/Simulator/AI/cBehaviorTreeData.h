#pragma once

#include <Spore\Internal.h>

namespace Simulator
{
	namespace AI
	{
		struct cDecider;
		typedef float(*DecideCallback)(int, float, float, int, bool, int, cDecider*, int);

		typedef bool(*ActivateCallback)(void* pObject, double deltaTime, int, int, int, int);

		struct cBehavior
		{
			/* 00h */	uint32_t mID;
			/* 04h */	ActivateCallback* mpActivateCallback;
			/* 08h */	void* mpTickCallback;
			/* 0Ch */	void* mpDeactivateCallback;
			// Activate(), Tick(), Deactivate()
		};
		ASSERT_SIZE(cBehavior, 0x10);

		struct cDecider
		{
			// sub_BC7F60 calls Decide()

			/* 00h */	uint32_t mID;
			/* 04h */	int field_4;
			/* 08h */	DecideCallback mpDecideCallback;
			/* 0Ch */	int field_C;
			/* 10h */	char padding_10[0xC];
			/* 1Ch */	float field_1C;
			/* 20h */	int field_20;
			/* 24h */	int field_24;
			/* 28h */	char padding_28[0x70 - 0x28];
			/* 70h */	cBehavior* mpBehavior;
			/* 74h */	int field_74;
			/* 78h */	int field_78;
			/* 7Ch */	int mNumChildren;
			/* 80h */	cDecider* mpChildren;
			/* 84h */	int field_84;
		};
		ASSERT_SIZE(cDecider, 0x88);

		class cBehaviorTreeData
		{
			// InitializeTreeData()
			// SetRootDecider()

		public:
			/* 00h */	cDecider* mpRootDecider;
		};
	}
}