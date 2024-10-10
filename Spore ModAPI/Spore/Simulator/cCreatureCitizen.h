#pragma once

#include <Spore\Simulator\cCreatureBase.h>
#include <Spore\Simulator\cHitSphere.h>

#define cCreatureCitizenPtr eastl::intrusive_ptr<Simulator::cCreatureCitizen>

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

		/// Programs this creature behavior tree data (i.e. its AI) to do a certain action from Simulator::CitizenAction.
		/// The action is defined by an ID and an object to act on, for instance,
		/// Simulator::kCitizenActionGrabTool and the cTribeTool object.
		/// @param actionId
		/// @param actionObject
		/// @param property [Optional]
		void DoAction(int actionId, cGameData* actionObject, App::Property* property = nullptr);

		/// For a given tribal tool from Simulator::TribeToolType, returns which item must be held by
		/// the citizen. The item is part of the Simulator::HandheldItem enum.
		/// @param toolType
		/// @returns An integer identifying the kind of item to be held
		int GetHandheldItemForTool(int toolType);

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
		/* 1004h */	Math::Vector3 field_1004;
		/* 1010h */	eastl::intrusive_ptr<cCity> mpOwnerCity;
		/* 1014h */	eastl::intrusive_ptr<cTribe> mpOwnerTribe;
		/* 1018h */	eastl::vector<ObjectPtr> field_1018;
		/* 102Ch */	int mSpecializedTool;
		/* 1030h */	cHitSpherePtr mpHitSphere;
	};
	ASSERT_SIZE(cCreatureCitizen, 0x1038);

	namespace Addresses(cCreatureCitizen) {
		DeclareAddress(Update);  // 0xC24210 0xC24A30
		DeclareAddress(DoAction);  // 0xC26EF0 0xC27710
		DeclareAddress(GetHandheldItemForTool);  // 0xC22E70 0xC23740
	}
}