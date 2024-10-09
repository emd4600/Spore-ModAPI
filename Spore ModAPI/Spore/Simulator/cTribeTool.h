#pragma once

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <Spore\Simulator\cCombatant.h>
#include <Spore\Simulator\cTribeToolData.h>
#include <Spore\Simulator\cPlaceableStructure.h>

#define cTribeToolPtr eastl::intrusive_ptr<Simulator::cTribeTool>

namespace Simulator
{
	class cTribe;

	class cTribeTool
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
		/* 108h */	, public cBehaviorList
		/* 120h */	, public cCombatant
		/* 1E8h */	, public cPlaceableStructure
	{
	public:
		static const uint32_t TYPE = 0x116D858;
		static const uint32_t NOUN_ID = 0x18C8F0C;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/* 54h */	virtual void func54h(int);  // does nothing
		/* 58h */	virtual int GetToolType();
		/* 5Ch */	virtual const char* GetToolName();  // returns only in English, probably unused
		/* 60h */	virtual void SetToolType(int toolType);
		/* 64h */	virtual void SetTribe(cTribe*);

		/// It returns the tool class (TribeToolClass). It does so by checking the tool data
		/// in GetTribeToolDataArray().
		/// @returns
		int GetToolClass();

		/// Returns how much money can be refunded for this tool. It does so by doing
		/// `(1.0 - GetHealthPercentage()) * toolData.mPrice`. The tool data is obtained 
		/// from GetTribeToolDataArray()
		/// @returns
		int GetRefundMoney();

	public:
		/* 1ECh */	float field_1EC;
		/* 1F0h */	int field_1F0;
		/* 1F4h */	int field_1F4;
		/* 1F8h */	eastl::intrusive_ptr<cTribe> mTribe;
		/* 1FCh */	int mToolType;
		/* 200h */	cGonzagoTimer mCreationTimer;
		/* 220h */	cGonzagoTimer mDestroyedTimer;
		/* 240h */	int field_240;
		/* 244h */	int field_244;
		/* 248h */	int mhFootprint;
	};
	ASSERT_SIZE(cTribeTool, 0x250);

	namespace Addresses(cTribeTool) {
		DeclareAddress(GetToolClass);  // 0xC9CAB0 0xC9D2A0
		DeclareAddress(GetRefundMoney);  // 0xC9C970 0xC9D160
	}
}