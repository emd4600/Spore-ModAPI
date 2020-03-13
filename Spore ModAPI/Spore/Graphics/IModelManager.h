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

#include <cstdint>

#include <Spore\Object.h>
#include <Spore\Graphics\IModelWorld.h>

#define ModelManager (*Graphics::IModelManager::Get())

#define IModelManagerPtr intrusive_ptr<Graphics::IModelManager>

namespace Graphics
{
	enum class ModelGroups : uint32_t
	{
		DeformHandle = 0x1BA53EA,
		DeformHandleOverdraw = 0x1BA53EB,
		Background = 0x223E8E0,
		Overdraw = 0x22FFF11,
		EffectsMask = 0x23008D4,
		TestEnv = 0x26F3933,
		PartsPaintEnv = 0xFE39DE0,
		Skin = 0xFEB8DF2,
		RotationRing = 0x31390732,
		RotationBall = 0x31390733,
		SocketConnector = 0x4FF4AF74,
		AnimatedCreature = 0x509991E6,
		TestMode = 0x509AA7C9,
		Vertebra = 0x513CDFC1,
		PaletteSkin = 0x71257E8B,
		ExcludeFromPinning = 0x900C6ADD,
		Palette = 0x900C6AE5,
		BallConnector = 0x900C6CDD,
		Rigblock = 0x9138FD8D,
		RigblockEffect = 0x4FE3913,
		GameBackground = 0x64AC354
	};

	///
	/// This manager stores the model worlds in the game; for more info, check the IModelWorld class.
	/// This manager can be used to create new model worlds or get existing ones, which in turn can be used
	/// to render models in the game.
	///
	class IModelManager
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;

		virtual ~IModelManager() {};

		/* 0Ch */	virtual bool Initialize() = 0;
		/* 10h */	virtual bool Dispose() = 0;

		///
		/// Creates a new IModelWorld and stores it in this manager, mapped with the given ID.
		/// @param id The ID the new model world will be mapped to.
		/// @param pName [Optional] The name of the model world. This might be ignored.
		/// @param bEnableBuiltins [Optional] If true, builtin models will be used when a model does not exist.
		///
		/* 14h */	virtual IModelWorld* CreateWorld(uint32_t id, const char* pName = nullptr, bool bEnableBuiltins = false) = 0;

		///
		/// Disposes the model world with the given ID, and removes it from this manager. This method should be paired with the 
		/// CreateWorld() method; call it when the model world won't be used anymore.
		/// @param id The ID the model world was mapped to.
		///
		/* 18h */	virtual void DisposeWorld(uint32_t id) = 0;

		///
		/// Returns the IModelWorld* of this manager mapped to the given ID.
		/// @param id The ID the model world was mapped to.
		///
		/* 1Ch */	virtual IModelWorld* GetWorld(uint32_t id) = 0;

		/* 20h */	virtual Object* func20h() = 0;

		// possible SetActiveWorld?
		/* 24h */	virtual void func24h(Object*) = 0;

		// returns some kind of flags
		/* 28h */	virtual int GetGroupFlag(uint32_t groupID, int=0) = 0;

		// adds the object if not already in the vector
		/* 2Ch */	virtual bool func2Ch(int) = 0;
		// removes the object from the vector
		/* 30h */	virtual bool func30h(int) = 0;

		/* 34h */	virtual void func34h(float, float, int) = 0;
		/* 38h */	virtual void Update(float, float) = 0;


		///
		/// Gets the active model manager.
		///
		static IModelManager* Get();
	};


	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(IModelManager)
	{
		DeclareAddress(Get);
	}
}