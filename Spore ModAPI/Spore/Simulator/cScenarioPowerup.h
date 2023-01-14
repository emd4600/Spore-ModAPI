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

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cCreatureBase.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\App\PropertyList.h>

namespace Simulator
{
	class cScenarioPowerup
	{
	public:
		static const uint32_t TYPE = 0x8367427;
		
		/* 00h */	virtual ~cScenarioPowerup();
		/* 04h */	virtual cGameData* ToGameData() = 0;
		/* 08h */	virtual cSpatialObject* ToSpatialObject() = 0;

		/// Called when an object (creatures, and maybe other kinds of objects too?) gets inside the range of activation
		/// of a powerup, so this function activates the effects of those powerups. This function might be called twice, 
		/// with the two parameters reversed; Spore activates the powerups when the first parameter is a cScenarioPowerup.
		/// 
		/// This method will call the ActivateMedKit(), ActivateEnergyKit(), etc methods.
		/// @param pFirst
		/// @param pSecond
		static void ReactToPowerup(cGameData* pFirst, cGameData* pSecond, void*);

		static void ActivateMedKit(cScenarioPowerup* pPowerup, cCreatureBase* pCreature);
		static void ActivateEnergyKit(cScenarioPowerup* pPowerup, cCreatureBase* pCreature);
		static void ActivateSpeedBoost(cScenarioPowerup* pPowerup, cCreatureBase* pCreature);
		static void ActivateDamageBoost(cScenarioPowerup* pPowerup, cCreatureBase* pCreature);
		static void ActivateArmorBoost(cScenarioPowerup* pPowerup, cCreatureBase* pCreature);
		static void ActivateMine(cScenarioPowerup* pPowerup, cCombatant* pCombatant);
		static void ActivateJumpPad(cScenarioPowerup* pPowerup, cCreatureBase* pCreature);
		static void ActivateTeleporter(cScenarioPowerup* pPowerup, cCreatureBase* pCreature);
		static void ActivateGate(cCreatureBase* pCreature, cScenarioPowerup* pKeyPowerup, cScenarioPowerup* pGatePowerup);
		static void ActivateGrenade(cScenarioPowerup* pPowerup, cCreatureBase* pAttackerCreature);
		
	public:
		/* 04h */	ScenarioPowerupType mPowerupType;
		/* 08h */	ResourceKey mPowerupModel;
		/* 14h */	bool field_14;
		/* 18h */	PropertyListPtr mpPropList;
		/* 1Ch */	ObjectPtr field_1C;
		/* 20h */	cGameDataPtr field_20;
		/* 24h */	float field_24;  // not initialized
		/* 28h */	float field_28;  // not initialized
		/* 2Ch */	int mScenarioClassIndex;  // not initialized
		/* 30h */	bool mHasBeenThrown;
		/* 34h */	float mTimeInFlight;
		/// When you throw the object, this is the object to whom you throw it to. Only used by grenade.
		/* 38h */	cGameDataPtr mpThrowObjective;
	};
	ASSERT_SIZE(cScenarioPowerup, 0x3C);

	namespace Addresses(cScenarioPowerup)
	{
		DeclareAddress(ReactToPowerup);  // 0xF23FD0, 0xF23BF0
		//TODO DeclareAddress(ApplyBoost);  // 0xF20670, 0xF20290
		DeclareAddress(ActivateMedKit);  // 0xF229C0, 0xF225E0
		DeclareAddress(ActivateEnergyKit);  // 0xF22BE0, 0xF22800
		DeclareAddress(ActivateSpeedBoost);  // 0xF232B0, 0xF22ED0
		DeclareAddress(ActivateDamageBoost);  // 0xF23000, 0xF22C20
		DeclareAddress(ActivateArmorBoost);  // 0xF22D50, 0xF22970
		DeclareAddress(ActivateMine);  // 0xF20BB0, 0xF207D0
		DeclareAddress(ActivateJumpPad);  // 0xF23890, 0xF234B0
		DeclareAddress(ActivateTeleporter);  // 0xF23660, 0xF23280
		DeclareAddress(ActivateGate);  // 0xF23E90, 0xF23AB0
		DeclareAddress(ActivateGrenade);  // 0xF20C40, 0xF20860
	}
}