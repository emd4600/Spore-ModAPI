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

#include <EASTL\vector.h>
#include <EASTL\map.h>
#include <Spore\MathUtils.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cSpaceToolData.h>

using namespace eastl;

namespace Simulator
{
	///
	/// Any object that has hit points and can combat other units. This class acts more as a container of different variables
	/// (like the target combatant, number of hit points, etc), and therefore it barely has any combat logic on it. The combat logic
	/// is managed externally, by the cCombatSimulator class. 
	/// 
	/// Combatants can only fight with other combatants, and can only attack one of them at a time. To do so, use the SetTarget() method.
	/// If the class has no target, it won't attack anyone.
	///
	/// Several attributes can be saved into the game data:
	/// - mHealthPoints
	/// - mMaxHealthPoints
	/// - mLastAttacker
	/// - mArmorProbability
	///
	class cCombatant
	{
	public:
		static const uint32_t TYPE = 0x13F94D4;
		static const uint32_t NOUN_ID = 0x13F94D4;

		virtual ~cCombatant();

		inline void SetHealthPoints(float healthPoints) {
			mHealthPoints = healthPoints;
		}

		/// Returns the maximum range of this combatant's weapon.
		/// If this combatant does not use weapon tools, returns 0.
		inline float GetWeaponRange() {
			if (GetWeapon()) {
				return GetWeapon()->GetMaxRange();
			}
			else return 0.0f;
		}

		/* calling 2Ch with argument 0 repairs broken buildings */

		/* 04h */	virtual bool Write(void* arg_0);

		/// Returns the cSpatialObject that corresponds to this combatant.
		/* 08h */	virtual cSpatialObject* ToSpatialObject() = 0;

		/// Returns the cGameData that corresponds to this combatant.
		/* 0Ch */	virtual cGameData* ToGameData() = 0;

		/// Returns this object political ID, used to identify the cGameData.
		/* 10h */	virtual uint32_t GetPoliticalID() = 0;

		/// Returns the weapon tool used by this combatant. This is only available for vehicles.
		/* 14h */	virtual cSpaceToolData* GetWeapon();

		/* 18h */	virtual int func18h(float, int, int, int, int);  // used to substract health?

		/* 1Ch */	virtual void AddHostileUnit(cCombatant* combatant);
		/* 20h */	virtual Math::Vector3 func20h();

		/// Generates a random index that allows to select from the existing aim points.
		/* 24h */	virtual int GetRandomAimIndex();
		/* 28h */	virtual Math::Vector3 func28h(int);
		/* 2Ch */	virtual void func2Ch(bool);  // heals buildings?
		/* 30h */	virtual Math::Vector3 func30h();
		/* 34h */	virtual uint32_t func34h();  // returns field_70, an effect ID
		/* 38h */	virtual void func38h();  // sets lastAttacker to -1 and field_28 to nullptr
		/* 3Ch */	virtual bool func3Ch();  // related with cBehaviorTreeData!

		/// Returns true if the other combatant is inside the maximum range of this combatant's weapon.
		/// If this combatant does not use weapon tools, returns false.
		/* 40h */	virtual bool IsInWeaponRange(cCombatant* other);

		/// Returns true if the weapon has enough ammo (if it uses ammo) and is not recharging.
		/// If this combatant does not use weapon tools, returns false.
		/* 44h */	virtual bool IsWeaponCharged(int = 0);

		/* 48h */	virtual void func48h(int, int);
		/* 4Ch */	virtual void func4Ch(int);

		/// Sets the target combatant; if it is not nullptr, this object will start attacking the given combatant.
		/// There can only be one target at a time.
		/// @param target The new target combatant.
		/* 50h */	virtual void SetTarget(cCombatant* target);

		/// Returns the current target, that is, the combatant that this class is attacking, or nullptr if the class is not in combat.
		/* 54h */	virtual cCombatant* GetTarget();

		/* 58h */	virtual float GetMaxHitPoints();  // might return hit points or max hit points

		/// Same as Object::Cast(uint32_t)
		/* 5Ch */	virtual void* Cast(uint32_t type);
		/// Same as Object::AddRef().
		/* 60h */	virtual int AddRef() = 0;
		/// Same as Object::Release().
		/* 64h */	virtual int Release() = 0;

	protected:
		// WARNING: there's no "field_4". The vfpointer is 8 bytes long because cGonzagoTimer sets alignment to 8!
		/* 08h */	bool field_8;  // if true, it's ignored when checking mouse position
		/* 09h */	bool field_9;
		/* 0Ch */	map<int, int> field_0C;
		/* 28h */	intrusive_ptr<cCombatant> field_28;
		/* 2Ch */	float mMaxHealthPoints;  // 10.0
		/* 30h */	intrusive_ptr<Object>  field_30;
		/* 34h */	int field_34;
		/* 38h */	float mHealthPoints;  // 10.0
		/* 3Ch */	int mLastAttacker;  // -1
		/* 40h */	float mArmorProbability;  // 0.5
		/* 44h */	intrusive_ptr<cCombatant> field_44;
		/* 48h */	intrusive_ptr<cCombatant> mpTarget;
		/* 4Ch */	Vector3 field_4C;
		/* 58h */	vector<Vector3> mAimPoints;
		/* 6Ch */	bool field_6C;  // true, needsToLoadAimPoints?
		/* 70h */	uint32_t field_70;  // an effect ID
		/* 74h */	Vector3 field_74;
		/* 80h */	bool field_80;
		/* 81h */	bool field_81;
		/* 84h */	vector<cGonzagoTimer> field_84;
		/* 98h */	cGonzagoTimer field_98;
		/* B8h */	int field_B8;  // not initialized
		/* BCh */	int field_BC;
		/* C0h */	intrusive_ptr<Object> field_C0;
		/* C4h */	intrusive_ptr<Object> field_C4;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cCombatant) == 0xC8, "sizeof(cCombatant) != C8h");

}
