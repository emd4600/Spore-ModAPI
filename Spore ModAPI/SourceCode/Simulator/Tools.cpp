#ifndef MODAPI_DLL_EXPORT
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
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cScenarioResource.h>
#include <Spore\Simulator\cToolStrategy.h>

#include <Spore\Simulator\cRepairToolStrategy.h>
#include <Spore\Simulator\cEnergyRepairToolStrategy.h>
#include <Spore\Simulator\cGetOutOfUFOToolStrategy.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cTurretDefenseMissileWeapon.h>
#include <Spore\Simulator\cTurretFlakWeapon.h>
#include <Spore\Simulator\cDeepSpaceProjectileToolStrategy.h>
#include <Spore\Simulator\cPlaceObjectToolStrategy.h>
#include <Spore\Simulator\cCropCirclesToolStrategy.h>
#include <Spore\Simulator\cGenesisDeviceToolStrategy.h>
#include <Spore\Simulator\cDefaultBeamTool.h>
#include <Spore\Simulator\cDefaultAoETool.h>
#include <Spore\Simulator\cAbductToolStrategy.h>
#include <Spore\Simulator\cScanToolStrategy.h>
#include <Spore\Simulator\cDropCargoToolStrategy.h>
#include <Spore\Simulator\cDragInputProjectileToolStrategy.h>
#include <Spore\Simulator\cArtilleryWeaponStrategy.h>
#include <Spore\Simulator\cMindEraseToolStrategy.h>
#include <Spore\Simulator\cGlobalMindEraseToolStrategy.h>
#include <Spore\Simulator\cRepairAOEToolStrategy.h>
#include <Spore\Simulator\cRallyCallToolStrategy.h>
#include <Spore\Simulator\cToggleToolStrategy.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>

namespace Simulator
{
	auto_METHOD_VOID(cSpaceToolData, AddAmmo, Args(int ammo), Args(ammo));
	auto_METHOD_VOID(cSpaceToolData, ConsumeAmmo, Args(int amount), Args(amount));
	auto_STATIC_METHOD(cSpaceToolData, uint32_t, ShowEventLog,
		Args(cSpaceToolData* pTool, uint32_t eventLogID, bool show), Args(pTool, eventLogID, show));

	auto_METHOD_const_(cSpaceToolData, cToolStrategy*, GetStrategy);

	//// STRATEGIES ////

	int cToolStrategy::AddRef() {
		return DefaultRefCounted::AddRef();
	}

	int cToolStrategy::Release() {
		return DefaultRefCounted::Release();
	}

	void* cToolStrategy::Cast(uint32_t type) const {
		if (type == Object::TYPE || type == cToolStrategy::TYPE) {
			return (Object*)this;
		}
		else {
			return nullptr;
		}
	}

	uint32_t cToolStrategy::GetType() {
		return TYPE;
	}

	uint32_t cToolStrategy::GetStrategyID() {
		return STRATEGY_ID;
	}


	auto_METHOD_VIRTUAL(cToolStrategy, cToolStrategy, bool, OnSelect, Args(cSpaceToolData* pTool), Args(pTool));

	bool cToolStrategy::OnDeselect(cSpaceToolData* pTool) { return true; }

	auto_METHOD_VIRTUAL(cToolStrategy, cToolStrategy, bool, Update, Args(cSpaceToolData* pTool, bool arg1, const char16_t** arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cToolStrategy, cToolStrategy, bool, WhileAiming, Args(cSpaceToolData* pTool, const Vector3& arg1, bool arg2), Args(pTool, arg1, arg2));

	void cToolStrategy::OnMouseDown(cSpaceToolData* pTool, const Vector3& arg1) {}

	auto_METHOD_VIRTUAL_VOID(cToolStrategy, cToolStrategy, SelectedUpdate, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));
	auto_METHOD_VIRTUAL(cToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C),
		Args(pTool, position, hitType, arg_C));
	auto_METHOD_VIRTUAL(cToolStrategy, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cToolStrategy, cToolStrategy, bool, OnMouseUp, Args(cSpaceToolData* pTool), Args(pTool));

	Vector3 cToolStrategy::GetAimPoint() {
		Vector3 dst;
		((void(__thiscall*)(cToolStrategy*,Vector3&))(GetAddress(cToolStrategy, GetAimPoint)))(this, dst);
		return dst;
	}

	Vector3 cToolStrategy::func40h() { 
		Vector3 dst;
		((void(__thiscall*)(cToolStrategy*, Vector3&))(GetAddress(cToolStrategy, func40h)))(this, dst);
		return dst;
	}
	int cToolStrategy::ProcessCost(int useCost) { return useCost; }


	//// cRepairToolStrategy ////

	auto_METHOD_VIRTUAL(cRepairToolStrategy, cToolStrategy, bool, Update, Args(cSpaceToolData* pTool, bool arg1, const char16_t** arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cRepairToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));
	auto_METHOD_VIRTUAL(cRepairToolStrategy, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cEnergyRepairToolStrategy ////

	auto_METHOD_VIRTUAL(cEnergyRepairToolStrategy, cToolStrategy, bool, Update, Args(cSpaceToolData* pTool, bool arg1, const char16_t** arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cEnergyRepairToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));


	//// cGetOutOfUFOToolStrategy ////

	auto_METHOD_VIRTUAL(cGetOutOfUFOToolStrategy, cToolStrategy, bool, OnSelect, Args(cSpaceToolData* pTool), Args(pTool));
	auto_METHOD_VIRTUAL(cGetOutOfUFOToolStrategy, cToolStrategy, bool, Update, Args(cSpaceToolData* pTool, bool arg1, const char16_t** arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cGetOutOfUFOToolStrategy, cToolStrategy, bool, WhileAiming, Args(cSpaceToolData* pTool, const Vector3& arg1, bool arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cGetOutOfUFOToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));


	//// cDefaultProjectileWeapon ////

	auto_METHOD_VIRTUAL(cDefaultProjectileWeapon, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));
	auto_METHOD_VIRTUAL(cDefaultProjectileWeapon, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cTurretDefenseMissileWeapon ////

	auto_METHOD_VIRTUAL(cTurretDefenseMissileWeapon, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cTurretFlakWeapon ////

	auto_METHOD_VIRTUAL(cTurretFlakWeapon, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cDeepSpaceProjectileToolStrategy ////

	auto_METHOD_VIRTUAL(cDeepSpaceProjectileToolStrategy, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cPlaceObjectToolStrategy ////

	auto_METHOD_VIRTUAL(cPlaceObjectToolStrategy, cToolStrategy, bool, OnSelect, Args(cSpaceToolData* pTool), Args(pTool));
	auto_METHOD_VIRTUAL(cPlaceObjectToolStrategy, cToolStrategy, bool, OnDeselect, Args(cSpaceToolData* pTool), Args(pTool));
	auto_METHOD_VIRTUAL(cPlaceObjectToolStrategy, cToolStrategy, bool, Update, Args(cSpaceToolData* pTool, bool arg1, const char16_t** arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cPlaceObjectToolStrategy, cToolStrategy, bool, WhileAiming, Args(cSpaceToolData* pTool, const Vector3& arg1, bool arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL_VOID(cPlaceObjectToolStrategy, cToolStrategy, SelectedUpdate, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));
	auto_METHOD_VIRTUAL(cPlaceObjectToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));


	//// cCropCirclesToolStrategy ////

	auto_METHOD_VIRTUAL(cCropCirclesToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));


	//// cGenesisDeviceToolStrategy ////

	auto_METHOD_VIRTUAL(cGenesisDeviceToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));


	//// cDefaultBeamTool ////

	auto_METHOD_VIRTUAL_VOID(cDefaultBeamTool, cToolStrategy, OnMouseDown, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));
	auto_METHOD_VIRTUAL(cDefaultBeamTool, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));
	auto_METHOD_VIRTUAL(cDefaultBeamTool, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cDefaultBeamTool, cToolStrategy, bool, OnMouseUp, Args(cSpaceToolData* pTool), Args(pTool));
	auto_METHOD_VIRTUAL(cDefaultBeamTool, cToolStrategy, bool, func48h, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));
	auto_METHOD_VIRTUAL(cDefaultBeamTool, cToolStrategy, bool, func4Ch, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));


	//// cDefaultAoETool ////

	auto_METHOD_VIRTUAL_VOID(cDefaultAoETool, cToolStrategy, OnMouseDown, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));
	auto_METHOD_VIRTUAL(cDefaultAoETool, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));
	auto_METHOD_VIRTUAL(cDefaultAoETool, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cDefaultAoETool, cToolStrategy, bool, OnMouseUp, Args(cSpaceToolData* pTool), Args(pTool));
	auto_METHOD_VIRTUAL(cDefaultAoETool, cToolStrategy, bool, func48h, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));
	auto_METHOD_VIRTUAL(cDefaultAoETool, cToolStrategy, bool, func4Ch, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));

	//// cAbductToolStrategy ////

	auto_METHOD_VIRTUAL(cAbductToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));
	auto_METHOD_VIRTUAL(cAbductToolStrategy, cToolStrategy, bool, OnMouseUp, Args(cSpaceToolData* pTool), Args(pTool));
	Vector3 cAbductToolStrategy::GetAimPoint() {
		Vector3 dst;
		((void(__thiscall*)(cAbductToolStrategy*, Vector3&))(GetAddress(cAbductToolStrategy, GetAimPoint)))(this, dst);
		return dst;
	}


	//// cScanToolStrategy ////

	auto_METHOD_VIRTUAL(cScanToolStrategy, cToolStrategy, bool, OnSelect, Args(cSpaceToolData* pTool), Args(pTool));
	auto_METHOD_VIRTUAL(cScanToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));


	//// cDropCargoToolStrategy ////

	auto_METHOD_VIRTUAL(cDropCargoToolStrategy, cToolStrategy, bool, Update, Args(cSpaceToolData* pTool, bool arg1, const char16_t** arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cDropCargoToolStrategy, cToolStrategy, bool, WhileAiming, Args(cSpaceToolData* pTool, const Vector3& arg1, bool arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cDropCargoToolStrategy, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cDropCargoToolStrategy, cToolStrategy, bool, OnMouseUp, Args(cSpaceToolData* pTool), Args(pTool));


	//// cDragInputProjectileToolStrategy ////

	auto_METHOD_VIRTUAL_VOID(cDragInputProjectileToolStrategy, cToolStrategy, OnMouseDown, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));
	auto_METHOD_VIRTUAL(cDragInputProjectileToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));
	auto_METHOD_VIRTUAL(cDragInputProjectileToolStrategy, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cArtilleryWeaponStrategy ////

	auto_METHOD_VIRTUAL(cArtilleryWeaponStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));
	auto_METHOD_VIRTUAL(cArtilleryWeaponStrategy, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cMindEraseToolStrategy ////

	auto_METHOD_VIRTUAL(cMindEraseToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));


	//// cGlobalMindEraseToolStrategy ////

	auto_METHOD_VIRTUAL(cGlobalMindEraseToolStrategy, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cRepairAOEToolStrategy ////

	auto_METHOD_VIRTUAL(cRepairAOEToolStrategy, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cRallyCallToolStrategy ////

	auto_METHOD_VIRTUAL(cRallyCallToolStrategy, cToolStrategy, bool, WhileFiring, Args(cSpaceToolData* pTool, const Vector3& arg1, int arg2), Args(pTool, arg1, arg2));


	//// cToggleToolStrategy ////

	bool cToggleToolStrategy::OnSelect(cSpaceToolData* pTool) { return true; }
	bool cToggleToolStrategy::OnDeselect(cSpaceToolData* pTool) { return true; }
	void cToggleToolStrategy::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position) { }


	//// cPlaceColonyToolStrategy ////

	auto_METHOD_VIRTUAL(cPlaceColonyToolStrategy, cToolStrategy, bool, OnSelect, Args(cSpaceToolData* pTool), Args(pTool));
	auto_METHOD_VIRTUAL(cPlaceColonyToolStrategy, cToolStrategy, bool, OnDeselect, Args(cSpaceToolData* pTool), Args(pTool));
	auto_METHOD_VIRTUAL(cPlaceColonyToolStrategy, cToolStrategy, bool, Update, Args(cSpaceToolData* pTool, bool arg1, const char16_t** arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL(cPlaceColonyToolStrategy, cToolStrategy, bool, WhileAiming, Args(cSpaceToolData* pTool, const Vector3& arg1, bool arg2), Args(pTool, arg1, arg2));
	auto_METHOD_VIRTUAL_VOID(cPlaceColonyToolStrategy, cToolStrategy, SelectedUpdate, Args(cSpaceToolData* pTool, const Vector3& arg1), Args(pTool, arg1));
	auto_METHOD_VIRTUAL(cPlaceColonyToolStrategy, cToolStrategy, bool, OnHit, Args(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int arg_C), Args(pTool, position, hitType, arg_C));
}
#endif
