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

#include <Spore\Object.h>
#include <Spore\MathUtils.h>
#include <Spore\ResourceKey.h>
#include <Spore\Simulator\cSpaceToolData.h>

#define cToolStrategyPtr intrusive_ptr<Simulator::cToolStrategy>

using namespace Math;

namespace Simulator
{

	class cToolStrategy 
		: public Object
		, public DefaultRefCounted
	{
	public:
		static const uint32_t STRATEGY_ID = 0xB0DA49D9;
		static const uint32_t TYPE = 0x24A4AC5;

		// abduct, beam, scan, dropCargo, mindErase have a common type ID: 0x60079DE
		// toggleTool type ID: 0x61D959A

		/* 00h */	virtual int AddRef() override;
		/* 04h */	virtual int Release() override;
		/* 08h */	virtual ~cToolStrategy() {};
		/* 0Ch */	virtual void* Cast(uint32_t type) const override;
		/* 10h */	virtual uint32_t GetType();  // 0x24A4AC5
		/* 14h */	virtual uint32_t GetStrategyID();  // returns cToolStrategy::STRATEGY_ID for all

		///
		/// Called when the user clicks on the tool button to select it.
		/// The return value is ignored.
		/// @param pTool The space tool. 
		///
		/* 18h */	virtual bool OnSelect(cSpaceToolData* pTool);

		///
		/// Called when the user clicks on the tool button to unselect it 
		/// (that is, if the tool was previously selected and the user clicks again).
		/// The return value is ignored.
		///
		/// The default implementation does nothing, just returns true.
		/// @param pTool The space tool. 
		///
		/* 1Ch */	virtual bool OnDeselect(cSpaceToolData* pTool);

		///
		/// Called every game loop if the tool is visible, that is, if the panel that contains it is selected or if the tool
		/// is selected.
		/// The return value is used to tell if the tool is available to be used or not.
		/// <li>If the method returns false, the tool is disabled and cannot be selected.</li>
		/// <li>If the method returns true, the tool is enabled and can be used.</li>
		///
		/// @param pTool The space tool.
		/// @param showErrors Whether event logs should be shown to the player or not.
		/// @param ppFailText [Optional] If not null, an error text can be set so that it is shown in the tool button.
		/// @returns Whether the tool must be enabled or not.
		///
		/* 20h */	virtual bool Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText=nullptr);

		/* 24h */	virtual bool WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors);

		/* 28h */	virtual void OnMouseDown(cSpaceToolData* pTool, const Vector3& playerPosition);

		///
		/// Unlike Update, it's not executed if the game is paused.
		/* 2Ch */	virtual void SelectedUpdate(cSpaceToolData* pTool, const Vector3& position);

		/* 30h */	virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType, int);

		/* 34h */	virtual bool WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int);

		/* 38h */	virtual bool OnMouseUp(cSpaceToolData* pTool);

		///
		/// Returns the coordinates of the position where the tool is aiming.
		///
		/// The default implementation uses the method cGameViewManager::GetWorldMousePosition(), 
		/// ignoring the player UFO.
		///
		/// @returns The coordinates of the position where the tool is aiming.
		///
		/* 3Ch */	virtual Vector3 GetAimPoint();

		/* 40h */	virtual Vector3 func40h();

		///
		/// Function called to calculate the sporebucks cost of firing the tool. It receives the value of the 
		/// 
		/* 44h */	virtual int ProcessCost(int useCost);
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cToolStrategy) == 0x0C, "sizeof(cToolStrategy) != 0x0C");

	namespace Addresses(cToolStrategy)
	{
		DeclareAddress(OnSelect);
		
		DeclareAddress(Update);
		DeclareAddress(WhileAiming);
		
		DeclareAddress(SelectedUpdate);
		DeclareAddress(OnHit);
		DeclareAddress(WhileFiring);
		DeclareAddress(OnMouseUp);
		DeclareAddress(GetAimPoint);
		DeclareAddress(func40h);

	}
}