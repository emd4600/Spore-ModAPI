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

#include <Spore\Internal.h>
#include <Spore\Object.h>
#include <Spore\MathUtils.h>
#include <Spore\App\PropertyList.h>

using namespace Math;

// off_13EF450 -> part vftable?  // 013EF460?
// 0044070F -> scale part¿
//TODO EVERYTHING! PLACEHOLDER
namespace Editors
{

	class EditorRigblock : public DefaultRefCounted, public Object
	{
	public:

		EditorRigblock() = delete;
		//{
		//	VOID_THISCALL(SelectAddress(0x434820, 0x434B70, 0x434B70), this);
		//}
		virtual ~EditorRigblock()
		{
			//TODO
		}

		/* 0Ch */	intrusive_ptr<App::PropertyList> prop;

		char _padding_10[0x0C];

		// 10h ModelPtr
		// 14h ModelPtr mpModel;
		// 18h ModelWorldPtr mpModelWorld;

		/* 1Ch */	unsigned long instanceID;
		/* 20h */	unsigned long groupID;

		char _padding_24[0x24];

		/* 48h */	Vector3 pos;
		/* 54h */	Vector3 lastPos;  // updated when the part is clicked

		// the same?
		// /* 88h */	Vector3 coords;
		// /* 94h */	Vector3 coords2;

		char _padding_60[0x178];

		/* 1D8h */	float size;
		/* 1DCh */	float size_2;  // again?!
		/* 1E0h */	float minScale;
		/* 1E4h */	float maxScale;
		/* 1E8h */	Vector3 modelDefaultMouseOffset;

		char _padding_1F4[0x24];

		/* 218h */	float modelMinBallConnectorScale;
		/* 21Ch */	float modelMaxBallConnectorScale;
		/* 220h */	float modelSymmetrySnapDelta;
		/* 224h */	int field_224;
		/* 228h */	float modelReplaceSnapDelta;
		/* 22Ch */	float modelSymmetryRotationSnapAngle;

		char _padding_230[0x1C];

		/* 24Ch */	int modelNumberOfSnapAxes;

		char _padding_250[0x16C];

		// /* 33Ch */	EditorRigblock* parent

		/* 3BCh */	unsigned long modelForcePinningType;
		/* 3C0h */	unsigned long modelPinningType;

		char _padding_3C4[0x60];

		// /* 40Ch */	Vector3

		/* 424h */	Vector3 modelPaletteRotation;

		char _padding_430[0x20];

		/* 450h */	float modelBottomEdgeDistanceAdjustment = 0.0f;
		/* 454h */	float modelScale = 1.0f;
		/* 458h */	ResourceKey* modelMinMuscleFile;
		/* 45Ch */	ResourceKey* modelMaxMuscleFile;

		char _padding_460[0x28];

		/* 488h */	float animationTime;

		char _padding_48C[0x158];

		/* 5E4h */	int modelPrice;
		/* 5E8h */	int modelComplexityScore;
		/* 5ECh */	int modelRunTimeBoneCount;
		/* 5F0h */	int modelBakeLevel;
		/* 5F4h */	int field_5F4;
		/* 5F8h */	ResourceKey modelRigBlockType;
		/* 604h */	unsigned long modelShowoffAnimation;
		/* 608h */	unsigned long modelShowoffEffect;

		char _padding_60C[0x7A8];

		// 6CCh pointer to array of MorphHandles (at 8Ch is anim ID)

		/* DB4h */	unsigned long foottype;
		/* DB8h */	unsigned long mouthtype;
		/* DBCh */	unsigned long weapontype;

		char _padding_DC0[0x48];


		//// _ZN14EditorRigblock8SetScaleEfii
		//// not sure, apparently there are more methods
		//void* SetScale(float scale, int arg_4, int arg_8);  // sub_440670

		//void* ParseProp(unsigned long instanceID, unsigned long groupID, int, int, int, int, int, int);  // sub_441590

		//// causes flora editor crash
		//static void* sub_49FF50(EditorRigblock* part, eastl::vector<void*>& dst, bool arg_8);

		//static void __fastcall sub_4490F0(EditorRigblock* _This, void* _Edx, Vector3 pos, bool arg_C);  // move part?


		// 00438D92 -> remove parent?

		// add part? loc_57DA5D
		// sub_754770 -> ModelLoader() ?
		// sub_747CB0 -> Model() ?

		//TODO this doesn't belong here!
		//static long AttachDetour();

		//virtual METHOD_(SelectAddress(0x456F60, 0x54B6C0, 0x54B6C0), Object, int, AddRef);
		//virtual METHOD_(SelectAddress(0x54B590, 0x54B6D0, 0x54B6D0), Object, int, Release);
		//virtual METHOD(SelectAddress(0x435B20, 0x435E70, 0x435E70), Object, void*, Cast, Args(uint32_t typeID), Args(typeID));

	//private:
	//	static void* (*sub_49FF50_ptr)(EditorRigblock* part, eastl::vector<void*>& dst, bool arg_8);
	//	static void(__thiscall*sub_4490F0_ptr)(EditorRigblock* _This, Vector3 pos, bool arg_C);

	//	//TODO rotate part?
	//	static void(__thiscall*sub_44A230_ptr)(EditorRigblock*, Matrix3 rot, int arg_24);
	};

	static_assert(sizeof(EditorRigblock) == 0xE08, "sizeof(EditorRigblock) must be 0xE08!");
}
