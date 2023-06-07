#pragma once

#include <Spore\Internal.h>
#include <Spore\MathUtils.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\ISimulatorSerializable.h>

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
			/* 78h */	int field_78;  // children decision policy
			/* 7Ch */	int mNumChildren;
			/* 80h */	cDecider* mpChildren;
			/* 84h */	int field_84;
		};
		ASSERT_SIZE(cDecider, 0x88);

		struct unk_behavior_state
		{
			struct unk
			{
				/* 00h */	uint32_t field_0;  // a behavior ID
				char padding_4[0xAC];
			};

			/* 00h */	uint32_t mActiveDeciderID;
			/* 04h */	cDecider* mpActiveDecider;
			/* 08h */	uint32_t mActiveBehaviorID;
			/* 0Ch */	int field_C;
			/* 10h */	unk field_10[1];  //TODO
		};

		struct cAgentOrder
		{
			/* 00h */	int mType;
			/* 08h */	cGonzagoTimer mTimeStamp;
			/* 28h */	ISimulatorSerializable* mpTarget;
			/* 2Ch */	Math::Vector3 mOriginalTargetPos;
			/* 38h */	bool mbHasTarget;
			/* 39h */	char mUserData1[20];  // an App::Property?
			/* 4Dh */	char mUserData2[20];  // an App::Property?
			/* 61h */	char mUserData3[20];  // an App::Property?
			/* 75h */	char mUserData4[20];  // an App::Property?
		};
		ASSERT_SIZE(cAgentOrder, 0x90);

		class cBehaviorTreeData
		{
			// InitializeTreeData()
			// SetRootDecider()

		public:
			/* 00h */	cDecider* mpRootDecider;
			//TODO
			/* 04h */	char padding_4[0x5FC - 0x4];
			/* 5FCh */	int mConstantDecisionFlags;
			/* 600h */	char padding600[0x670 - 0x600];
			///* 60Ch */	mOrders;
		};
		ASSERT_SIZE(cBehaviorTreeData, 0x670);
	}
}