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
#include <Spore\App\Propertylist.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\App\IMessageManager.h>
#include <Spore\Simulator\ISimulatorSerializable.h>

#define cSpaceInventoryItemPtr intrusive_ptr<Simulator::cSpaceInventoryItem>

namespace Simulator
{
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
		/* 24h */	virtual intrusive_ptr<cSpaceInventoryItem> Duplicate();
		/* 28h */	virtual const char16_t* func28();
		/* 2Ch */	virtual const char16_t* func2C();
		/* 30h */	virtual ResourceKey GetImageID();

		/// Returns the colors that override the icon color states, therefore 8 colors.
		/// Those colors are get from the "spaceToolImageColors" property.
		/* 34h */	virtual bool GetImageColors(size_t& dstCount, ColorRGB*& dst);

		/// Returns the ley of the panel the tool belongs to. 
		/// If this item is of cargo type, it returns the cargo panel key.
		/// OTherwise, it returns the value of the "spaceToolPanelKey" property.
		/* 38h */	virtual ResourceKey GetPanelID();
		/* 3Ch */	virtual bool GetItemCount(size_t& dst);
		/* 40h */	virtual int func40h();
		/* 44h */	virtual bool func44h();
		/* 48h */	virtual bool func48h();
		/* 4Ch */	virtual void ParseProp();

	public:
		/* 10h */	size_t mItemCount;  // 1
		/* 14h */	int mItemType;  // 2
		/* 18h */	unsigned int mItemCost;
		/* 1Ch */	bool mbIsUnique;
		/* 20h */	uint32_t mPoliticalId;  // -1
		/* 24h */	unsigned int mItemPosition;  // -1
		/* 28h */	bool mbIsActive;
		/* 2Ch */	intrusive_ptr<cSpaceInventoryItem> mpCargoSlot;
		/* 30h */	intrusive_ptr<App::PropertyList> mpPropList;
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

	static_assert(sizeof(cSpaceInventoryItem) == 0x7C, "sizeof(cSpaceInventoryItem) != 0x7C");
}