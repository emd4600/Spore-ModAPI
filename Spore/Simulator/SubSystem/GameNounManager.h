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
#include <Spore\Simulator\GameNounIDs.h>
#include <Spore\Simulator\tGameDataVectorT.h>
#include <Spore\Simulator\cCreatureAnimal.h>
#include <Spore\App\IMessageListener.h>
#include <EASTL\hash_map.h>
#include <EASTL\map.h>
#include <EASTL\list.h>

namespace Simulator
{

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


		/// Gets all the game data objects that use the given game noun ID. To be more specific, first a container is created
		/// with the pCreate callback; then 
		template <class T>
		tGameDataVectorT<T>& GetData(ContainerCreateCallback_t<T> pCreate, ContainerClearCallback_t<T> pClear,
			ContainerAddCallback_t<T> pAdd, ContainerFilterCallback_t pFilter, uint32_t nounID)
		{
			return *((tGameDataVectorT<T>*(__thiscall*)(cGameNounManager*, ContainerCreateCallback_t<T>, ContainerClearCallback_t<T>,
				ContainerAddCallback_t<T>, ContainerFilterCallback_t, uint32_t)) (GetMethodAddress(cGameNounManager, GetData)))(
					this, pCreate, pClear, pAdd, pFilter, nounID);
		}


		cCreatureAnimal* GetAvatar();

		void SetAvatar(cCreatureAnimal* pAnimal);

		///
		/// Returns the active Simulator game noun manager. Same as GameNounManager().
		///
		static cGameNounManager* Get();
			
	protected:
		/* 20h */	hash_map<int, int> field_20;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	intrusive_ptr<cCreatureAnimal> mpAvatar;  // cCreatureAnimal player?
		/* 58h */	intrusive_ptr<Object> mpAvatarHerd;  // cHerd
		/* 5Ch */	vector<intrusive_ptr<Object>> mPosseMembers;
		/* 70h */	intrusive_ptr<Object> mpPlayerTribe;
		/* 74h */	intrusive_ptr<Object> mpPlayer;  // cPlayer
		/* 78h */	intrusive_list<cGameData> mNouns;
		/* 80h */	vector<intrusive_ptr<Object>> field_80;  // objects that haven't been updated since last call to UpdateModels?
		/* 94h */	int field_94;
		/* 98h */	map<uint32_t, int> field_98;
		/* B4h */	map<int, int> mPoliticalMap;
		/* D0h */	map<int, intrusive_ptr<Object>> field_D0;
		/* ECh */	map<int, intrusive_ptr<Object>> field_EC;
		/* 108h */	int field_108;
		/* 10Ch */	list<intrusive_ptr<cGameData>> mObjects;
		/* 118h */	int field_118;
	};

	///
	/// Returns the active Simulator game noun manager. Same as cGameNounManager::Get().
	///
	inline cGameNounManager* GameNounManager()
	{
		return cGameNounManager::Get();
	}

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(cGameNounManager) == 0x11C, "sizeof(cGameNounManager) != 11Ch");

	namespace InternalAddressList(cGameNounManager)
	{
		DefineAddress(Get, GetAddress(0xB3D260, 0xB3D3D0, 0xB3D400));
		DefineAddress(CreateInstance, GetAddress(0xB20A90, 0xB20B80, 0xB20BF0));
		DefineAddress(DestroyInstance, GetAddress(0xB22450, NO_ADDRESS, 0xB22560));
		DefineAddress(GetData, GetAddress(0xB21280, 0xB21260, 0xB212D0));

		DefineAddress(UpdateModels, GetAddress(0xB227E0, NO_ADDRESS, 0xB228F0));
		DefineAddress(SetAvatar, GetAddress(0xB1FB90, NO_ADDRESS, 0xB1FCA0));
	}

	/// Gets all the game data objects that are of the specified type. No subclasses allowed.
	/// This only works if the specified class has the NOUN_ID attribute.
	template <class T>
	inline tGameDataVectorT<T>& GetData() {
		return GetData<T>(T::NOUN_ID);
	}


	/// Gets all the game data objects that use the given game noun ID.
	template <class T>
	inline tGameDataVectorT<T>& GetData(uint32_t nounID)
	{
		return cGameNounManager::Get()->GetData<T>(
			[]() {
			return new tGameDataVectorT<T>();
		},
			[](tGameDataVectorT<T>* pVector) {
			pVector->data.clear();
		},
			[](tGameDataVectorT<T>* pVector, cGameData* pObject) {
			// cast or whatever
			pVector->data.push_back(intrusive_ptr<T>(object_cast<T>(pObject)));
		},
			[](cGameData* pObject, uint32_t gameNounID) {
			return pObject->GetNounID() == gameNounID;
		}, nounID);
	}

	template <class T>
	inline T* simulator_new()
	{
		return object_cast<T>(GameNounManager()->CreateInstance(T::NOUN_ID));
	}
}
