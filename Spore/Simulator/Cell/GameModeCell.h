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
		DeclareAddress(GoalCards_ptr, SelectAddress(0x16B8068, 0x16B4DC8, 0x16B3DE8));
	}

	namespace Cell
	{
		enum
		{
			kGameModeID = 0x1654C00
		};

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

		protected:
			/* 08h */	bool mbEnableLoadingCards;  // not initialized
			/* 09h */	bool field_09;
			/* 0Ah */	bool field_0A;
		};

		/////////////////////////////////
		//// INTERNAL IMPLEMENTATION ////
		/////////////////////////////////

		static_assert(sizeof(GameModeCell) == 0x0C, "sizeof(GameModeCell) != 0Ch");

		inline GoalCard* GetGoalCards() {
			return (GoalCard*)GetAddress(Cell, GoalCards_ptr);
		}

		namespace Addresses(GameModeCell)
		{
			DeclareAddress(AddRef, SelectAddress(0x1098140, 0xDD3D10, 0xDD3CA0));
			DeclareAddress(Release, SelectAddress(0xE1CF40, 0x1154790, 0x1154790));
			DeclareAddress(func0Ch, SelectAddress(0xA37650, 0xB1FB00, 0xB1FB30));
			DeclareAddress(Initialize, SelectAddress(0xE82280, 0xE81CF0, 0xE81CF0));
			DeclareAddress(Dispose, SelectAddress(0xE824C0, 0xE81F30, 0xE81F30));
			DeclareAddress(OnEnter, SelectAddress(0xE55950, 0xE55300, 0xE552F0));
			DeclareAddress(OnExit, SelectAddress(0xE80190, 0xE7FC00, 0xE7FC00));
			DeclareAddress(func20h, SelectAddress(0xE515F0, 0xE50FF0, 0xE50FE0));
			DeclareAddress(OnKeyDown, SelectAddress(0xE81E80, 0xE818F0, 0xE818F0));
			DeclareAddress(OnKeyUp, SelectAddress(0xE51600, 0xE51000, 0xE50FF0));
			DeclareAddress(OnMouseDown, SelectAddress(0xE6CDE0, 0xE6C860, 0xE6C860));
			DeclareAddress(OnMouseUp, SelectAddress(0xE5C6F0, 0xE5C110, 0xE5C0F0));
			DeclareAddress(OnMouseMove, SelectAddress(0xE51620, 0xE51020, 0xE51010));
			DeclareAddress(OnMouseWheel, SelectAddress(0xE7DBC0, 0xE7D660, 0xE7D660));
			DeclareAddress(Update, SelectAddress(0xE80F10, 0xE80980, 0xE80980));

			DeclareAddress(HandleMessage, SelectAddress(0xE5CB90, 0xE62C90, 0xE62700));

		}
	}
}