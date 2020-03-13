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
#include <Spore\Transform.h>

#define ILightingWorldPtr intrusive_ptr<Graphics::ILightingWorld>

namespace Graphics
{
	///
	/// A lighting world is a space with a specific lighting configuration. Lighting worlds use configuration files
	/// stored in the lighting_properties~ folder, which specify information about the different lights and shadows,
	/// ambient lighting, etc.
	///
	/// The lighting in a world is not affected by and does not interact with other lighting worlds. 
	/// For that reason, lighting worlds are usually paired with IModelWorld instances.
	///
	class ILightingWorld
	{
	public:
		// 0Ch LightingManager
		// 10h related with propertyList
		// 14h configurationID

		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		
		virtual ~ILightingWorld() {};

		/* 0Ch */	virtual int func0Ch(int, int, int, int) = 0;
		/* 10h */	virtual int func10h(int, int) = 0;
		/* 14h */	virtual void func14h(int) = 0;
		/* 18h */	virtual int GetSunDirAndCelStrength(float boundingRadius, const Vector3& position) = 0;
		/* 1Ch */	virtual void func1Ch(float, int, int) = 0;
		// related with sunDirAndCelStrength, called when changing lighting world, setting model invisible or destroying model
		/* 20h */	virtual void func20h(int) = 0;
		// Parameter is cViewer, called every time in ModelWorld::Render
		/* 24h */	virtual void func24h(int) = 0;
		/* 28h */	virtual void func28h(const Transform&) = 0;
		/* 2Ch */	virtual Transform func2Ch() = 0;

		///
		/// Sets this lighting world to use the given configuration. The ID is the instance ID of a .prop
		/// lighting configuration file located in the 0x40200100 (lighting_properties~) folder.
		/// @param configID The instance ID of the configuration file.
		///
		/* 30h */	virtual void SetConfiguration(uint32_t configID) = 0;

		///
		/// Returns the instance ID of the configuration file used to define this lighting world.
		///
		/* 34h */	virtual uint32_t GetConfigurationID() = 0;

		///
		/// Returns the configuration file (as a PropertyList) used to define this lighting world.
		///
		/* 38h */	virtual App::PropertyList* GetPropertyList() = 0;

		/* 3Ch */	virtual void func3Ch(int) = 0;
		/* 40h */	virtual void func40h(int, int) = 0;
	};
}