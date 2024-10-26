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

#include <Spore\Simulator\cCreatureBase.h>
#include <Spore\Simulator\cSpeciesProfile.h>

#define cCreatureAnimalPtr eastl::intrusive_ptr<Simulator::cCreatureAnimal>

namespace Simulator
{
	class cHerd;

	class cCreatureAnimal
		: public cCreatureBase
	{
	public:
		static const uint32_t TYPE = 0xD0036E08;
		static const uint32_t NOUN_ID = 0x18EB45E;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		static cCreatureAnimal* Create(const Vector3& pPosition, cSpeciesProfile* pSpecies, int age = 1, cHerd* pHerd = nullptr, bool bIsAvatar = false, bool = false);

		void NPCTickAI(float deltaTime);
		void AvatarTickAI(float deltaTime);

	public:
		/* FC0h */	cGonzagoTimer mNoDamageTimer;
		/* FE0h */	cGonzagoTimer mLastAvatarDamageTimer;
		/* 1000h */	float field_1000;
		/* 1004h */	ResourceKey mNextSpecies; 
		/* 1010h */	ColorRGB mColor;
		/* 101Ch */	int field_101C;
		/* 1020h */	eastl::vector<int> field_1020;
		/* 1034h */	eastl::deque<int> field_1034;
		/* 1060h */ eastl::deque<int> field_1060;
		/* 108Ch */	eastl::fixed_vector<int, 32> field_108C;
		/* 1124h */	eastl::fixed_vector<int, 128> field_1124;
		/* 133Ch */	eastl::fixed_vector<int, 32> field_133C;
		/* 13D4h */	eastl::fixed_vector<int, 8> field_13D4;
		/* 140Ch */	eastl::fixed_vector<int, 128> field_140C;
		/* 1624h */	int field_1624;  // cAIMemory
		/* 1628h */	cGonzagoTimer field_1628;
		//TODO struct related with adventures, check sub_D98AC0
		/* 1648h */	int field_1648;
		/* 164Ch */	int field_164C;
		/* 1650h */	int field_1650;  // 1
		/* 1654h */	Vector3 field_1654;
		/* 1660h */	float field_1660;
		/* 1664h */	int field_1664;  // 5
		/* 1668h */	int field_1668;
		/* 166Ch */	bool field_166C;  // not initialized
		/* 166Dh */	bool field_166D;
		/* 1670h */	int field_1670;
		/* 1674h */	eastl::intrusive_ptr<cHerd> mHerd;  // cHerd ?
		/* 1678h */	int mPregnantEggs;
		/* 167Ch */	float mUntargetDistanceTime;
		/* 1680h */	uint32_t mOwnerMissionID;
		/* 1684h */	int mPersonality;
		/* 1688h */	int field_1688;
		/* 168Ch */	float field_168C;
		/* 1690h */	float field_1690;
		/* 1694h */	float mCharmDamage;
		/* 1698h */	cCombatantPtr mpCharmer;
		/* 169Ch */	float mCharmTime;
	};
	ASSERT_SIZE(cCreatureAnimal, 0x16A0);

	namespace Addresses(cCreatureAnimal) {
		DeclareAddress(Create);
		DeclareAddress(NPCTickAI);  // 0xC08CD0 0xC09570
		DeclareAddress(AvatarTickAI);  // 0xC03710 0xC04020
		DeclareAddress(OnJumpLand);  // 0xC044D0 0xC04CB0
		DeclareAddress(OnStartSwimming);  // 0xC04610 0xC04DF0
		DeclareAddress(Update);  // 0xC0A590 0xC0AE30
		DeclareAddress(TakeDamage);
	}
}