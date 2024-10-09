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

#include <Spore\Simulator\cGameData.h>
#include <Spore\Simulator\cSpatialObject.h>
#include <Spore\Simulator\cBehaviorList.h>
#include <EASTL\vector.h>

#define cGameBundleContainerPtr eastl::intrusive_ptr<Simulator::cGameBundleContainer>
#define cGameBundlePtr eastl::intrusive_ptr<Simulator::cGameBundle>

namespace Simulator
{
	class cGameBundleContainer;

	class cGameBundle
		/* 00h */	: public cGameData
		/* 34h */	, public cSpatialObject
		/* 108h */	, public cBehaviorList
	{
	public:
		static const uint32_t TYPE = 0x4FFCDEDA;
		static const uint32_t NOUN_ID = 0x18C431C;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

	public:
		/* 120h */	int field_120;
		/* 124h */	bool mLoose;
		/* 128h */	cGameBundleContainerPtr mpContainer;
		/* 12Ch */	int mType;
		/* 130h */	int mDisplayType;
		/* 134h */	int mAmountInBundle;  // not initialized
		/* 138h */	bool field_138;
	};
	ASSERT_SIZE(cGameBundle, 0x13C);

	class cGameBundleContainer
	{
	public:
		static const uint32_t TYPE = 0x135B1E8;

		//PLACEHOLDER
		virtual ~cGameBundleContainer();

	public:
		/* 04h */	eastl::vector<cGameBundlePtr> mBundleList;
		/* 18h */	cGameDataPtr mpOwner;
		/* 1Ch */	int mContainerCapacity;
		/* 20h */	int mBundleCapacity;
	};
	ASSERT_SIZE(cGameBundleContainer, 0x24);
}