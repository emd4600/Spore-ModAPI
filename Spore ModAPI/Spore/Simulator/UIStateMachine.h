#pragma once

#include "Spore\Internal.h"
#include "Spore\Object.h"
#include <EASTL\map.h>
#include <EASTL\string.h>
#include <EASTL\vector.h>

#define cCommandParameterSetPtr eastl::intrusive_ptr<Simulator::cCommandParameterSet>
#define cMessageCommandDispatcherPtr eastl::intrusive_ptr<Simulator::cMessageCommandDispatcher>
#define cStringCommandGeneratorPtr eastl::intrusive_ptr<Simulator::cStringCommandGenerator>

namespace Simulator
{
	enum class UIStateMachineEvent
	{
		MouseDown = 1,
		MouseDoubleClick = 2,
		MouseUp = 3,
		MouseMove = 6,
		LongMouseMove = 7,
		MouseWheel = 8,
		KeyDown = 4,
		KeyUp = 5,
		MenuItem = 9,
		TriggerDown = 10,
		TriggerUp = 11
	};

	enum class UIStateMachineEventKey 
	{
		TAB = 9,
		LEFT = 0x3E8,
		MIDDLE = 0x3E9,
		RIGHT = 0x3EA,
		BACKSPACE = 8,
		SPACE = 0x20,
		ESCAPE = 0x1B,
		ENTER = 0xD,
		FORWARD = 1,
		BACK = -1,
		PGUP = 0x21,
		PGDOWN = 0x22,
		ARROWUP = 0x26,
		ARROWDOWN = 0x28,
		ARROWLEFT = 0x25,
		ARROWRIGHT = 0x27,
		DELETE_ = 0x2E,
		HOME = 0x24,
		OPENBRACKET = 0xDB,
		CLOSEBRACKET = 0xDD,
		SHIFT = 0x10,
		CONTROL = 0x11,
		ALT = 0x12,
		F1 = 0x70,
		F2 = 0x71,
		F3 = 0x72,
		F4 = 0x73,
	};

	enum class UIStateMachineKeyMod 
	{
		LEFT = 8,
		MIDDLE = 0x10,
		RIGHT = 0x20,
		CONTROL = 2,
		ALT = 4,
		SHIFT = 1,
		NONE = 0,
		ANY = 0x3FF,
		NOREPEAT = 0x40,
	};

	enum class UIStateMachineObjectFlags
	{
		PlayerOwned = 1,
		NPCOwned = 2,
		IsSelected = 0x10,
		IsNotSelected = 0x20,
		SomeObjectsAreSelected = 4,
		NoObjectsAreSelected = 8,
		ObjectIsShowingMenu = 0x40,
		ObjectIsNotShowingMenu = 0x80,
		ObjectIsUnderWater = 0x100,
		ObjectIsNotUnderWater = 0x200,
	};

	struct UIStateMachineTransition
	{
		/* 00h */	eastl::string field_0;  // always default string
		/* 10h */	int dstState;
		/* 14h */	uint32_t messageId;
		/* 18h */	int messageParam;
		/* 1Ch */	UIStateMachineEventKey eventParam;
		/* 20h */	uint32_t objectTypeId;  // -1
		/* 24h */	bool isPush;
		/* 28h */	UIStateMachineEvent eventType;
		/// Combination of UIStateMachineKeyMod
		/* 2Ch */	int keyModFlags;
		/// Combination of UIStateMachineObjectFlags
		/* 30h */	int objectFlags;
		/* 34h */	int longMouseMove;
	};
	ASSERT_SIZE(UIStateMachineTransition, 0x38);

	struct UIStateMachine
	{
		static constexpr int ORIGIN = -1;

		/// Maps each state index to all the transitions from it.
		/// Transitions with no origin state are mapped to ORIGIN
		/* 00h */	eastl::map<int, eastl::vector<UIStateMachineTransition>> mTransitions;
		/* 1Ch */	eastl::map<int, eastl::string> mStates;
	};
	ASSERT_SIZE(UIStateMachine, 0x38);

	class cCommandParameterSet
		: public Object
		, public IVirtual
	{
	public:
		/* 08h */	char padding_8[0x3C - 8];
	};
	ASSERT_SIZE(cCommandParameterSet, 0x3C);

	class cStringCommandGenerator
		: public Object
		, public IVirtual
	{
	public:
		/* 08h */	int mnRefCount;
		/* 0Ch */	eastl::vector<int> field_8;
		/* 20h */	cCommandParameterSetPtr mParamSet;
	};
	ASSERT_SIZE(cStringCommandGenerator, 0x24);


	class cMessageCommandDispatcher
		: public Object
		, public IVirtual
		//TODO something else
	{
	public:
		static const uint32_t TYPE = 0xB903CC3;

		/* 10h */	virtual bool Initialize();
		/* 14h */	virtual bool Dispose();
		/* 18h */	virtual bool func18h();
		/* 1Ch */	virtual int ExecuteCommand(uint32_t commandId, cCommandParameterSet* param1 = nullptr, cCommandParameterSet* param2 = nullptr);

	public:
		/* 08h */	char padding_8[0x30];
		/* 38h */	cCommandParameterSetPtr field_38;
		/* 3Ch */	cCommandParameterSetPtr field_3C;
		/* 40h */	cStringCommandGeneratorPtr field_40;
		/* 44h */	int field_44;
	};
	ASSERT_SIZE(cMessageCommandDispatcher, 0x48);
}