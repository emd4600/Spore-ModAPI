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

#include <Spore\App\PropertyList.h>
#include <Spore\Simulator\cSpaceInventoryItem.h>
#include <Spore\Simulator\cGonzagoTimer.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cDefaultAoEArea.h>
#include <Spore\Simulator\cDefaultBeamProjectile.h>
#include <Spore\LocalizedString.h>

namespace Simulator
{
	class cToolStrategy;

	class cSpaceToolData
		: public cSpaceInventoryItem
	{
	public:
		static const uint32_t TYPE = 0x707459F0;

		enum SpaceToolHit
		{
			kHitCombatant = 0,
			kHitGround = 1,
			kHitWater = 2,
			kHitAir = 3
		};

		enum SpaceToolTarget
		{
			/* shr 0 */	kTargetAnimal = 1,
			/* shr 1 */	kTargetA13ABC9F = 2,
			/* shr 2 */	kTargetUFO = 4,
			/* shr 3 */	kTargetVehicle = 8,
			/* shr 4 */	kTargetTurret = 0x10,
			/* shr 5 */	kTargetCity = 0x20,
			/* shr 6 */	kTargetBuilding = 0x40,
			/* shr 7 */	kTargetWorld = 0x80,
			/* shr 8 */	kTargetAir = 0x100,
			/* shr 9 */	kTargetA6663355 = 0x200,
			/* shr 10 */	//4BF0FA5A = 0x400
		};

		enum SpaceToolFlags
		{
			/// If the beam takes the surface orientation on hit or uses the beam
			/* shr 00 */	kFlagHitOrientsToTerrain = 0x1,
			/// If the beam effect passes through any combatants to hit the terrain or water
			/* shr 01 */	kFlagBeamPassThrough = 0x2,
			/* shr 02 */	kFlagIsHoming = 0x4,
			/// Does this tool destroy flora and fauna?
			/* shr 03 */	kFlagDestroysFloraAndFauna = 0x8,
			/// Does this tool need to interact with creature trees?
			/* shr 04 */	kFlagPicksFlora = 0x10,
			/// Flag if the tool requires the use of ammo
			/* shr 05 */	kFlagUsesAmmo = 0x20,
			/// Disable this tool on the users homeworld
			/* shr 06 */	kFlagDisableOnHomeWorld = 0x40,
			/// Disable this tool when visiting savegame worlds
			/* shr 07 */	kFlagDisableOnSaveGames = 0x80,
			/// If the projectile ignores all collisions
			/* shr 08 */	kFlagPassTroughAll = 0x100,
			/// If the projectile damages friendlies
			/* shr 09 */	kFlagDamagesFriendlies = 0x200,
			/* shr 10 */	kFlagPreventsPlanetExit = 0x400,
			/* shr 11 */	kFlagProjectileLobAngle = 0x800,
			/// If the tool waits for the hit effect to resolve
			/* shr 12 */	kFlagDoActionPostEffect = 0x1000,
			/* shr 13 */	kFlagOnlyOnPlayerColonies = 0x2000,
			/* shr 14 */	kFlagOnlyOnNPCColonies = 0x4000,
			/// When this tool is selected in the interface, it will be automatically used and deselected
			/* shr 15 */	kFlagUseOnActivate = 0x8000,
			/* shr 16 */	kFlagCanPlayerLockOn = 0x10000,
			/// Disable this tool when visiting 201 world
			/* shr 17 */	kFlagDisableOn201Ruins = 0x20000,
			/// If the projectile effect passes through any combatants to hit the terrain or water
			/* shr 18 */	kFlagProjectilePassThrough = 0x40000,
			/* shr 19 */	kFlagIsSuperWeapon = 0x80000
		};

		// constructor sub_104D0D0 (_ZN14cmDataC2Ev)

		// sub_1051710 consumes energy?

		// virtual function sub_104DA80 -> parseprop

		///
		/// Adds a certain quantity to the current ammount of ammo of the tool, 
		/// ensuring it is not greater than the `mMaxAmmoCount` property.
		/// @param ammo
		///
		void AddAmmo(int amount);

		///
		/// Removes a certain quantity of ammo. By default the removed ammo is taken from the property `mAmmoUsedPerShot`,
		/// but it can also be specified manually.
		/// @param amount The amount of ammo to remove or -1.
		/// 
		void ConsumeAmmo(int amount = -1);

		//TODO maxRange * rangeMultipler
		inline float GetMinRange() const {
			return this->mRangeMultiplier * this->mMinRange;
		}
		inline float GetMaxRange() const {
			return this->mRangeMultiplier * this->mMaxRange;
		}
		inline bool IsTargetAir() const {
			return (this->mTargetFlags & kTargetAir) != 0;
		}

		cToolStrategy* GetStrategy() const;

		static uint32_t ShowEventLog(cSpaceToolData* pTool, uint32_t eventLogID, bool show=true);

		//TODO sub_1050A70 IsRecharging()
		//TODO sub_10509B0 IsBeamTool()
		//TODO sub_1050A10 IsToggleTool()
		//TODO PLACEHOLDER sub_104D7A0 DeselectAfterUse() ?
		//PLACEHOLDER 0x3C5DBC7 message to enter editor?

		// sub_104C8D0 is recharging or in use


	public:
		/* 7Ch */	int mCurrentAmmoCount;
		/* 80h */	bool mbIsInUse;
		/* 88h */	cGonzagoTimer mRechargeTimer;
		/* A8h */	cGonzagoTimer mAutoFireTimer;
		/* C8h */	cGonzagoTimer mChargeTimer;
		/* E8h */	cGonzagoTimer mMissCheckTimer;
		/* 108h */	intrusive_ptr<Object> field_108;
		/* 10Ch */	intrusive_ptr<Object> field_10C;
		/* 110h */	intrusive_ptr<Object> field_110;
		/* 114h */	intrusive_ptr<cSpatialObject> mpToolOwner;
		/* 118h */	intrusive_ptr<cSpatialObject> mpToolTarget;
		/* 11Ch */	int mTargetDamagePointId;
		/* 120h */	intrusive_ptr<cDefaultAoEArea> mpArea;
		/* 124h */	intrusive_ptr<cDefaultBeamProjectile> mpBeam;
		/* 128h */	int field_128;
		/* 12Ch */	intrusive_ptr<Object> mpAppTarget;  // it really is object
		/* 130h */	char padding_130[0xC];  // 134h cSpaceToolDAta
		/* 13Ch */	bool mbInterruptedByDamage;
		/* 140h */	int field_140;  // effect?
		/* 144h */	float mDamageMultiplier; // 1.0
		/* 148h */	float mRangeMultiplier; // 1.0
		/* 14Ch */	float mProjectileScale;
		/* 150h */	bool feld_150;
		/* 154h */	float field_154;
		/* 158h */	float field_158;
		/* 15Ch */	float field_15C;
		/* 160h */	float field_160;
		/* 164h */	float field_164;
		/* 168h */	float field_168;
		/* 16Ch */	int field_16C;
		/* 170h */	int field_170;
		/* 174h */	SpaceToolFlags mFlags;
		/// Strategy class to use for custom behavior beyond normal tool usage
		/* 178h */	int mStrategy;
		/// Weapon, terraforming, special, other (a grouping for the tool in the various UI buckets)
		/* 17Ch */	uint32_t mType;  // 0x8DA5FFB9 other
		/// Projectile, etc
		/* 180h */	uint32_t mWeaponSubType;  // -1
		/// Artillery, pulse
		/* 184h */	uint32_t mProjectileType;  // -1
		/* 188h */	uint32_t mProjectileMotion;  // 0x82CE6992
		/// Defines where the tool can be used (always, planet, space, passive).
		/* 18Ch */	uint32_t mContext;
		/// The file which serves as an upgrade to this tool.
		/* 190h */	ResourceKey mUpgradeFile;
		/// The amount of ammo each shot consumes
		/* 19Ch */	int mAmmoUsedPerShot;
		/// The maximum ammo for the tool
		/* 1A0h */	int mMaxAmmoCount;
		/// The cost to use the tool once
		/* 1A4h */	int mUseCost;
		/// Energy required per use
		/* 1A8h */	float mEnergyCost;
		/// The world unit radius in which the tool will destroy game objects
		/* 1ACh */	float mDamageArea;
		/// The range at which cities can detect the usage of weaponry
		/* 1B0h */	float mDetectableRange;
		/// Minimum damage the tool will cause if it registers for damage
		/* 1B4h */	float mMinDamage;
		/// Maximum damage the tool will cause if it registers for damage
		/* 1B8h */	float mMaxDamage;
		/// Maximum projectile scaling for this tool
		/* 1BCh */	float mMaxProjectileScale;
		/// The time (in seconds) that it takes the tool to recharge before it can be used again
		/* 1C0h */	float mRechargeRate;
		/// The time (in seconds) between repeat firings of a weapon (-1 means never)
		/* 1C4h */	float mAutoFireRate;
		/// Min range for a tool to be fireable (-1 means no range constraint)
		/* 1C8h */	float mMinRange;
		/// Max range over which a tool can fire (-1 means no range constraint)
		/* 1CCh */	float mMaxRange;
		/// Damage radius (only used by Area of Effect weapons)
		/* 1D0h */	float mDamageRadius;
		/// The time (in seconds) for the weapon to fully charge before firing
		/* 1D4h */	float mChargeRate;
		/// Projectile speed
		/* 1D8h */	float mProjectileSpeed;
		/// Projectile acceleration
		/* 1DCh */	float mProjectileAcceleration;
		/// How fast it can turn, used by turret defense missiles
		/* 1E0h */	float mProjectileTurnRate;
		/// Altitude at which it explodes
		/* 1E4h */	float mProjectileMaxAltitude;
		/// Lowest altitude the projectile can explode at
		/* 1E8h */	float mProjectileMinAltitude;
		/// Distance from target, inside of which it explodes
		/* 1ECh */	float mProjectileDetonationDistance;
		/// Time in seconds before the projectile will explode naturally
		/* 1F0h */	float mProjectileTimeOut;
		/* 1F4h */	float mProjectileEccentricity;
		/// How much relationship changes when this tool hits
		/* 1F8h */	float mRelationshipDelta;
		/// How much all empires' relationship changes when this tool hits
		/* 1FCh */	float mGalacticRelationshipDelta;
		/* 200h */	float mGalacticRelationshipRadius;
		/// How many charges rewarded to the player on civ transition
		/* 204h */	int mCulturalRewardCount;
		/// How many charges rewarded to the player on civ transition
		/* 208h */	int mMilitaryRewardCount;
		/// How many charges rewarded to the player on civ transition
		/* 20Ch */	int mEconomicRewardCount;
		/// How many charges rewarded to player when they discover the meaning of life (enter the galactic core)
		/* 210h */	int mMeaningOfLifeRewardCount;
		/// Degree angle up from horizontal that the projectile will be lobbed from
		/* 214h */	float mProjectileLobAngle;
		/// Effect component for hitting the player
		/* 218h */	uint32_t mHitPlayerEffectID;
		/// Effect component for beam style weapons
		/* 21Ch */	uint32_t mBeamEffectID;
		/// Effect component for beam style weapons
		/* 220h */	uint32_t mHitGroundEffectID;
		/// Effect component for beam style weapons
		/* 224h */	uint32_t mHitWaterEffectID;
		/// Effect component for beam style weapons
		/* 228h */	uint32_t mHitCombatantEffectID;
		/// Effect that is emitted from the shooter
		/* 22Ch */	uint32_t mMuzzleEffectID;
		/// Effect that plays as the projectile flies through the air
		/* 230h */	uint32_t mProjectileEffectID;
		/// Effect that is pinned to the terrain for the duration of a deep space projectile's life
		/* 234h */	uint32_t mTargetEffectID;
		/// Rate at which a projectile's explosion spreads (use a high number for instantaneous)
		/* 238h */	float mProjectileExplosionExpansionRate;
		/* 23Ch */	uint32_t mPlacedModelKey;
		/// Hash of slots, map, or none
		/* 240h */	uint32_t mMinimapSlotsToggleEffectID;
		/* 244h */	uint32_t mTerraformingIconID;
		/* 248h */	int mTerrainColorIndex;
		/* 24Ch */	int mWaterColorIndex;
		/* 250h */	int mAtmosphereColorIndex;
		/* 254h */	SpaceToolTarget mTargetFlags;
		/* 258h */	LocalizedString mTargetFlagsFailMessage;
		/// Velocity added to atmosphere terraforming element when the tool is used on the ground
		/* 26Ch */	float mHitGroundAtmosphereVelocity;
		/// Velocity added to water terraforming element when the tool is used on the ground
		/* 270h */	float mHitGroundWaterVelocity;
		/// Velocity added to temperature terraforming element when the tool is used on the ground
		/* 274h */	float mHitGroundTemperatureVelocity;
		/// Velocity added to atmosphere terraforming element when the tool is used on the water
		/* 278h */	float mHitWaterAtmosphereVelocity;
		/// Velocity added to water terraforming element when the tool is used on the water
		/* 27Ch */	float mHitWaterWaterVelocity;
		/// Velocity added to temperature terraforming element when the tool is used on the water
		/* 280h */	float mHitWaterTemperatureVelocity;
		/// Vlocity added to atmosphere terraforming element when the tool is used on a combatant
		/* 284h */	float mHitCombatantAtmosphereVelocity;
		/// Velocity added to water terraforming element when the tool is used on a combatant
		/* 288h */	float mHitCombatantWaterVelocity;
		/// Velocity added to temperature terraforming element when the tool is used on a combatant
		/* 28Ch */	float mHitCombatantTemperatureVelocity;
		/// Velocity added to atmosphere terraforming element when the tool that detonates in air
		/* 290h */	float mHitAirAtmosphereVelocity;
		/// Velocity added to water terraforming element when the tool is used on detonates in air
		/* 294h */	float mHitAirWaterVelocity;
		/// Velocity added to temperature terraforming element when the tool is used on detonates in air
		/* 298h */	float mHitAirTemperatureVelocity;

		/* 29Ch */	int field_29C;  // not initialized

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cSpaceToolData) == 0x2A0, "sizeof(cSpaceToolData) != 0x2A0");

	namespace Addresses(cSpaceToolData)
	{
		DeclareAddress(AddAmmo, SelectAddress(0x104D730, 0x104CBE0, 0x104CBE0));
		DeclareAddress(ConsumeAmmo, SelectAddress(0x104D760, 0x104CC10, 0x104CC10));
		DeclareAddress(GetStrategy, SelectAddress(0x1050490, NO_ADDRESS, 0x1050030));
		DeclareAddress(ShowEventLog, SelectAddress(0x1053350, NO_ADDRESS, 0x1052800));
	}
}