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
#include <Spore\App\IGameMode.h>
#include <Spore\Simulator\GoalCard.h>

namespace Simulator
{
	namespace Addresses(Cell) {
		DeclareAddress(GoalCards_ptr);
	}

	namespace Cell
	{
		class GameModeCell
			: public App::IGameMode
			, public App::IUnmanagedMessageListener
		{
		public:

			GameModeCell();
			virtual ~GameModeCell();


			//// OVERRIDES ////

			/* 00h */	virtual int AddRef() override;
			/* 04h */	virtual int Release() override;

			/* 0Ch */	virtual bool func0Ch() override;
			/* 10h */	virtual bool Initialize(App::IGameModeManager* pManager) override;
			/* 14h */	virtual bool Dispose() override;
			/* 18h */	virtual bool OnEnter() override;
			/* 1Ch */	virtual void OnExit() override;
			/* 20h */	virtual void* func20h(int) override;
			/* 24h */	virtual bool OnKeyDown(int virtualKey, KeyModifiers modifiers) override;
			/* 28h */	virtual bool OnKeyUp(int virtualKey, KeyModifiers modifiers) override;
			/* 2Ch */	virtual bool OnMouseDown(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
			/* 30h */	virtual bool OnMouseUp(MouseButton mouseButton, float mouseX, float mouseY, MouseState mouseState) override;
			/* 34h */	virtual bool OnMouseMove(float mouseX, float mouseY, MouseState mouseState) override;
			/* 38h */	virtual bool OnMouseWheel(int nWheelDelta, float mouseX, float mouseY, MouseState mouseState) override;
			/* 3Ch */	virtual void Update(float fDelta1, float fDelta2) override;

			virtual bool HandleMessage(uint32_t messageID, void* pMessage) override;

		public:
			/* 08h */	bool mbEnableLoadingCards;  // not initialized
			/* 09h */	bool field_09;
			/* 0Ah */	bool field_0A;
		};
		ASSERT_SIZE(GameModeCell, 0xC);

#ifndef SDK_TO_GHIDRA
		inline GoalCard* GetGoalCards() {
			return (GoalCard*)GetAddress(Cell, GoalCards_ptr);
		}
#else
		GoalCard sGoalCards[0x76];
#endif

		namespace Addresses(GameModeCell)
		{
			DeclareAddress(AddRef);
			DeclareAddress(Release);
			DeclareAddress(func0Ch);
			DeclareAddress(Initialize);
			DeclareAddress(Dispose);
			DeclareAddress(OnEnter);
			DeclareAddress(OnExit);
			DeclareAddress(func20h);
			DeclareAddress(OnKeyDown);
			DeclareAddress(OnKeyUp);
			DeclareAddress(OnMouseDown);
			DeclareAddress(OnMouseUp);
			DeclareAddress(OnMouseMove);
			DeclareAddress(OnMouseWheel);
			DeclareAddress(Update);

			DeclareAddress(HandleMessage);

		}
	}
}