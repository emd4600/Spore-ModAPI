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

#include <Spore\MathUtils.h>
#include <Spore\LocalizedString.h>
#include <Spore\Resource\ResourceObject.h>
#include <Spore\App\PropertyList.h>
#include <Spore\Simulator\cScenarioPosseMember.h>
#include <Spore\Simulator\cScenarioClass.h>
#include <Spore\Simulator\cScenarioMarker.h>
#include <Spore\Simulator\cScenarioAct.h>
#include <EASTL\vector.h>
#include <EASTL\vector_map.h>
#include <EASTL\vector_multimap.h>

#define cScenarioResourcePtr eastl::intrusive_ptr<Simulator::cScenarioResource>

namespace Simulator
{
	class cScenarioResource 
		: public Resource::ResourceObject
	{
	public:
		static const uint32_t TYPE = 0xE742574A;

		/// Reads a `0x366A930D` type file, which contains the planet prop file and the adventure data itself.
		/// @param pStream
		/// @returns
		bool Read(IO::IStream* pStream);

		/// Writes a `0x366A930D` type file, which contains the planet prop file and the adventure data itself.
		/// @param pStream
		/// @returns
		bool Write(IO::IStream* pStream);

	public:
		/* 14h */	int field_14;
		/* 18h */	App::PropertyList mpPropList;
		/* 50h */	float mfWaterScoreDEPRECATED;
		/* 54h */	float mfAtmosphereScoreDEPRECATED;
		/* 58h */	float mfTemperatureScoreDEPRECATED;
		/* 5Ch */	bool mbIsTimeLockedDEPRECATED;
		/* 60h */	float mTimeElapsedDEPRECATED;
		/* 64h */	bool mbCustomScreenshotThumbnailDEPRECATED;
		/* 68h */	uint32_t mScreenshotTypes[4];
		/* 78h */	uint32_t mType;  // 0x20790816
		/* 7Ch */	cScenarioString mIntroText;
		/* B8h */	cScenarioString mWinText;
		/* F4h */	cScenarioString mLoseText;
		/* 130h */	cScenarioAsset mAvatarAsset;
		/* 150h */	Vector3 mAvatarPosition;
		/* 15Ch */	Quaternion mAvatarOrientation;
		/* 16Ch */	float mAvatarScale;
		/* 170h */	float mAvatarHealthMultiplier;
		/* 174h */	bool mbAvatarIsInvulnerable;
		/* 175h */	bool mbAvatarLocked;
		/* 178h */	eastl::vector<cScenarioPosseMember> mInitialPosseMembers;
		/* 190h */	cScenarioPosseMember mInitialPosseMembers_[3];
		/* 238h */	int mNumAllowedPosseMembers;
		/* 23Ch */	eastl::fixed_vector<cScenarioAct, 8> mActs;
		/* 2BF4h */	eastl::vector_map<int, cScenarioClass> mClasses;
		/* 2C0Ch */	int mClassIDCounter;  // 1024
		/* 2C10h */	eastl::vector_map<int, cScenarioMarker> mMarkers;
		/* 2C28h */	int field_2C28; 
		/* 2C2Ch */	bool mbIsMission;
		/* 2C2Dh */	bool field_2C2D;  // true
		/* 2C30h */	Vector3 mCameraTarget;
		/* 2C3Ch */	Quaternion mCameraOrientation;
		/* 2C4Ch */	float mfCameraDistance;
		/* 2C50h */	int mMarkerPositioningVersion;
		/* 2C54h */	eastl::vector<uint32_t> mUsedAppPackIds;
		/* 2C6Ch */	eastl::vector<cScenarioClass> mClassesOld;
		/* 2C80h */	eastl::vector<ResourceKey> mInitialPosseMemberKeysDEPRECATED;
		/* 2C94h */	ResourceKey mAvatarAssetKeyDEPRECATED;
		/* 2CA0h */	uint64_t mAvatarServerIDDEPRECATED;
		/* 2CA8h */	int mVersion;  // 0x11
	};
	ASSERT_SIZE(cScenarioResource, 0x2CB0);

	namespace Addresses(cScenarioResource)
	{
		DeclareAddress(Read);  // 0xF2FDD0, 0xF2FC40
		DeclareAddress(Write);  // 0xF261F0, 0xF25E00
	}
}