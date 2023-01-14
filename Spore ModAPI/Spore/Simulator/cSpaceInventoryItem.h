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
#include <Spore\App\PropertyList.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\IMessageManager.h>
#include <Spore\Simulator\SimulatorEnums.h>
#include <Spore\Simulator\ISimulatorSerializable.h>

#define cSpaceInventoryItemPtr eastl::intrusive_ptr<Simulator::cSpaceInventoryItem>

namespace Simulator
{
	/// Represents an item of the space player inventory. This include space tools and cargo.
	class cSpaceInventoryItem 
		: public DefaultRefCounted
		, public App::IUnmanagedMessageListener
		, public ISimulatorSerializable
	{
	public:
		using DefaultRefCounted::AddRef;
		using DefaultRefCounted::Release;

		static const uint32_t TYPE = 0x707459DD;

		/* 10h */	virtual uint32_t GetType();
		/* 14h */	virtual void SetItemID(const ResourceKey& key);
		/* 18h */	virtual const ResourceKey& GetItemID();
		/* 1Ch */	virtual uint32_t GetItemInstanceID();
		/* 20h */	virtual bool IsCargoType();
		/* 24h */	virtual cSpaceInventoryItemPtr Duplicate();
		/* 28h */	virtual const char16_t* GetDescription();
		/* 2Ch */	virtual const char16_t* GetDetailDescription();
		/* 30h */	virtual ResourceKey GetImageID();

		/// Returns the colors that override the icon color states, therefore 8 colors.
		/// Those colors are get from the "spaceToolImageColors" property.
		/// @param dstCount
		/// @param dst
		/// @returns 
		/* 34h */	virtual bool GetImageColors(size_t& dstCount, Math::ColorRGB*& dst);

		/// Returns the key of the panel the tool belongs to. 
		/// If this item is of cargo type, it returns the cargo panel key.
		/// Otherwise, it returns the value of the "spaceToolPanelKey" property.
		/// @returns
		/* 38h */	virtual ResourceKey GetPanelID();

		/* 3Ch */	virtual bool GetItemCount(size_t& dst);
		/* 40h */	virtual int func40h();

		/// Returns true if this item is available in the current planet. 
		/// For example, for animal cargo this is true if the animal species is present in the planet.
		/// @returns
		/* 44h */	virtual bool IsAvailableInCurrentPlanet();

		/* 48h */	virtual bool func48h();
		/* 4Ch */	virtual void ParseProp();


		/// Creates an inventory item for multi-delivery mission objects. It will read a .prop file with
		/// name `instanceID` in the folder `multiDelivery_mision_objects~` (`0x37D494E`).
		/// @param dst
		/// @param itemID
		/// @param instanceIDcddc
		static void CreateMultiDeliveryObject(cSpaceInventoryItem& dst, const ResourceKey& itemID, uint32_t instanceID);

	public:
		/* 10h */	size_t mItemCount;  // 1
		/* 14h */	SpaceInventoryItemType mItemType;  // 2
		/* 18h */	unsigned int mItemCost;
		/* 1Ch */	bool mbIsUnique;
		/* 20h */	uint32_t mPoliticalId;  // -1
		/* 24h */	unsigned int mItemPosition;  // -1
		/* 28h */	bool mbIsActive;
		/* 2Ch */	cSpaceInventoryItemPtr mpCargoSlot;
		/* 30h */	PropertyListPtr mpPropList;
		/* 34h */	LocalizedString mDescription;
		/* 48h */	LocalizedString mDetailDescription;
		/* 5Ch */	ResourceKey mItemID;
		/* 68h */	App::IMessageManager* mpMessageManager;
		/* 6Ch */	App::IMessageListener* mpMessageListener;  // this
		/* 70h */	uint32_t* mpMessageIDs;
		/* 74h */	size_t mNumMessageIDs;
		/* 78h */	int field_78;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	ASSERT_SIZE(cSpaceInventoryItem, 0x7C);

	namespace Addresses(cSpaceInventoryItem)
	{
		DeclareAddress(CreateMultiDeliveryObject);
	}
}