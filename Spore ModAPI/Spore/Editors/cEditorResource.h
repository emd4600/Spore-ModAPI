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

using namespace Math;
using namespace eastl;

namespace Editors
{
	class cEditorResource : public Resource::ResourceObject
	{
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
			/* 20h */	ColorRGB mSkinColor1;
			/* 2Ch */	ColorRGB mSkinColor2;
			/* 38h */	ColorRGB mSkinColor3;
		};

		cEditorResource();

	public:
		/* 18h */	Properties mProperties;

		/* 98h */	vector<void*> field_98;
	};

}