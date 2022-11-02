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

#include <Spore\Swarm\IEffect.h>
#include <Spore\Swarm\IEffectsWorld.h>
#include <Spore\Swarm\IEffectMap.h>
#include <Spore\Swarm\ISurface.h>
#include <Spore\Object.h>
#include <Spore\Internal.h>
#include <EASTL\vector.h>

/// Access the active effects manager.
#define EffectsManager (*Swarm::IEffectsManager::Get())

#define IEffectsManagerPtr intrusive_ptr<Swarm::ISwarmManager>

namespace Swarm
{
	/// This class is the main manager of the Swarm effects system. It allows to create instances of effects. 
	/// The manager also can be used to create IEffectsWorld, which are the objects that contain the effects. 
	/// The manager creates instances of effects using the currently active effect world.
	class IEffectsManager
	{
	public:
		/* 00h */	virtual bool Initialize() = 0;
		/* 04h */	virtual bool Dispose() = 0;
		/* 08h */	virtual int AddRef() = 0;
		/* 0Ch */	virtual int Release() = 0;

		// Swarm::cIResources*
		/* 10h */	virtual void SetResources(Object*) = 0;
		/* 14h */	virtual Object* Resources() = 0;
		// Swarm::cIRenderer*
		/* 18h */	virtual void SetRenderer(Object*) = 0;
		/* 1Ch */	virtual Object* Renderer() = 0;
		// Swarm::cIDecalManager*
		/* 20h */	virtual void SetDecalManager(void*, int index) = 0;
		/* 24h */	virtual void* DecalManager(int index) = 0;

		///
		/// Returns whether an effect with this instance and group ID exists in any of the effect directories (effdir) in the manager.
		/// @param instanceID The instance ID of the effect.
		/// @param groupID The group ID of the effect, usually 0.
		///
		/* 28h */	virtual bool HasVisualEffect(uint32_t instanceID, uint32_t groupID) const = 0;
		// the dst mut not be initialized, becuase the previous object is ignored.

		///
		/// Creates an effect object with this instance and group ID in the default effect world. The destination is an 
		/// uninitialized intrusive_ptr; the object must be nullptr or not be initialized, because it will be ignored.
		/// @param instanceID The instance ID of the effect.
		/// @param groupID The group ID of the effect, usually 0.
		/// @param[out] dst An uninitialized intrusive_ptr<IEffect> where the effect will be put.
		/// @returns True if the effect was found and returned, false otherwise.
		///
		/* 2Ch */	virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IEffectPtr& dst) = 0;

		/* 30h */	virtual void SetState(SwarmState state) = 0;
		/* 34h */	virtual SwarmState State() = 0;

		/* 38h */	virtual void SetLOD(float value, int = 5) = 0;

		/* 3Ch */	virtual void SetDefaultTimeline(int timelineType) = 0;

		/* 40h */	virtual void DoUpdate(float, float) = 0;

		/* 44h */	virtual void DoUpdate2(float, float) = 0;  // calls Update

		/* 48h */	virtual void ResetState() = 0;

		///
		/// Creates a new IEffectsWorld mapped to the given ID.
		/// @param worldID The ID the world will be mapped to.
		///
		/* 4Ch */	virtual IEffectsWorld* CreateWorld(uint32_t worldID, int=0) = 0;
		
		///
		/// Removes the IEffectsWorld mapped to the given ID from this manager. If the ID is not mapped, this method
		/// does nothing.
		/// @param worldID The ID the world to remove is mapped to.
		///
		/* 50h */	virtual void RemoveWorld(uint32_t worldID) = 0;

		/// 
		/// Returns the IEffectsWorld mapped to the given ID, or nullptr if the ID is not mapped.
		/// An ID of 0 returns the default world.
		/// @param worldID The ID the world is mapped to.
		///
		/* 54h */	virtual IEffectsWorld* World(uint32_t worldID) = 0;

		///
		/// Sets the given effect world to be the default one; it does not need to be mapped.
		/// If the world is nullptr, the default world will be set as active.
		/// @param pWorld The world that will be set as active, or nullptr to set the default world.
		///
		/* 58h */	virtual void SetDefaultWorld(IEffectsWorld* pWorld) = 0;

		///
		/// Returns the active effect world.
		///
		/* 5Ch */	virtual IEffectsWorld* DefaultWorld() = 0;

		/* 60h */	virtual void GetWorldIDs(vector<uint32_t>& dst) = 0;

		/* 64h */	virtual bool AddCollection(void*) = 0;
		/* 68h */	virtual bool RemoveCollection(void*) = 0;
		/* 6Ch */	virtual void* GetResources(uint32_t instanceID, uint32_t groupID, int) = 0;
		/* 70h */	virtual int GetComponentDescription(int, int, int) = 0;
		/* 74h */	virtual int GetAuxiliaryDescription(int, int, int) = 0;

		///
		/// Maps the given ISurface to the specified ID. 
		/// @param surfaceID The ID of the surface.
		/// @param pSurface
		///
		/* 78h */	virtual void RegisterSurface(class ResourceID surfaceID, ISurface* pSurface) = 0;

		///
		/// Gets the ISurface mapped to the specified ID, or nullptr if none is mapped to that ID.
		/// @param surfaceID The ID of the surface.
		///
		/* 7Ch */	virtual ISurface* Surface(class ResourceID surfaceID) = 0;

		/* 80h */	virtual void RegisterSurfaceName(const char* pName, class ResourceID surfaceID, void* callback) = 0;

		/* 84h */	virtual bool SurfaceInfo(class ResourceID surfaceID, void* callback) = 0;

		/* 88h */	virtual void RegisterMap(class ResourceID mapID, IEffectMap* pMap) = 0;
		/* 8Ch */	virtual IEffectMap* Map(class ResourceID mapID) = 0;  //CreateResourceMap? find 0x016F280B
		/* 90h */	virtual void RegisterMapName(const char* pName, class ResourceID mapID) = 0;
		/* 94h */	virtual ResourceID MapID(int) = 0;

		///
		/// Set the given application flag.
		/// @param flag The flag to set.
		/// @param bValue The new value of the flag.
		///
		/* 98h */	virtual void SetAppFlag(int flag, bool bValue) = 0;
		/* 9Ch */	virtual bool AppFlag(int flag) = 0;

		//TODO returns cGlobalParams
		/* A0h */	virtual void* GlobalParams() = 0;
		/* A4h */	virtual void* GlobalParams2() = 0;

		/* A8h */	virtual void UpdateProperties(void*) = 0;

		/* ACh */	virtual const char* GetStatsString() = 0;

		/* B0h */	virtual void* Stats() = 0;

		/* B4h */	virtual void GetActiveEffectInfo(int, int, int infoLevel) = 0;

		//TODO parameter is cEffectInfo
		/* B8h */	virtual bool GetEffectInfo(void* pDst, const char* pName) = 0;
		/* BCh */	virtual bool GetEffectInfo2(vector<int>& dst, const char* pName) = 0;
		/* C0h */	virtual bool OpenEffectFile(const char* pName) = 0;
		/* C4h */	virtual bool GetEffectDebugName(uint32_t instanceID, uint32_t groupID, int) = 0;

		///
		/// Gets the active manager of the Swarm system.
		///
		static IEffectsManager* Get();
	};

	namespace Addresses(ISwarmManager)
	{
		DeclareAddress(Get);
	}
	namespace Addresses(IEffectsManager)
	{
		DeclareAddress(Get);
	}
}
