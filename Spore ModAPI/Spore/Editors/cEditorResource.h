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

#include <Spore\Resource\ResourceObject.h>
#include <Spore\MathUtils.h>
#include <EASTL\vector.h>

#define cEditorResourcePtr eastl::intrusive_ptr<Editors::cEditorResource>

namespace Editors
{
	struct cEditorResourceBlock
	{
		/* 00h */	uint32_t groupID;
		/* 04h */	uint32_t instanceID;
		/* 08h */	int parentIndex;
		/* 0Ch */	int symmetricIndex;
		/* 10h */	float scale;
		/* 14h */	Math::Vector3 position;
		/* 20h */	Math::Vector3 triangleDirection;
		/* 2Ch */	Math::Vector3 trianglePickOrigin;
		/* 38h */	Math::Matrix3 orientation;
		/* 5Ch */	Math::Matrix3 userOrientation;
		/* 80h */	bool snapped;
		/* 81h */	bool isAsymmetric;
		/// If 3, not limb
		/* 84h */	int limbType; 
		/* 88h */	float muscleScale;
		/* 8Ch */	float baseMuscleScale;
		/* 90h */	int handlesCount;
		/* 94h */	float handleWeights[8];
		/* B4h */	uint32_t handleChannels[8];
		/* D4h */	int paintListCount;
		/* D8h */	int paintRegions[8];
		/* F8h */	uint32_t paintIDs[8];
		/* 118h */	Math::ColorRGB paintColors1[8];
		/* 178h */	Math::ColorRGB paintColors2[8];
	};
	ASSERT_SIZE(cEditorResourceBlock, 0x1d8);

	/// Resource of a saved creation, represents a `.crt`, `.bld`, `.vcl`, etc file.
	/// This can be used in an editor by loading it into an EditorModel.
	class cEditorResource 
		: public Resource::ResourceObject
	{
	public:
		struct Properties
		{
			/* 00h */	uint32_t mModelType;
			/* 04h */	int mZCorpScore;
			/* 08h */	uint32_t mSkinEffectID1;
			/* 0Ch */	uint32_t mSkinEffectID2;
			/* 10h */	uint32_t mSkinEffectID3;
			/* 14h */	unsigned int mSkinEffectSeed1;
			/* 18h */	unsigned int mSkinEffectSeed2;
			/* 1Ch */	unsigned int mSkinEffectSeed3;
			/* 20h */	Math::ColorRGB mSkinColor1;
			/* 2Ch */	Math::ColorRGB mSkinColor2;
			/* 38h */	Math::ColorRGB mSkinColor3;
		};
		ASSERT_SIZE(Properties, 0x44);

		static const uint32_t TYPE = 0x3C609F8;

		virtual void* Cast(uint32_t type) const override;

		cEditorResource();
		~cEditorResource();

	public:
		/* 18h */	Properties mProperties;
		/* 5Ch */	char padding_5C[0x98 - 0x5C];
		/* 98h */	eastl::vector<cEditorResourceBlock> mBlocks;
	};

}