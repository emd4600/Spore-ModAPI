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
#include <Spore\Graphics\Model.h>
#include <Spore\Anim\anim_cid.h>
#include <Spore\Anim\SPAnimation.h>


// ??? Spore calls it "new_ac" so don't really know what it stands for
// off_144CEC0 is the  vftable
// sub_59A990 is the intrusive_ptr setter

// loc_63ACE4 play mode play run animations

//  loc_D49254 ability  loc_D48CFA

// vftable 58h: GetCurrentAnimationID?

#define AnimatedCreaturePtr eastl::intrusive_ptr<Anim::AnimatedCreature>

namespace Anim
{
	typedef int AnimIndex;

	class IAnimWorld;

	class AnimatedCreature
	{
	public:
		//TODO
		/* 00h */	virtual int func00h(int, bool) = 0;  // set flag?

		/// Plays an animation, this is the same as calling LoadAnimation() and StartAnimation().
		/// @param animID The ID of the animation to play, a TLSA group.
		/// @param[in, out] pChoice [Optional] The selected animation choice index will be written here.
		///  If initial value is not -1, it will be used to force a certain choice.
		/// @returns Index of animation, that can be used in other operations.
		/* 04h */	virtual AnimIndex PlayAnimation(uint32_t animID, int* pChoice = nullptr) = 0;

		/// Loads an animation to be used by this creature. It takes the ID of a TLSA group.
		/// It returns an index that is used to identify the animation within this creature.
		///
		/// TLSA Animaiton groups can specify multiple animation choices with different probabilities.
		/// The `pChoice` argument can be provided to force a certain choice index; if the value is -1,
		/// the argument will be used as an ooutput to know what choice has been selected.
		/// @param animID The ID of the animation to play, a TLSA group.
		/// @param[in, out] pChoice [Optional] The selected animation choice index will be written here.
		///  If initial value is not -1, it will be used to force a certain choice.
		/// @returns Index of animation, that can be used in other operations.
		/* 08h */	virtual AnimIndex LoadAnimation(uint32_t animID, int* pChoice = nullptr) = 0;
		/* 0Ch */	virtual bool SetAnimationMode(AnimIndex index, int mode) = 0;  // the default mode is 0
		/* 10h */	virtual bool SetAnimationIdle(AnimIndex index, bool idle) = 0;
		/* 14h */	virtual bool SetAnimationBlendInTime(AnimIndex index, float blendInTime) = 0;

		/// @param index Index of the animation
		/* 18h */	virtual bool StartAnimation(AnimIndex index) = 0;
		/* 1Ch */	virtual bool func1Ch(AnimIndex index, float) = 0;

		/// Enables or disables looping in this animation, which is repating the animation once it ends playing. 
		/// SetLoopTimes() must also be called to set how many times
		/// the animation is looped, setting it to -1 loops it indefinitely.
		/// @param index Index of the animation
		/// @param loop If true, the animation will repeat when it finishes.
		/* 20h */	virtual bool SetLoop(AnimIndex index, bool loop) = 0;

		/// Sets how many times the animation is played. The number does not need to be integer: 
		/// for example, setting it to 0.5 will play half the animation.
		/// Numbers above 1 will only be used if looping is enabled for this animation (SetLoop()).
		/// Setting it to -1 repeats it indefinitely.
		/// @param index Index of the animation
		/// @param loopTimes How many times the animation is played. You can use decimals to only play a portion the last time.
		/* 24h */	virtual bool SetLoopTimes(AnimIndex index, float loopTimes = -1.0f) = 0;
		/* 28h */	virtual bool func28h(AnimIndex index, float) = 0;
		/* 2Ch */	virtual bool func2Ch(AnimIndex index, float) = 0;
		/* 30h */	virtual bool func30h(AnimIndex index, float) = 0;
		/* 34h */	virtual bool func34h(AnimIndex index, float) = 0;
		/* 38h */	virtual bool func38h(AnimIndex index, float) = 0;
		/* 3Ch */	virtual bool func3Ch(AnimIndex index, int) = 0;
		/* 40h */	virtual bool SetAnimationID(AnimIndex index, uint32_t animID) = 0;
		/* 44h */	virtual bool func44h(AnimIndex index, float) = 0;
		/* 48h */	virtual bool func48h(AnimIndex index, int) = 0;
		/* 4Ch */	virtual bool func4Ch(AnimIndex index, int, int) = 0;
		/* 50h */	virtual int func50h() = 0;
		/* 54h */	virtual int func54h() = 0;
		// Used to get current animation ID?
		/* 58h */	virtual int GetCurrentAnimation(uint32_t* dstAnimID, float* dstTime = nullptr, int* = nullptr, AnimIndex* dstAnimIndex = nullptr) = 0;
		/* 5Ch */	virtual bool func5Ch(AnimIndex index, float*, float*) = 0;
		/* 60h */	virtual float GetAnimationLength(uint32_t animID) = 0;
		/* 64h */	virtual int func64h() = 0;
		/* 68h */	virtual int func68h() = 0;
		/* 6Ch */	virtual int func6Ch() = 0;
		/* 70h */	virtual Graphics::IModelWorld* GetAnimWorld() = 0;
		/* 74h */	virtual int func74h() = 0;
		/* 78h */	virtual int func78h() = 0;  // returns main anim_query?
		/* 7Ch */	virtual ~AnimatedCreature();

		static bool IsIdleWalkLookatStart(uint32_t animID);
		static bool IsIdleWalkStop(uint32_t animID);
		static bool IsIdleWalk(uint32_t animID);


		int AddRef();
		int Release();

		Graphics::Model* GetModel();

		/* 04h */	Vector3 mPosition;
		/* 10h */	Quaternion mOrientation;
		/* 20h */	char padding_20[0x154 - 0x20];

		// 3Ch scale?

		// 74h ColorRGBA that gets copied to model color

		/* 154h */	int field_154;
		/* 158h */	int field_158;
		/* 15Ch */	int field_15C;  // another animated creature?
		/* 160h */	int field_160;
		/* 164h */	Vector3 field_164;  // dest position?
		/* 170h */	int field_170[3];
		/* 17Ch */	anim_cid* p_cid;
		/* 180h */	ModelPtr mpModel;
		// 184h "anim_qb", contains data about animations
		/* 184h */	int field_184;
		/* 188h */	int field_188;
		/* 18Ch */	AnimIndex field_18C;
		/* 190h */	IAnimWorld* mpAnimWorld;
		/* 194h */	int field_194;
		/* 198h */	int mnRefCount;
	};
	ASSERT_SIZE(AnimatedCreature, 0x19C);

	struct anim_query
	{
		struct AnimReference {
			uint32_t animID;
			float duration;  // -1.0
			float durationScale;  // 1.0
		};

		/* 00h */	void* p_anim_aid;
		/* 04h */	int field_4;
		/* 08h */	AnimReference anims[8];
		/* 68h */	int field_68;  // index to anims
		/* 6Ch */	AnimIndex field_6C;
		/* 70h */	float field_70;
		/* 74h */	float field_74;
		/* 78h */	float field_78;
		/* 7Ch */	bool field_7C;
		/* 80h */	int mode;  // 1
		/* 84h */	bool idle;
		/* 88h */	float blendInTime;
		/* 8Ch */	float field_8C;
		/* 90h */	float field_90;  // 1.0
		/* 94h */	float field_94;  // 1.0
		/* 98h */	float field_98;
		/* 9Ch */	bool field_9C;
		/* 9Dh */	bool field_9D;
		/* A0h */	float field_A0;
		/* A4h */	int field_A4;  // not initialized
		/* A8h */	float field_A8;  // current time?
		/* ACh */	int field_AC;  // not initialized
		/* B0h */	int field_B0;
		/* B4h */	int field_B4;
		/* B8h */	float field_B8;
		/* BCh */	int field_BC;
		/* C0h */	int field_C0;
		/* C4h */	float field_C4;
		/* C8h */	float field_C8;
		/* CCh */	float field_CC;  // -1.0
		/* D0h */	float field_D0;  // 1.0
		/* D4h */	bool field_D4;
		/* D8h */	uint32_t animID;
		/* DCh */	int field_DC;
		/* E0h */	int field_E0;
		/* E4h */	int field_E4;
		/* E8h */	int field_E8;
		/* ECh */	int field_EC;
	};
	ASSERT_SIZE(anim_query, 0xF0);

	struct anim_qb
	{
		/* 00h */	int field_0;
		/* 04h */	int field_4;
		/* 08h */	anim_query queries[16];
		/* F08h */	int field_F08;  // -1
		/* F0Ch */	int field_F0C[16];  // -1, indices to queries
		/* F4Ch */	int field_F4C[16];  // -1
		/* F8Ch */	int field_F8C;  // not initialized
		/* F90h */	int field_F90;  // not initialized
		/* F94h */	int field_F94;  // not initialized
		/* F98h */	int field_F98;  // not initialized
		/* F9Ch */	int field_F9C;  // -1
		/* FA0h */	int field_FA0;  // -1
		/* FA4h */	int field_FA4;  // -1
		/* FA8h */	int field_FA8;  // -1
		/* FACh */	bool field_FAC;
		/* FB0h */	float field_FB0;
		/* FB4h */	float field_FB4;  // 1.0
		/* FB8h */	float field_FB8;
		/* FBCh */	anim_cid* p_anim_cid;
		/* FC0h */	int field_FC0;
		/* FC4h */	float field_FC4;  // 0.2
		/* FC8h */	float field_FC8;  // 0.4
		/* FCCh */	bool field_FCC;
	};
	ASSERT_SIZE(anim_qb, 0xFD0);

	/*
	struct AnimEntry {
		80h int mode;
		84h	bool idle;
		88h	float blendInTime;

		D8h	uint32_t animID;

		D4h A0h related with endMode

		E8h ECh related with randomizeChoicePerLoop
	};
	*/

	/// Data of a message sent from an animation event
	struct AnimationMessage
	{
		/* 00h */	uint32_t messageID;
		/* 04h */	char* pName;
		/* 08h */	AnimatedCreature* pCreature;
		/* 0Ch */	int blockIndex;
		/* 10h */	int parameter0;
		/* 14h */	float parameter1;
	};

	inline Graphics::Model* AnimatedCreature::GetModel() {
		return mpModel.get();
	}
}