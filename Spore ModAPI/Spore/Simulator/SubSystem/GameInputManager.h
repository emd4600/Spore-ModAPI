/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#pragma once

#include <Spore\App\IMessageListener.h>
#include <Spore\Object.h>
#include <Spore\Input.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\UIStateMachine.h>
#include <EASTL\map.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <EASTL\set.h>

#define GameInputManager (*Simulator::cGameInputManager::Get())

namespace Simulator
{
	class cGameInputManager
		/* 00h */	: public DefaultRefCounted
		/* 08h */	, public App::IUnmanagedMessageListener
		/* 0Ch */	, public cStrategy
	{
	public:
		/* 10h */	virtual void SetTriggerFile(const char* pFileName, int = 0, bool isMain = true);
		/* 14h */	virtual void func14h_();
		/* 18h */	virtual bool IsTriggered(int triggerCode);
		/* 1Ch */	virtual void func1Ch_();
		// other arguments set field_60 and field_64
		/* 20h */	virtual void AddUIStateMachine(UIStateMachine*, int initialState, int);
		/* 24h */	virtual void AddUIStateMachine2(UIStateMachine*, int initialState);
		/* 28h */	virtual void func28h_(uint32_t messageId);
		/* 2Ch */	virtual bool ProcessTransitionForVector(const eastl::vector<UIStateMachineTransition>& transitions, UIStateMachineEvent eventType, UIStateMachineEventKey eventParam, Object* pObject, const Math::Vector3& coords, int objectFlags, int keyModFlags);
		/// Tries to transition from the current state to the next state given the specified event. 
		/// If the transition is succesful, it emits its corresponding message.
		/* 30h */	virtual bool ProcessTransition(UIStateMachineEvent eventType, UIStateMachineEventKey eventParam, Object* pObject, const Math::Vector3& coords, int objectFlags, int keyModFlags);
		/* 34h */	virtual int func34h_();
		/* 38h */	virtual void func38h_(int);
		/* 3Ch */	virtual void LoadUIStateMachine(const char* name);
		/* 40h */	virtual void DeclareMenu(uint32_t menuId, const char* menuName);
		/* 44h */	virtual bool func44h_(int, int);
		/* 48h */	virtual void func48h_(bool);
		/* 4Ch */	virtual bool OnKeyDown(int virtualKey, KeyModifiers modifiers);
		/* 50h */	virtual bool OnKeyUp(int virtualKey, KeyModifiers modifiers);
		/* 54h */	virtual bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState);
		/* 58h */	virtual bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState);
		/* 5Ch */	virtual bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState);
		/* 60h */	virtual bool OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, MouseState mouseState);
		/* 64h */	virtual bool func64h_(int, int);
		/* 68h */	virtual bool func68h_(int);

	public:
		struct InputUnknown
		{
			/* 00h */	int field_0;
			/* 04h */	int field_4;
			/* 08h */	int field_8;
			/* 0Ch */	int field_C;
			/* 10h */	int field_10;
			/* 14h */	int field_14;
			/* 18h */	bool field_18;  // false
			/* 19h */	char field_19;  // 0xFE
		};
		struct InputUnknown2
		{
			virtual ~InputUnknown2();  // and more things
			/* 04h */	int field_4;
			/* 08h */	int field_8;
			/* 0Ch */	int field_C;
			/* 10h */	int field_10;  // allocator
			/* 14h */	int field_14;
			/* 18h */	int field_18;
			/* 1Ch */	int field_1C;
			/* 20h */	int field_20;
			/* 24h */	int field_24;  // allocator
			/* 28h */	int field_28;
			/* 2Ch */	bool field_2C;
		};

		/* 28h */	UIStateMachine mStateMachine;
		/* 60h */	int mCurrentState;
		/* 64h */	int field_64;
		/* 68h */	float mMouseX;
		/* 6Ch */	float mMouseY;
		/* 70h */	float field_70;
		/* 74h */	InputUnknown field_74;
		/* 90h */	InputUnknown2 field_90;
		/* C0h */	InputUnknown field_C0;
		/* DCh */	eastl::string field_DC;
		/* ECh */	eastl::string field_EC;
		/* FCh */	eastl::vector<int> field_FC;
		/* 110h */	int field_110;

	public:
		static cGameInputManager* Get();
	};
	ASSERT_SIZE(cGameInputManager, 0x114);

	namespace Addresses(cGameInputManager)
	{
		DeclareAddress(Get);
	}
}