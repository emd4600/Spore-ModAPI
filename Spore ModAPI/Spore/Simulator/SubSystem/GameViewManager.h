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
#include <Spore\Graphics\IRenderable.h>
#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\cViewer.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <EASTL\intrusive_list.h>
#include <EASTL\vector.h>
#include <EASTL\map.h>
#include <EASTL\hash_map.h>
#include <EASTL\fixed_vector.h>

/// Gets the active game view manager.
#define GameViewManager (*Simulator::cGameViewManager::Get())

namespace Addresses(Simulator)
{
	DeclareAddress(LightingWorld_ptr);
}

namespace Simulator
{
	using namespace Math;

	class cCombatant;

	class cGameViewManager
		: public Graphics::IRenderable
		, public App::IMessageListener
		, public cStrategy
	{
	public:
		/// The ID used for the Simulator model world, effects world
		static const uint32_t GraphicsWorldID = 0xEB9968;
		/// The ID used for the Simulator lighting world, effects world
		static const uint32_t LightingWorldID = 0x4A4DEA0;

		//PLACEHOLDER initialize alll simulator systems? sub_B33270

		//TODO PLACEHOLDER
		/* 10h */	virtual void func10h_();
		/* 14h */	virtual void PrepareSimulator();
		/* 18h */	virtual void func18h_();
		/* 1Ch */	virtual void func1Ch_();
		/* 20h */	virtual void func20h_();
		/* 24h */	virtual void func24h_();
		/* 28h */	virtual void func28h_();
		/* 2Ch */	virtual void func2Ch_();
		/* 30h */	virtual void func30h_(long nEllapsedMilliseconds);
		/* 34h */	virtual int func34h_();  // get cRotationRing?
		/* 38h */	virtual Vector3 func38h_(int, struct Vector3);
		/* 3Ch */	virtual Vector3 func3Ch_(int);
		// if pPlayer is not null, it ignores it when checking the position
		// apparently only detects certain objects like airplanes, creatures, city walls, buildings but not planet ornaments
		/* 40h */	virtual Vector3 GetWorldMousePosition(int=0, cCombatant* pCombanant=nullptr);

	protected:
		/* 24h */	intrusive_list<int> field_24;
		/* 2Ch */	fixed_vector<int, 16> field_2C;
		/* 84h */	uint32_t mGameModeID;  // -1
		/* 88h */	intrusive_ptr<Object> field_88;
		/* 8Ch */	hash_map<int, int> field_8C;
		/* ACh */	vector<int> field_AC;
		/* C0h */	bool field_C0;
		/* C1h */	bool field_C1;  // visible?
		/* C4h */	intrusive_ptr<int> field_C4;  // release at 8
		/* C8h */	map<int, int> field_C8;
		/* E4h */	intrusive_ptr<Object> field_E4;  // IModelWorld?
		/* E8h */	intrusive_ptr<Object> field_E8;
		/* ECh */	App::cViewer* field_EC;  // with hologram render type
		/* F0h */	int field_F0;  // not initialized, ResourceKey?
		/* F4h */	int field_F4;  // not initialized
		/* F8h */	int field_F8;  // not initialized
		/* FCh */	int field_FC;
		/* 100h */	int field_100;
		/* 104h */	int field_104;
		/* 108h */	intrusive_ptr<Object> mpCreatureFXAnimWorld;
		/* 10Ch */	bool mbSuperHighResVehicles;
		/* 10Dh */	bool mbSuperHighResIgnoreCount;
		/* 10Eh */	bool mbSuperHighResBuildings;
		/* 110h */	fixed_vector<int, 32> field_110;  // ?

	public:
		/// Gets the active game view manager.
		static cGameViewManager* Get();
	};

	inline Graphics::ILightingWorld* GetLightingWorld() {
		return *(Graphics::ILightingWorld**)(GetAddress(Simulator, LightingWorld_ptr));
	}


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cGameViewManager) == 0x1A8, "sizeof(cGameViewManager) != 1A8h");

	namespace Addresses(cGameViewManager)
	{
		DeclareAddress(Get);
	}
}