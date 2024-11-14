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
#include <Spore\Clock.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\App\PropertyList.h>
#include <Spore\Editors\EditorBaseHandle.h>
#include <EASTL\bitset.h>
#include <EASTL\map.h>
#include <EASTL\fixed_vector.h>
#include <EASTL\fixed_string.h>

#define EditorRigblockPtr eastl::intrusive_ptr<Editors::EditorRigblock>

// off_13EF450 -> part vftable?  // 013EF460?
// 0044070F -> scale part¿
//TODO EVERYTHING! PLACEHOLDER
namespace Editors
{
	class EditorRigblock;
	class EditorModel;

	struct EditorRigblockCapability
	{
		/// Property ID used to check the capability, such as `modelCapabilityAdventurerMissile`
		/* 00h */	uint32_t mPropertyID;
		/// True if the level can be changed with a handle, like with some adventurer parts
		/* 04h */	bool mIsVariableLevel;
		/* 08h */	int mCapabilityLevel;
		/* 0Ch */	int mCapabilityLevel2;
		/* 10h */	int field_10;
	};
	ASSERT_SIZE(EditorRigblockCapability, 0x14);

	struct EditorRigblockPaint
	{
		/* 00h */	uint32_t mPaintID; // ID of the skinPaint_script~ entry
		/* 04h */	ColorRGB mPaintColor1;
		/* 10h */	ColorRGB mPaintColor2;
	};
	ASSERT_SIZE(EditorRigblockPaint, 0x1C);

	struct UnkEditorRigblockStruct1
	{
		/* 00h */	int field_0;
		/* 04h */	float field_4;
		/* 08h */	float field_8;
		/* 0Ch */	float field_C;  // 0.1
		/* 10h */	bool field_10;
		/* 11h */	bool field_11;
		/* 14h */	int field_14;
		/* 18h */	char padding_18[0x10];
		/* 28h */	bool field_28;
		/* 29h */	bool field_29;
		/* 2Ch */	EditorRigblock* field_2C;
		/* 30h */	int field_30;
		/* 34h */	int mIndex;
	};
	ASSERT_SIZE(UnkEditorRigblockStruct1, 0x38);

	//TODO related with display? check SetShadedDisplay()
	struct UnkEditorRigblockStruct2
	{
		/* 00h */	bool field_0;
		/* 01h */	bool field_1;
		/* 04h */	int field_4;
	};
	ASSERT_SIZE(UnkEditorRigblockStruct2, 0x8);

	enum EditorRigblockBoolAttributes
	{
		kEditorRigblockModelOrientToSurfaces = 0,

		kEditorRigblockModelOrientWhenSnapped = 4,
		kEditorRigblockModelUseDummyBlocks = 5,

		kEditorRigblockModelIsVertebra = 7,
		kEditorRigblockModelIsPlantRoot = 8,
		kEditorRigblockModelOverrideBounds = 9,
		kEditorRigblockModelUseSkin = 0xA,
		kEditorRigblockModelHasSocketAndBallConnector = 0xA,  //???? TODO maybe has morph handles? check when sub_43C190 is called

		kEditorRigblockIsSnapped = 0xC,
		kEditorRigblockHasLeftModel = 0xD,

		kEditorRigblockModelRemainUpright = 0x11,
		kEditorRigblockModelMoveBottomEdgeToSurface = 0x12,
		kEditorRigblockModelPointForward = 0x13,
		kEditorRigblockModelIsNullBlock = 0x14,
		kEditorRigblockModelUseHullForBBox = 0x15,
		kEditorRigblockModelHasStayAbove = 0x16,
		kEditorRigblockModelHasSnapDownTo = 0x17,
		kEditorRigblockModelHideDeformHandles = 0x18,
		kEditorRigblockModelHideRotationHandles = 0x19,
		kEditorRigblockModelHasAlignLateralWith = 0x1A,
		kEditorRigblockModelHasAlignHeightWith = 0x1B,
		kEditorRigblockModelSnapToParentCenter = 0x1C,
		kEditorRigblockModelSnapToParentSnapVectors = 0x1D,
		kEditorRigblockModelSnapToCenterOfEditor = 0x1E,
		kEditorRigblockModelHasBallConnector = 0x1F,
		kEditorRigblockModelHasSocketConnector = 0x20,
		kEditorRigblockModelCellAllowOnTopOfBody = 0x21,
		kEditorRigblockModelPreferToBeOnPlaneOfSymmetry = 0x22,
		kEditorRigblockModelCanBeParentless = 0x23,
		kEditorRigblockModelBoundsCheckOnlyForDelete = 0x24,

		kEditorRigblockModelHasRotationBallHandle = 0x26,
		kEditorRigblockModelHasEffectsBone = 0x27,
		kEditorRigblockModelActLikeFinOnPlaneOfSymmetry = 0x28,
		kEditorRigblockModelWarpCursorToPinPoint = 0x29,

		kEditorRigblockModelActsLikeGrasper = 0x2C,
		kEditorRigblockModelActsLikeFoot = 0x2D,
		kEditorRigblockModelUseHullForPicking = 0x2E,
		kEditorRigblockModelHasForcePinningAgainstType = 0x2F,
		kEditorRigblockModelAllowAsymmetricalRotationOnPlaneOfSymmetry = 0x30,
		kEditorRigblockModelCircularTopAlignment = 0x31,
		kEditorRigblockModelRemainUprightOnTop = 0x32,
		kEditorRigblockModelIsAllowedOutOfBounds = 0x33,
		kEditorRigblockModelDoNotFlipBasedOnSurfaceNormalOnPlaneOfSymmetry = 0x34,
		kEditorRigblockModelHasAlignXYWith = 0x35,
		kEditorRigblockModelHas2002C980Bone = 0x36,
		kEditorRigblockModelAllowTopBehaviors = 0x37,
		kEditorRigblockModelCellApplyBehaviorToUserRotation = 0x38,
		kEditorRigblockModelIsAsymmetric = 0x39,

		kEditorRigblockModelStartAsymmetric = 0x3B,
	};

	/// Represents a "part" (or rigblock) in an editor. Rigblocks are any of the objects in the editor the player can
	/// interact with, including spines. The rigblocks of the current creation are stored in the EditorModel class.
	class EditorRigblock 
		: public DefaultRefCounted
		, public Object
	{
	public:
		static const uint32_t TYPE = 0xEFD66F0B;

		using DefaultRefCounted::AddRef;
		using DefaultRefCounted::Release;

		virtual ~EditorRigblock() = 0;

		/// For build mode only, sets whether the rigblock is shown with a bit of shading
		/// (used when hovering over rigblocks).
		/// @param isShaded
		void SetShadedDisplay(bool isShaded);

		//// _ZN14EditorRigblock8SetScaleEfii
		//// not sure, apparently there are more methods
		//void* SetScale(float scale, int arg_4, int arg_8);  // sub_440670

		//void* ParseProp(unsigned long instanceID, unsigned long groupID, IModelWorld*, int, int, int, int, int);  // sub_441590

		//// causes flora editor crash
		//static void* sub_49FF50(EditorRigblock* part, eastl::vector<void*>& dst, bool arg_8);

		//static void __fastcall sub_4490F0(EditorRigblock* _This, void* _Edx, Vector3 pos, bool arg_C);  // move part?


		// 00438D92 -> remove parent?

		// add part? loc_57DA5D
		// sub_754770 -> ModelLoader() ?
		// sub_747CB0 -> Model() ?

		//TODO this doesn't belong here!
		//static long AttachDetour();

		//virtual METHOD_(SelectAddress(0x456F60, 0x54B6C0), Object, int, AddRef);
		//virtual METHOD_(SelectAddress(0x54B590, 0x54B6D0), Object, int, Release);
		//virtual METHOD(SelectAddress(0x435B20, 0x435E70), Object, void*, Cast, Args(uint32_t typeID), Args(typeID));

	//private:
	//	static void* (*sub_49FF50_ptr)(EditorRigblock* part, eastl::vector<void*>& dst, bool arg_8);
	//	static void(__thiscall*sub_4490F0_ptr)(EditorRigblock* _This, Vector3 pos, bool arg_C);

	//	//TODO rotate part?
	//	static void(__thiscall*sub_44A230_ptr)(EditorRigblock*, Matrix3 rot, int arg_24);

	public:
		/* 0Ch */	PropertyListPtr mpPropList;
		/* 10h */	ModelPtr mpModel;
		/* 14h */	ModelPtr field_14;
		/* 18h */	IModelWorldPtr mpModelWorld;
		// 10h ModelPtr
		// 14h ModelPtr mpModel;
		// 18h ModelWorldPtr mpModelWorld;
		/* 1Ch */	uint32_t mInstanceID;
		/* 20h */	uint32_t mGroupID;
		/// Property `0xE305AAFB`
		/* 24h */	int field_24;
		/* 28h */	EditorModel* mpEditorModel;
		/* 2Ch */	int field_2C;
		/* 30h */	float field_30;
		/* 34h */	bool field_34;  // true
		/* 38h */	UnkEditorRigblockStruct2 field_38;
		/* 40h */	UnkEditorRigblockStruct2 field_40;
		/* 48h */	Vector3 mPosition;
		/* 54h */	Vector3 lastPos;  // updated when the part is clicked
		/// Combination of mUserOrientation and mOrientation
		/* 60h */	Matrix3 mTotalOrientation;
		/* 84h */	Matrix3 field_84;
		/* A8h */	Matrix3 mOrientation;
		/* CCh */	Matrix3 field_CC;
		/* F0h */	Matrix3 mUserOrientation;
		/* 114h */	Matrix3 field_114;
		/* 138h */	Vector3 field_138; // position relative to parent?
		/* 144h */	Vector3 field_144;
		/* 150h */	int field_150;  // -2
		/* 154h */	EditorBaseHandlePtr mAxisHandles[3];  //TODO  sub_483CE0
		/* 160h */	EditorBaseHandlePtr mpRotationBallHandle;  //TODO a handle, sub_482F30
		/* 164h */	int field_164;
		/* 168h */	int field_168;
		/* 16Ch */	float field_16C;
		/* 170h */	Clock field_170;
		/* 188h */	int field_188;
		/* 18Ch */	int field_18C;
		/* 190h */	int field_190;
		/* 194h */	int field_194;  // not initialized
		/* 198h */	int field_198;  // not initialized
		/* 19Ch */	int field_19C;  // not initialized
		/* 1A0h */	bool field_1A0;
		/* 1A4h */	int field_1A4;
		/* 1A8h */	bool field_1A8;
		/* 1A9h */	bool field_1A9;
		/* 1ACh */	int field_1AC;  // not initialized
		/* 1B0h */	int field_1B0;  // not initialized
		/* 1B4h */	int mDeformBoneEndJointIndex;  // -1
		/* 1B8h */	int mDeformBoneBaseJointIndex;  // -1
		/* 1BCh */	int mDeformBoneMiddleIndex;  // -1
		/* 1C0h */	int field_1C0;  // -2
		/* 1C4h */	int field_1C4;  // 1
		/* 1C8h */	int field_1C8;  // 1
		/* 1CCh */	int mLimbType;  // 3, sub_44F2B0
		/* 1D0h */	float mMuscleScale;  // 0.5
		/* 1D4h */	float mBaseMuscleScale;  // 1.0
		/* 1D8h */	float size;  // 1.0
		/* 1DCh */	float size_2;  // 1.0  // again?!
		/* 1E0h */	float mModelMinScale;
		/* 1E4h */	float mModelMaxScale;
		/* 1E8h */	Vector3 mModelDefaultMouseOffset;
		/* 1F4h */	Matrix3 mModelEditorInitialRotation;
		/* 218h */	float mModelMinBallConnectorScale;  // 0.5
		/* 21Ch */	float mModelMaxBallConnectorScale;  // 2.0
		/* 220h */	float mModelSymmetrySnapDelta;
		/* 224h */	float field_224;
		/* 228h */	float mModelReplaceSnapDelta;  // 0.4
		/* 22Ch */	float mModelSymmetryRotationSnapAngle;  // 0.5
		/* 230h */	bool field_230;  // true
		/* 234h */	eastl::vector<int> field_234;
		/* 248h */	int mModelNumberOfSnapAxes;  // -1
		/* 24Ch */	Transform mEffectsBoneTransform1;
		/* 284h */	Transform mEffectsBoneTransform2;
		/// Index to the model bone named `effecs`
		/* 2BCh */	int mEffectsBoneIndex;  // not initialized
		/* 2C0h */	Transform mCSnapBoneTransform1;
		/* 2F8h */	Transform mCSnapBoneTransform2;
		/// Index to the model bone named `csnap`
		/* 330h */	int mCSnapBoneIndex;  // not initialized
		/* 334h */	int field_334;  // not initialized
		/* 338h */	int field_338;  // not initialized
		/* 33Ch */	EditorRigblockPtr mpParent;
		/* 340h */	eastl::fixed_vector<EditorRigblockPtr, 8> mChildren;
		/* 378h */	int field_378;
		/* 37Ch */	char _padding_37C[0x3A0 - 0x37C];  // not initialized
		/* 3A0h */	Vector3 mTriangleDirection;
		/* 3ACh */	Vector3 mTrianglePickOrigin;
		/* 3B8h */	int field_3B8;  // not initialized
		/// 2 for `PinningPhysics`, 4 for `PinningGeometry`
		/* 3BCh */	int mModelForcePinningType;  // not initialized
		/* 3C0h */	uint32_t mModelPinningTypeGroup;  // not initialized
		/* 3C4h */	int field_3C4;  // not initialized
		/// True if pinning type instanceID is `0x17CFD48F`
		/* 3C8h */	bool field_3C8;  // not initialized
		/* 3C9h */	bool field_3C9;
		/* 3CCh */	int field_3CC;  // not initialized
		/* 3D0h */	int field_3D0;  // not initialized
		/* 3D4h */	int field_3D4;  // not initialized
		/* 3D8h */	int field_3D8;  // -1
		/* 3DCh */	int field_3DC;
		/* 3E0h */	EditorRigblockPtr mpSymmetricRigblock;
		/* 3E4h */	EditorRigblockPtr mpAsymmetricRigblock;
		/* 3E8h */	bool field_3E8;
		/* 3ECh */	EditorBaseHandlePtr mpBallConnectorHandle;  //TODO BallConnectorHandle type, sub_47F410
		/* 3F0h */	ModelPtr mpSocketConnectorModel;
		/* 3F4h */	Vector3 mModelMinSocketConnectorOffset;
		/* 400h */	Vector3 mModelMaxSocketConnectorOffset;
		/* 40Ch */	Vector3 mSocketConnectorOffset;
		/* 418h */	Vector3 mModelRotationBallHandleOffset;
		/* 424h */	Vector3 mModelPaletteRotation;
		/* 430h */	int field_430;  // -1
		/* 434h */	int field_434;
		/* 438h */	bool field_438;
		/* 43Ch */	int field_43C;
		/* 440h */	float field_440;
		/* 444h */	float field_444;
		/* 448h */	int field_448;  // not initialized
		/* 44Ch */	int field_44C;  // not initialized
		/* 450h */	float mModelBottomEdgeDistanceAdjustment;
		/* 454h */	float mModelScale;  // not initialized
		/* 458h */	ResourceKey* mModelMinMuscleFile;
		/* 45Ch */	ResourceKey* mModelMaxMuscleFile;
		/// Name of the sound played when scaling this rigblock, default is `creature_size`
		/* 460h */	eastl::fixed_string<char, 32> mModelSoundScale;
		/// Name of the sound played when rotating this rigblock, default is `creature_rotate`
		/* 494h */	eastl::fixed_string<char, 32> mModelSoundRotation;
		/* 4C8h */	eastl::fixed_vector<eastl::pair<uint32_t, EditorRigblockPaint>, 8> mPaints;
		/* 5E0h */	bool field_5E0;  // not initialized, part of field_4C8
		/* 5E4h */	int mModelPrice;
		/* 5E8h */	int mModelComplexityScore;
		/* 5ECh */	int mModelRunTimeBoneCount;
		/* 5F0h */	int mModelBakeLevel;
		/* 5F4h */	float field_5F4;
		/* 5F8h */	ResourceKey mModelRigBlockType;
		/* 604h */	uint32_t mModelShowoffAnimation;  // not initialized
		/* 608h */	uint32_t mModelShowoffEffect;  // not initialized
		/* 60Ch */	bool field_60C;
		/* 610h */	int field_610;
		/* 614h */	eastl::map<int, int> field_614;
		/* 630h */	eastl::fixed_vector<int, 32> field_630;
		/* 6C8h */	int field_6C8;  // not initialized
		//TODO 6CCh pointer to array of MorphHandles (at 8Ch is anim ID)
		/* 6CCh */	eastl::fixed_vector<EditorBaseHandlePtr, 8> mMorphHandles;
		/* 704h */	eastl::fixed_vector<float, 8> mMorphHandleWeights;
		/* 73Ch */	eastl::fixed_vector<uint32_t, 8> mMorphHandleChannels;
		/* 774h */	eastl::fixed_vector<ResourceKey, 8> mModelSnapDownTo;
		/* 7ECh */	eastl::fixed_vector<ResourceKey, 8> mModelSnapToParentTypes;
		/* 864h */	eastl::fixed_vector<ResourceKey, 8> mModelStayAbove;
		/* 8DCh */	eastl::fixed_vector<ResourceKey, 8> mModelAlignLateralWith;
		/* 954h */	eastl::fixed_vector<ResourceKey, 8> mModelAlignHeightWith;
		/* 9CCh */	eastl::fixed_vector<ResourceKey, 8> mModelAlignXYWith;
		/* A44h */	eastl::fixed_vector<ResourceKey, 8> mModelTypesToInteractWith;
		/* ABCh */	eastl::fixed_vector<ResourceKey, 8> mModelTypesToSnapReplace;
		/* B34h */	eastl::fixed_vector<ResourceKey, 16> mModelTypesNotToInteractWith;
		/* C0Ch */	eastl::fixed_vector<EditorRigblockCapability, 20> mCapabilities;
		/// For audio
		/* DB4h */	uint32_t mFootType;
		/// For audio
		/* DB8h */	uint32_t mMouthType;
		/// For audio
		/* DBCh */	uint32_t mWeaponType;
		/* DC0h */	int field_DC0;  // not initialized
		/* DC4h */	int field_DC4;  // not initialized
		/* DC8h */	eastl::bitset<64> mBooleanAttributes;
		/* DD0h */	UnkEditorRigblockStruct1 field_DD0;
	};
	ASSERT_SIZE(EditorRigblock, 0xE08);

	namespace Addresses(EditorRigblock)
	{
		DeclareAddress(SetShadedDisplay);  // 0x43A980 0x43ACF0
	}
}
