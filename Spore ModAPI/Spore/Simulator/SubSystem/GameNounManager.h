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

#include <Spore\Object.h>
#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\SubSystem\cStrategy.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Simulator\tGameDataVectorT.h>
#include <Spore\Simulator\cCreatureAnimal.h>
#include <Spore\Simulator\cTribe.h>
#include <Spore\Simulator\cHerd.h>
#include <Spore\App\IMessageListener.h>
#include <EASTL\hash_map.h>
#include <EASTL\map.h>
#include <EASTL\list.h>

/// Access the active Simulator game noun manager.
#define GameNounManager (*Simulator::cGameNounManager::Get())

namespace Simulator
{
#ifndef SDK_TO_GHIDRA
	/// Creates the vector game data container.
	template <class T>
	using ContainerCreateCallback_t = tGameDataVectorT<T>*(*)();
	/// Clears the content of the vector.
	template <class T>
	using ContainerClearCallback_t = void(*)(tGameDataVectorT<T>* pVector);
	/// This method must add the game data object into the vector. Only the objects that have passed the
	/// filter function are used in this callback.
	template <class T>
	using ContainerAddCallback_t = void(*)(tGameDataVectorT<T>* pVector, cGameData* pObject);
	/// Used to decide which game objects go to the vector and which do not. It receives the object to
	/// evaluate and the game noun ID passed to the GetData function.
	using ContainerFilterCallback_t = bool(*)(cGameData* pObject, uint32_t gameNounID);
#endif

	/// The class that manages game objects, known in Spore code as 'nouns'. Use this class to create or destroy
	/// instances of Simulator classes. To create a Simulator object, use simulator_new() (which calls this class).
	/// This class is also used to obtain all active instances of a certain object, using Simulator::GetData().
	/// Use `GameNounManager.GetAvatar()` to obtain the player creature.
	/// 
	/// This is a singleton class, so use GameNounManager to access it.
	class cGameNounManager
		: public App::IMessageListener
		, public cStrategy
	{
	public:
		/// Creates an instance of a simulator object of the given type. The noun ID is one of
		/// the values in the Simulator::GameNounIDs enum.
		/// @param nounID The ID of the object to create.
		/// @returns The created object, as a Simulator::cGameData*.
		cGameData* CreateInstance(uint32_t nounID);

		void DestroyInstance(cGameData* pInstance);

		void UpdateModels();


#ifndef SDK_TO_GHIDRA
		/// Gets all the game data objects that use the given game noun ID. To be more specific, first a container is created
		/// with the pCreate callback; then 
		template <class T>
		tGameDataVectorT<T>& GetData(ContainerCreateCallback_t<T> pCreate, ContainerClearCallback_t<T> pClear,
			ContainerAddCallback_t<T> pAdd, ContainerFilterCallback_t pFilter, uint32_t nounID)
		{
			return *((tGameDataVectorT<T>*(__thiscall*)(cGameNounManager*, ContainerCreateCallback_t<T>, ContainerClearCallback_t<T>,
				ContainerAddCallback_t<T>, ContainerFilterCallback_t, uint32_t)) (GetAddress(cGameNounManager, GetData)))(
					this, pCreate, pClear, pAdd, pFilter, nounID);
		}
#endif

		cCreatureAnimal* GetAvatar();

		void SetAvatar(cCreatureAnimal* pAnimal);

		cTribe* GetPlayerTribe();

		/// Returns the active Simulator game noun manager.
		static cGameNounManager* Get();
			
	public:
		/* 20h */	eastl::hash_map<int, int> field_20;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	cCreatureAnimalPtr mpAvatar;
		/* 58h */	cHerdPtr mpAvatarHerd;
		/* 5Ch */	eastl::vector<cCreatureAnimalPtr> mPosseMembers;
		/* 70h */	cTribePtr mpPlayerTribe;
		/* 74h */	ObjectPtr mpPlayer;  // cPlayer
		/* 78h */	eastl::intrusive_list<cGameData> mNouns;
		/* 80h */	eastl::vector<ObjectPtr> field_80;  // objects that haven't been updated since last call to UpdateModels?
		/* 94h */	int field_94;
		/* 98h */	eastl::map<uint32_t, tGameDataVectorT<cGameData>> mNounMap;
		/* B4h */	eastl::map<int, int> mPoliticalMap;
		/* D0h */	eastl::map<int, ObjectPtr> field_D0;
		/* ECh */	eastl::map<int, ObjectPtr> field_EC;
		/* 108h */	int field_108;
		/* 10Ch */	eastl::list<cGameDataPtr> mObjects;
		/* 118h */	int field_118;
	};
	ASSERT_SIZE(cGameNounManager, 0x11C);

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(cGameNounManager)
	{
		DeclareAddress(Get);
		DeclareAddress(CreateInstance);
		DeclareAddress(DestroyInstance);
		DeclareAddress(GetData);

		DeclareAddress(UpdateModels);
		DeclareAddress(SetAvatar);
	}

#ifndef SDK_TO_GHIDRA
	/// Gets all the game data objects that use the given game noun ID.
	/// All the found objects will be casted to the specified type.
	template <class T>
	inline tGameDataVectorT<T>& GetData(uint32_t nounID)
	{
		return GameNounManager.GetData<T>(
			[]() {
			return new tGameDataVectorT<T>();
		},
			[](tGameDataVectorT<T>* pVector) {
			pVector->data.clear();
		},
			[](tGameDataVectorT<T>* pVector, cGameData* pObject) {
			pVector->data.push_back(intrusive_ptr<T>(object_cast<T>(pObject)));
		},
			[](cGameData* pObject, uint32_t gameNounID) {
			return pObject->GetNounID() == gameNounID;
		}, nounID);
	}

	/// Gets all the game data objects that are of the specified type.
	/// Only classes that define a `NOUN_ID` can be used here.
	/// All the found objects will be casted to the specified type.
	template <class T>
	inline tGameDataVectorT<T>& GetData() {
		return GetData<T>(T::NOUN_ID);
	}

	/// Gets all the game data objects that can be casted to the specified type.
	/// You can use this with base classes that aren't nouns to use all the objects of subclasses;
	/// for example you can use it with cCombatant or cCreatureBase.
	/// Only classes that define a `TYPE` can be used here.
	/// All the found objects will be casted to the specified type.
	template <class T>
	inline tGameDataVectorT<T>& GetDataByCast()
	{
		return GameNounManager.GetData<T>(
			[]() {
			return new tGameDataVectorT<T>();
		},
			[](tGameDataVectorT<T>* pVector) {
			pVector->data.clear();
		},
			[](tGameDataVectorT<T>* pVector, cGameData* pObject) {
			pVector->data.push_back(intrusive_ptr<T>(object_cast<T>(pObject)));
		},
			[](cGameData* pObject, uint32_t gameNounID) {
			return pObject->Cast(T::TYPE) != nullptr;
		}, T::TYPE);
	}
#endif
}

template <class T>
inline T* simulator_new()
{
	return object_cast<T>(GameNounManager.CreateInstance(T::NOUN_ID));
}
