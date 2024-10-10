#pragma once

#include <Spore\UTFWin\UILayout.h>
#include <Spore\Simulator\cObjectPool.h>
#include <Spore\Simulator\cGameData.h>

namespace UI
{
	enum class SimulatorRolloverID
	{

		/// Rollover_TribeTool
		TribeTool = 2,
		/// Rollover_TribeCitizen
		TribeCitizen = 3,
		/// Rollover_TribeHut
		TribeHut = 4,
		/// Rollover_Tribe_Minimap
		TribeMinimap = 5,
		/// Rollover_ScenarioVehicle or Rollover_CivVehicle
		Vehicle = 6,
		/// RolloverCity_Minimap
		SpaceMinimap = 7,
		/// SharedHealthBar, or RolloverSpaceCity in Space stage
		HealthBar = 8,
		/// Rollover_Building
		Building = 9,
		/// SharedHealthBar
		SharedHealthBar = 10,
		/// RolloverUFO
		UFO = 11,
		/// Rollover_Creature
		Creature = 12,
		/// SharedHealthBar
		SharedHealthBar2 = 13,
		/// Rollover_CRGMinimap
		CreatureMinimap = 14,
		/// SharedHealthBar
		SharedHealthBar3 = 15,
		/// Rollover_FixedObject
		FixedObject = 16,
	};

	class SimulatorRollover
		: public Simulator::cObjectPoolClass
	{
	public:
		/// Returns which kind of rollover must be shown for a certain Simulator object.
		/// @param object
		/// @returns
		static SimulatorRolloverID GetRolloverIdForObject(Simulator::cGameData* object);

		/// If possible, displays a rollover over the specificed Simulator object.
		/// 
		static void ShowRollover(Simulator::cGameData* object);

		static SimulatorRollover* ShowRolloverInternal(Simulator::cGameData* object, SimulatorRolloverID rolloverId, float = -1.0f);

	public:
		/* 04h */	cGameDataPtr mpObject;
		/* 08h */	char padding_8[0x50 - 8];
		/* 50h */	UILayoutPtr mpLayout;
		/// Control ID 0x93310E4A
		/* 54h */	IWindowPtr mpMainWindow;
		/// Control ID 0x93310E4B
		/* 58h */	IWindowPtr mpFrameWindow;
		/// Control ID 0x31E94D0
		/* 5Ch */	IWindowPtr field_5C;
		/// Control ID 0x933103EA
		/* 60h */	IWindowPtr field_60;
		/// Control ID 0x26E0DF0
		/* 64h */	IWindowPtr field_64;
		/// Control ID 0x26E0DF1
		/* 68h */	IWindowPtr field_68;
		/// Control ID 0x26E0DF2
		/* 6Ch */	IWindowPtr field_6C;
		/// Control ID 0x26E0DF3
		/* 70h */	IWindowPtr field_70;
		/// Control ID 0x4D039A8
		/* 74h */	IWindowPtr field_74;
		/// Control ID 0x4B47745
		/* 78h */	IWindowPtr field_78;
		/// Control ID 0x553E937
		/* 7Ch */	IWindowPtr field_7C;
		/// Control ID 0x553EA66
		/* 80h */	ObjectPtr field_80;
		/// Control ID 0x553E92B
		/* 84h */	IWindowPtr field_84;
		/// Control ID 0x553EA6E
		/* 88h */	IWindowPtr field_88;
		/// Control ID 0x657C8F8
		/* 8Ch */	IWindowPtr field_8C;
		/// Control ID 0x46ADF86
		/* 90h */	ObjectPtr field_90;  // SporeAnimatedIconWin
		/// Control ID 0x26E0001
		/* 94h */	ObjectPtr field_94;
		/// Control ID 0x26E0003
		/* 98h */	ObjectPtr field_98;
		/// Control ID 0x26E0001
		/* 9Ch */	ObjectPtr field_9C;
		/// Control ID 0x542EFB0
		/* A0h */	IWindowPtr field_A0;
		/// Control ID 0x542EFB0
		/* A4h */	ObjectPtr field_A4;
		/// Control ID 0x199A7D2
		/* A8h */	IWindowPtr field_A8;
		/// Control ID 0x41F852D
		/* ACh */	IWindowPtr field_AC;
		/// Control ID 0x5E62810
		/* B0h */	ObjectPtr field_B0;
		/// Control ID 0x6303998
		/* B4h */	ObjectPtr field_B4;
		/* B8h */	char padding_B8[0x130 - 0xB8];
	};
	ASSERT_SIZE(SimulatorRollover, 0x130);

	namespace Addresses(SimulatorRollover)
	{
		DeclareAddress(GetRolloverIdForObject);  // 0xB67960 0xB67D70
		DeclareAddress(ShowRollover);  // 0xB69680 0xB69A90
		DeclareAddress(ShowRolloverInternal);  // 0xB68790 0xB68BA0
	}
}
