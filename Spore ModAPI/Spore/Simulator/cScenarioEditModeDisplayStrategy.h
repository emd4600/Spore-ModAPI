#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\App\MessageListenerData.h>
#include <Spore\UTFWin\UILayout.h>
#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\cSPUIMessageBox.h>

#define cScenarioEditModeDisplayStrategyPtr eastl::intrusive_ptr<Simulator::cScenarioEditModeDisplayStrategy>

namespace Simulator
{
	class cScenarioEditModeDisplayStrategy
		/* 00h */	: public DefaultRefCounted
		/* 08h */	, public UTFWin::IWinProc
		/* 0Ch */	, public UTFWin::MessageBoxCallback
		/* 10h */	, public App::IMessageListener
	{
	public:
		static const uint32_t TYPE = 0x7103861;

		bool Load();

	public:
		/* 14h */	DefaultRefCountedPtr field_14;
		/* 18h */	DefaultRefCountedPtr mEditModeScriptUI;  // cScenarioEditModeScriptUIPtr
		/* 1Ch */	int field_1C;  // -1
		/* 20h */	int field_20;  // -1
		/// 0x396F69F5.spui
		/* 24h */	UILayoutPtr mMainUILayout;
		/* 28h */	DefaultRefCountedPtr field_28;
		/* 2Ch */	ObjectPtr mNamePanelUI;
		/* 30h */	ObjectPtr mWorldComplexityMeter;  // cScenarioComplexityMeterPtr
		/* 34h */	ObjectPtr mTerraformComplexityMeter;  // cScenarioComplexityMeterPtr
		/* 38h */	ObjectPtr mTutorialsChecklistUI;  // cScenarioTutorialsChecklistUIPtr
		/* 3Ch */	ObjectPtr mTutorialsChecklistUI2;  // cScenarioTutorialsChecklistUIPtr
		/* 40h */	ObjectPtr mPosseUI;  // UI::PossePtr
		/* 44h */	ObjectPtr mSPUIGlobalOptions;  // cSPUIGlobalOptionsPtr
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	int field_54;
		/* 58h */	int field_58;
		/* 5Ch */	int field_5C;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;
		/* 70h */	App::MessageListenerData mMessageListenerData;
		/* 84h */	int field_84;
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;
		/* 90h */	int field_90;
		/* 94h */	int field_94;
	};
	ASSERT_SIZE(cScenarioEditModeDisplayStrategy, 0x98);

	namespace Addresses(cScenarioEditModeDisplayStrategy) {
		DeclareAddress(Load);  // 0xED6000 0xED5C70
	}
}