#pragma once

#include <Spore\Simulator\cBaseSimulatorInputStrategy.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cTribeTool.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Clock.h>

namespace Simulator
{
	class cTribeInputStrategy
		/* 00h */	: public cBaseSimulatorInputStrategy
		/* 3Ch */	, public App::IUnmanagedMessageListener
	{
	public:
		/// Returns the input action ID (from Simulator::TribeInputAction) that the selected actors (e.g. tribe members) should do next.
		/// This is called when hovering or clicking over objects such as tribal tools.
		/// @param object
		/// @param unk
		/// @returns An action ID from TribeInputAction enum
		int ChooseInputActionID(cGameData* object, int unk);

		/// Makes selected tribe members act on a tribe tool. This might be repairing it if it's hurt,
		/// grabbing the tool, or dancing around the fire pit.
		/// @param tribeTool
		bool DoToolActionForAllSelected(cTribeTool* tribeTool);

		/// Makes selected tribe members do an action on an object.
		/// This will call cCreatureCitizen::DoAction(), and may play a sound.
		/// @param citizenActionId Action ID, from Simulator::CitizenAction
		/// @param actionObject
		/// @param unk
		void DoActionForAllSelected(int citizenActionId, cGameData* actionObject, int unk = 0);

		/// Called when the player inputs an action, this will do the appropriate action for
		/// the selected tribe members and the given object (which will be the hovered object by the mouse).
		/// The method calls ChooseInputActionID(), then chooses how to translate that into CitizenActions 
		/// that the tribe members will do.
		/// @param actionObject
		void DoActionGeneric(cGameData* actionObject);
		
		/// Sets the current cursor, and maybe shows a rollover, depending on the current object
		/// pointed at by the mouse cursor. The object will be cGameViewManager::GetHoveredObject()
		/// The method will do nothing if IsInEditor() returns true.
		void SetHoverObjectCursorAndRollover();

		/// Returns true if the player has gone to the creature outfitter editor, false otherwise.
		static bool IsInEditor();

	public:
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	int field_54;
		/* 58h */	float field_58;  // 225.0
		/* 5Ch */	int field_5C;
		/* 60h */	eastl::map<int, int> field_60;
		/* 7Ch */	eastl::map<int, int> field_7C;
		/* 98h */	int field_98;
		/* 9Ch */	int field_9C;
		/* A0h */	int field_A0;
		/* A8h */	Clock field_A8;
		/* C0h */	int field_C0;
		/* C4h */	bool field_C4;
		/* C8h */	int field_C8;
	};
	ASSERT_SIZE(cTribeInputStrategy, 0xD0);

	namespace Addresses(cTribeInputStrategy) {
		DeclareAddress(DoToolActionForAllSelected);  // 0xCCFFE0 0xCD09B0
		DeclareAddress(DoActionForAllSelected);  // 0xCCFF70 0xCD0940
		DeclareAddress(ChooseInputActionID);  // 0xCCE870 0xCCF130
		DeclareAddress(DoActionGeneric);  // 0xCD0250 0xCD0250
		DeclareAddress(SetHoverObjectCursorAndRollover);  // 0xCCF800 0xCD00C0
		DeclareAddress(sIsInEditor_ptr);  // 0x168AD70 0x1686AF0
	}
}