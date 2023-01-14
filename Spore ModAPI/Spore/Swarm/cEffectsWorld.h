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

#include <Spore\Swarm\IEffectsWorld.h>
#include <Spore\Swarm\IEffectsManager.h>
#include <Spore\Object.h>

#include <EASTL\vector.h>
#include <EASTL\string.h>

namespace Swarm
{

	// TODO: Uncompleted
	class cEffectsWorld : public IEffectsWorld, public IVirtual
	{
	public:
		cEffectsWorld(IEffectsManager* pManager, cGlobalParams* pGlobalParams);

	protected:
		/* 08h */	int mnRefCount;
		/* 0Ch */	bool field_0C;
		/* 10h */	int field_10;
		/* 14h */	IEffectsManager* mpManager;
		/* 18h */	cGlobalParams* mpGlobalParams;  // it's a copy of the one in the constructor
		/* 1Ch */	int field_1C;
		/* 20h */	SwarmState mState;
		/* 24h */	bool field_24;
		/* 28h */	int field_28;  // 1
		/* 2Ch */	int field_2C;
		/* 30h */	eastl::vector<IVisualEffectPtr> field_30;
		/* 44h */	eastl::vector<int> field_44;  // indices to field_30
		/* 58h */	eastl::vector<int> field_58;
		/* 6Ch */	eastl::vector<int> field_6C;
		/* 80h */	int field_80;  // 1
		/* 84h */	int field_84;  // 1
		/* 88h */	float field_88;  // 1.0f
		/* 8Ch */	int field_8C;  // not initialized
		/* 90h */	int field_90;
		/* 94h */	eastl::string field_94;


		// 20h state
		// 90h effectCount

		/* 14h */	virtual void SetLOD(float value, int) override = 0;
	};
	ASSERT_SIZE(cEffectsWorld, 0xA4);
}