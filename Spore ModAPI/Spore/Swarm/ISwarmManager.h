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
#include <Spore\Swarm\IEffectWorld.h>
#include <Spore\Swarm\ISurface.h>
#include <Spore\Object.h>
#include <Spore\Internal.h>

/// Access the active swarm manager.
#define SwarmManager (*Swarm::ISwarmManager::Get())

///
/// Swarm is the effects system of Spore.
///
namespace Swarm
{
	///
	/// This class is the main manager of the Swarm effects system. It allows to create instances of effects. 
	/// The manager also can be used to create IEffectWorld, which are the objects that contain the effects. 
	/// The manager creates instances of effects using the currently active effect world.
	///
	class ISwarmManager
	{
	public:
		/* 00h */	virtual bool Initialize() = 0;
		/* 04h */	virtual bool Dispose() = 0;
		/* 08h */	virtual int AddRef() = 0;
		/* 0Ch */	virtual int Release() = 0;

		/* 10h */	virtual void func10h(Object*) = 0;
		/* 14h */	virtual Object* func14h() = 0;
		/* 18h */	virtual void func18h(Object*) = 0;
		/* 1Ch */	virtual Object* func1Ch() = 0;
		/* 20h */	virtual void func20h(int, int) = 0;
		/* 24h */	virtual int func24h(int) = 0;

		///
		/// Returns whether an effect with this instance and group ID exists in any of the effect directories (effdir) in the manager.
		/// @param instanceID The instance ID of the effect.
		/// @param groupID The group ID of the effect, usually 0.
		///
		/* 28h */	virtual bool HasEffect(uint32_t instanceID, uint32_t groupID) const = 0;
		// the dst mut not be initialized, becuase the previous object is ignored.

		///
		/// Creates an effect object with this instance and group ID in the active effect world. The destination is an 
		/// uninitialized intrusive_ptr; the object must be nullptr or not be initialized, because it will be ignored.
		/// @param instanceID The instance ID of the effect.
		/// @param groupID The group ID of the effect, usually 0.
		/// @param dst An uninitialized intrusive_ptr<IEffect> where the effect will be put.
		/// @returns True if the effect was found and returned, false otherwise.
		///
		/* 2Ch */	virtual bool CreateEffect(uint32_t instanceID, uint32_t groupID, intrusive_ptr<IEffect>& dst) = 0;

		/* 30h */	virtual void func30h(int) = 0;
		/* 34h */	virtual int func34h() = 0;

		/* 38h */	virtual void SetLOD(float value, int = 5) = 0;

		/* 3Ch */	virtual void func3Ch(int) = 0;

		/* 40h */	virtual void Update(float, float) = 0;

		/* 44h */	virtual void func44h(float, float) = 0;  // calls Update
		/* 48h */	virtual void func48h() = 0;


		///
		/// Creates a new IEffectWorld mapped to the given ID.
		/// @param worldID The ID the world will be mapped to.
		///
		/* 4Ch */	virtual IEffectWorld* CreateWorld(uint32_t worldID, int=0) = 0;
		
		///
		/// Removes the IEffectWorld mapped to the given ID from this manager. If the ID is not mapped, this method
		/// does nothing.
		/// @param worldID The ID the world to remove is mapped to.
		///
		/* 50h */	virtual void RemoveWorld(uint32_t worldID) = 0;

		/// 
		/// Returns the IEffectWorld mapped to the given ID, or nullptr if the ID is not mapped.
		/// An ID of 0 returns the default world.
		/// @param worldID The ID the world is mapped to.
		///
		/* 54h */	virtual IEffectWorld* GetWorld(uint32_t worldID) = 0;

		///
		/// Sets the given effect world to be the active one; it does not need to be mapped.
		/// If the world is nullptr, the default world will be set as active.
		/// @param pWorld The world that will be set as active, or nullptr to set the default world.
		///
		/* 58h */	virtual void SetActiveWorld(IEffectWorld* pWorld) = 0;

		///
		/// Returns the active effect world.
		///
		/* 5Ch */	virtual IEffectWorld* GetActiveWorld() = 0;

		/* 60h */	virtual void func60h(int) = 0;
		/* 64h */	virtual bool func64h(int) = 0;
		/* 68h */	virtual bool func68h(int) = 0;
		/* 6Ch */	virtual int func6Ch(uint32_t instanceID, uint32_t groupID, int) = 0;
		/* 70h */	virtual int func70h(int, int, int) = 0;
		/* 74h */	virtual int func74h(int, int, int) = 0;

		///
		/// Maps the given ISurface to the specified ID. 
		/// @param surfaceID The ID of the surface.
		/// @param pSurface
		///
		/* 78h */	virtual void AddSurface(class ResourceID surfaceID, ISurface* pSurface) = 0;

		///
		/// Gets the ISurface mapped to the specified ID, or nullptr if none is mapped to that ID.
		/// @param surfaceID The ID of the surface.
		///
		/* 7Ch */	virtual ISurface* GetSurface(class ResourceID surfaceID) = 0;

		/* 80h */	virtual void func80h(int, int, int, int) = 0;
		/* 84h */	virtual bool func84h(int, int, int) = 0;
		/* 88h */	virtual void func88h(class ResourceID, void*) = 0;
		/* 8Ch */	virtual void* func8Ch(class ResourceID) = 0;
		/* 90h */	virtual void func90h(int, int, int) = 0;
		/* 94h */	virtual ResourceID func94h(int) = 0;

		///
		/// Set the given application flag.
		/// @param flag The flag to set.
		/// @param bValue The new value of the flag.
		///
		/* 98h */	virtual void SetAppFlag(int flag, bool bValue) = 0;
		/* 9Ch */	virtual int func9Ch(int) = 0;
		/* A0h */	virtual int funcA0h() = 0;
		/* A4h */	virtual int funcA4h() = 0;
		/* A8h */	virtual void funcA8h(int) = 0;
		/* ACh */	virtual void funcACh() = 0;
		/* B0h */	virtual int funcB0h() = 0;

		/* B4h */	virtual void funcB4h(int, int, int) = 0;

		/* B8h */	virtual bool funcB8h(int, const char*) = 0;
		/* BCh */	virtual int funcBCh(int, int) = 0;
		/* C0h */	virtual int funcC0h(int, int) = 0;
		/* C4h */	virtual bool funcC4h(int, int, int) = 0;

		///
		/// Gets the active manager of the Swarm system.
		///
		static ISwarmManager* Get();
	};

	namespace Addresses(ISwarmManager)
	{
		DeclareAddress(Get);
	}
}
