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

#include <Spore\Graphics\ILightingWorld.h>
#include <Spore\MathUtils.h>

namespace Graphics
{
	///
	/// This manager handles the lighting configurations in the game. It stores a map of ILightingWorld instances.
	///
	class ILightingManager
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		virtual ~ILightingManager() {};

		/* 0Ch */	virtual bool Initialize() = 0;
		/* 10h */	virtual bool Dispose() = 0;
		/* 14h */	virtual void func14h(int) = 0;

		///
		/// Creates a new ILightingWorld and maps it to the specified ID. The instance ID of the configuration file can 
		/// optionally be specified, to load the lighting configuration.
		/// @param worldID The ID the lighting world will be mapped to.
		/// @param pName [Optional] The name of the world, it might be ignored.
		/// @param configID [Optional] The instance ID of the configuration file of the lighting.
		///
		/* 18h */	virtual ILightingWorld* CreateWorld(uint32_t worldID, const char* pName = nullptr, uint32_t configID = 0) = 0;

		///
		/// Returns the ILightingWorld previously mapped with the given ID, or nullptr if the ID is not mapped.
		/// @param worldID The ID of the world mapped.
		///
		/* 1Ch */	virtual ILightingWorld* GetWorld(uint32_t worldID) = 0;

		///
		/// Disposes the lighting world with the given ID, and removes it from this manager. This method should be paired with the 
		/// CreateWorld() method; call it when the model world won't be used anymore.
		/// @param worldID The ID the lighting world was mapped to.
		///
		/* 20h */	virtual void DisposeWorld(uint32_t worldID) = 0;

		/* 24h */	virtual Math::Vector3 func24h() = 0;
		/* 28h */	virtual void func28h(const Math::Vector3&, int, int) = 0;
		/* 2Ch */	virtual void func2Ch(int) = 0;

		///
		/// Returns the active lighting manager. Same as LightingManager().
		///
		static ILightingManager* Get();
	};

	///
	/// Returns the active lighting manager. Same as ILightingManager::Get().
	///
	inline ILightingManager* LightingManager()
	{
		return ILightingManager::Get();
	}

	namespace Addresses(ILightingManager)
	{
		DeclareAddress(Get, SelectAddress(0x67DEB0, 0x67DD50, 0x67DD50));
	}
}