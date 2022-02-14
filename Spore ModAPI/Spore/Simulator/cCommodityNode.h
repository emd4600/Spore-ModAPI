#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cVehicle.h>

#define cCommodityNodePtr eastl::intrusive_ptr<Simulator::cCommodityNode>

namespace Simulator
{
	class cCommodityNode
		: public cGameData
		, public cSpatialObject
		, public cCombatant
	{
	public:
		static const uint32_t TYPE = 0x403DF5F;
		static const uint32_t NOUN_ID = 0x403DF5C;

		/* 1D0h */	float mResourcePoints;  // 100.0
		/* 1D4h */	float mMaxResourcePoints;  // 100.0
		/* 1D8h */	cGameDataPtr mpHitSphere;  //PLACEHOLDER cHitSphere
		/* 1DCh */	int field_1DC;
		/* 1E0h */	cVehiclePtr mConstructingVehicle;
		/* 1E4h */	bool mbMineInitialized;
		/* 1E5h */	bool field_1E5;
		/* 1E6h */	bool field_1E6;
		/* 1E7h */	bool field_1E7;
		/* 1E8h */	bool field_1E8;
		/* 1E9h */	bool field_1E9;
		/* 1ECh */	int mMineState;
		/* 1F0h */	cGonzagoTimer mMineStateTimer;
		/* 210h */	int mMineStateTimeout;
		/* 214h */	uint32_t mConstructingPoliticalID;
		/* 218h */	uint32_t mCapturePoliticalID;
		/* 21Ch */	uint32_t mConvertPoliticalID;
		/* 220h */	uint32_t mBuyPoliticalID;
		/* 224h */	float mCapturePercent;
		/* 228h */	float mConvertPercent;
		/* 22Ch */	float mBuyPercent;
		/* 230h */	deque<ObjectPtr> field_230;
		/* 25Ch	*/	int field_25C;  // not initialized
		/* 260h	*/	int field_260;
		/* 264h */	int field_264;
		/* 268h */	cGonzagoTimer field_268;
		/* 288h */	int field_288;
	};
	ASSERT_SIZE(cCommodityNode, 0x290);
}