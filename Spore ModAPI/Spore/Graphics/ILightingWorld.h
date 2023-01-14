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
#include <Spore\App\cViewer.h>
#include <Spore\Transform.h>

#define ILightingWorldPtr eastl::intrusive_ptr<Graphics::ILightingWorld>

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
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;
		
		virtual ~ILightingWorld() {};

		/* 0Ch */	virtual int AddLight(const Vector3& position, const ColorRGB& color, float, float) = 0;

		/* 10h */	virtual void UpdateLightPosition(int index, const Vector3&) = 0;

		/* 14h */	virtual void RemoveLight(int index) = 0;

		/* 18h */	virtual void* CreateLightingInfo(float boundingRadius, const Vector3& position) = 0;

		/* 1Ch */	virtual void UpdateLightingInfo(float, const Vector3&, void* pLightingInfo) = 0;

		// related with sunDirAndCelStrength, called when changing lighting world, setting model invisible or destroying model
		//TODO param is cLightingInfo*
		/* 20h */	virtual void DestroyLightingInfo(void* pLightingInfo) = 0;

		// Called every time in ModelWorld::Render
		/* 24h */	virtual void ApplyGlobalState(App::cViewer* viewer) = 0;

		/// Sets the transform for this lighting world.
		/// @param transform
		/* 28h */	virtual void SetTransform(const Transform& transform) = 0;

		/* 2Ch */	virtual Transform GetTransform() = 0;

		///
		/// Sets this lighting world to use the given configuration. The ID is the instance ID of a .prop
		/// lighting configuration file located in the 0x40200100 (lighting_properties~) folder.
		/// @param configID The instance ID of the configuration file.
		///
		/* 30h */	virtual void SetLightingState(uint32_t configID) = 0;

		///
		/// Returns the instance ID of the configuration file used to define this lighting world.
		///
		/* 34h */	virtual uint32_t GetLightingState() = 0;

		///
		/// Returns the configuration file (as a App::PropertyList) used to define this lighting world.
		///
		/* 38h */	virtual App::PropertyList* GetLightingStateConfig() = 0;

		// parameter is Swarm::cIDecalManager>
		/* 3Ch */	virtual void SetLightDecalManager(Object*) = 0;

		// parameter is tLightingWorldType
		/* 40h */	virtual void SetWorldType(int worldType, const BoundingBox& bbox) = 0;

	private:
		// 0Ch LightingManager
		// 10h related with propertyList
		// 14h configurationID

		// 40h ColorRGB mAmbientColor;
		// 4Ch eastl::vector<Light*> mLights;
		// 60h Light*
		// 64h Transform
		
		// 260h sunDirAndCelStrength, 261 is whether it's enabled

		// A0h Transform

		// D4h Vector3 mViewPos;
	};
}