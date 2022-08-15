#pragma once

#include <Spore\Simulator\cCreatureBase.h>
#include <Spore\Simulator\cHitSphere.h>

#define cCreatureCitizenPtr intrusive_ptr<Simulator::cCreatureCitizen>

namespace Simulator
{
	class cTribe;
	class cCity;

	class cCreatureCitizen
		: public cCreatureBase
	{
	public:
		static const uint32_t TYPE = 0x4F176642;
		static const uint32_t NOUN_ID = 0x18EB4B7;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* FC0h */	int field_FC0;  // 3
		/* FC4h */	uint32_t mFavoredGrasperlikeAppendage;  // -1
		/* FC8h */	uint32_t mGrasperlikeAppendageForBundle;  // -1
		/* FD0h */	cGonzagoTimer field_FD0;
		/* FF0h */	int field_FF0;
		/* FF4h */	int mSelectionGroup;  // -1
		/* FF8h */	int field_FF8;  // -1
		/* FFCh */	int field_FFC;
		/* 1000h */	bool mAffectedByRecruiting;
		/* 1001h */	bool field_1001;  // not initialized
		/* 1002h */	bool field_1002;  // true
		/* 1004h */	Vector3 field_1004;
		/* 1010h */	intrusive_ptr<cCity> mpOwnerCity;
		/* 1014h */	intrusive_ptr<cTribe> mpOwnerTribe;
		/* 1018h */	vector<ObjectPtr> field_1018;
		/* 102Ch */	int mSpecializedTool;
		/* 1030h */	cHitSpherePtr mpHitSphere;
	};
	ASSERT_SIZE(cCreatureCitizen, 0x1038);
}