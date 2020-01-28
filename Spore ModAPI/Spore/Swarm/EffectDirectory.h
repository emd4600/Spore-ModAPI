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

#include <Spore\IO\IStream.h>
#include <Spore\Swarm\Components\IEffectComponent.h>
#include <Spore\Swarm\Components\VisualEffect.h>
#include <Spore\ResourceID.h>

#include <EASTL\vector.h>
#include <EASTL\string.h>
#include <EASTL\hash_map.h>
#include <EASTL\intrusive_ptr.h>

#define EffectDirectoryPtr intrusive_ptr<Swarm::EffectDirectory>

using namespace eastl;

namespace Swarm
{
	enum
	{
		kEffectTypeParticles = 0x01,
		kEffectTypeMetaParticles = 0x02,
		kEffectTypeDecal = 0x03,
		kEffectTypeSequence = 0x04,
		kEffectTypeSound = 0x05,
		kEffectTypeShake = 0x06,
		kEffectTypeCamera = 0x07,
		kEffectTypeModel = 0x08,
		kEffectTypeScreen = 0x09,
		kEffectTypeLight = 0x0A,
		kEffectTypeGame = 0x0B,
		kEffectTypeFastParticle = 0x0C,
		kEffectTypeDistribute = 0x0D,
		kEffectTypeRibbon = 0x0E,

		kEffectTypeBrush = 0x20,
		kEffectTypeTerrainScript = 0x21,
		kEffectTypeSkinpaintSettings = 0x22,
		kEffectTypeSkinpaintDistribute = 0x23,

		kEffectTypeGamemodel = 0x25,
		kEffectTypeSkinpaintParticle = 0x26,
		kEffectTypeSkinpaintFlood = 0x27,
		kEffectTypeVolume = 0x28,
		kEffectTypeSplitController = 0x29,
		kEffectTypeTerrainDistribute = 0x2A,
		kEffectTypeCloud = 0x2B,
		kEffectTypeGroundCover = 0x2C,
		kEffectTypeMixEvent = 0x2D,

		kEffectTypeText = 0x2F,
	};

	class IEffectDirectory
	{
	public:
		// I don't know what this class is, but we need to at least have a virtual method.
		virtual void AddRef() = 0;
	};

	///
	/// An EffectDirectory is a file that contains one or multiple effect declarations. They correspond to the .EFFDIR file
	/// format. Effect directories contain all the components used (particles, sounds, models, etc) and the effect declarations
	/// themselves, along with associations that define an ID for each effect.
	///
	class EffectDirectory : public IEffectDirectory, public IVirtual
	{
	public:
		/* 00h */	virtual void AddRef() = 0;
		/* 04h */	virtual void Release() = 0;

		/* 08h */	virtual bool func08h() = 0;
		/* 0Ch */	virtual void func0Ch() = 0;
		/* 10h */	virtual void Reset() = 0;
		/* 14h */	virtual void func14h() = 0;

		// returns the index
		/* 18h */	virtual int AddVisualEffect(Components::VisualEffect* effect) = 0;

		///
		/// Adds the given IEffectComponent to this directory. The component will be stored in a list
		/// of the specified type.
		/// @param type The type of the component, in the enum Swarm::kEffectType... values.
		/// @param pComponent The IEffectComponent to add.
		/// @returns The index of the component in the list of the appropiate type.
		///
		/* 1Ch */	virtual int AddComponent(int type, Components::IEffectComponent* pComponent) = 0;

		///
		/// Gets the IEffectComponent that is in the given index in the list of the specified type.
		/// @param index The index of the component (e.g. the one returned by AddComponent()).
		/// @param type The type of the component, in the enum Swarm::kEffectType... values.
		/// @returns The IEffectComponent at that index.
		///
		/* 20h */	virtual Components::IEffectComponent* GetComponent(int index, int type) = 0;

		///
		/// Adds the given IEffectDescription to this directory. The component will be stored in a list
		/// of the specified type.
		/// @param type The type of the component, in the enum Swarm::kDescType... values.
		/// @param pDescription The IEffectDescription to add.
		/// @returns The index of the component in the list of the appropiate type.
		///
		/* 24h */	virtual int AddDescription(int type, Components::IEffectDescription* pDescription) = 0;
		///
		/// Gets the IEffectDescription that is in the given index in the list of the specified type.
		/// @param index The index of the component (e.g. the one returned by AddDescription()).
		/// @param type The type of the component, in the enum Swarm::kDescType... values.
		/// @returns The IEffectDescription at that index.
		///
		/* 28h */	virtual Components::IEffectDescription* GetDescription(int index, int type) = 0;

		// Get resource names?
		/* 2Ch */	virtual size_t func2Ch(int index, int pDst, int) = 0;

		///
		/// Reads all the effects into this directory from the specified IStream.
		/// @param pInputStream The input IStream where the data will be read.
		/// @returns True if there were no errors.
		///
		/* 30h */	virtual bool Read(IO::IStream* pInputStream) = 0;

		///
		/// Writes all the effects of this directory into the specified IStream.
		/// @param pOutputStream The output IStream where the data will be written.
		/// @returns True if there were no errors.
		///
		/* 34h */	virtual bool Write(IO::IStream* pOutputStream) = 0;

		///
		/// Deleted method, does nothing.
		///
		/* 38h */	virtual bool Compile() = 0;

		///
		/// Tells whether an effect with this name is contained in this directory. If it is, 
		/// the name will be written into the given string.
		/// @param[out] dst The destination string where the name will be written.
		/// @param pName The name of the effect to find.
		/// @returns True if the effect exists, false otherwise.
		///
		/* 3Ch */	virtual bool HasEffectName(string& dst, const char* pName) = 0;

		///
		/// Puts all the effect names contained in this directory into the given vector. Note that not all effects use names;
		/// inf act, most of them use IDs. Optionally, a pattern can be specified to only get certain names. The pattern uses the character 
		/// '?' to allow any character, and '*' to allow any sequence of characters.
		/// @param dst A string vector where the names will be output.
		/// @param pPattern [Optional] The pattern names must match in order to be added to the list.
		///
		/* 40h */	virtual void GetEffectNames(vector<string>& dst, const char* pPattern = nullptr) = 0;

		Components::VisualEffect* GetVisualEffect(size_t index);

		int GetEffectIndex(uint32_t instanceID, uint32_t groupID);

	protected:
		/* 08h */	int mnRefCount;
		/* 0Ch */	vector<vector<intrusive_ptr<Components::IEffectComponent>>> mComponents;
		/* 20h */	vector<vector<intrusive_ptr<Components::IEffectDescription>>> mDescriptions;
		/* 34h */	vector<Components::VisualEffect> mVisualEffects;
		/* 48h */	hash_map<string, size_t> mEffectNames;  // maps a string to the VisualEffect index
		// /* 68h */	hash_map<uint32_t, int> mEffectIDs;  // maps an ID to the VisualEffect index
		/* 68h */	hash_map<ResourceID, size_t> mEffectIDs;  // maps an ID to the VisualEffect index
		/* 88h */	vector<ResourceID> mImports;
	};

	static_assert(sizeof(EffectDirectory) == 0x9C, "sizeof(EffectDirectory) != 9Ch");

	inline Components::VisualEffect* EffectDirectory::GetVisualEffect(size_t index)
	{
		if (index >= mVisualEffects.size()) return nullptr;
		return &mVisualEffects[index];
	}

	inline int EffectDirectory::GetEffectIndex(uint32_t instanceID, uint32_t groupID)
	{
		// The arguments are switched
		auto it = mEffectIDs.find(ResourceID(groupID, instanceID));
		if (it != mEffectIDs.end())
		{
			return it->second;
		}
		else
		{
			return -1;
		}
	}
}