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
#include <Spore\Graphics\ModelAsset.h>


// ??? Spore calls it "new_ac" so don't really know what it stands for
// off_144CEC0 is the  vftable
// sub_59A990 is the intrusive_ptr setter

// loc_63ACE4 play mode play run animations

//  loc_D49254 ability  loc_D48CFA

// [127h]: at 2E4h has vector<CreatureBlock>

// vftable 58h: GetCurrentAnimationID?

#define AnimatedCreaturePtr intrusive_ptr<Anim::AnimatedCreature>

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
		/* 28h */	virtual int func28h() = 0;
		/* 2Ch */	virtual int func2Ch() = 0;
		/* 30h */	virtual int func30h() = 0;
		/* 34h */	virtual int func34h() = 0;
		/* 38h */	virtual int func38h() = 0;
		/* 3Ch */	virtual int func3Ch(int index, int) = 0;
		/* 40h */	virtual bool SetAnimationID(AnimIndex index, uint32_t animID) = 0;
		/* 44h */	virtual int func44h() = 0;
		/* 48h */	virtual int func48h() = 0;
		/* 4Ch */	virtual int func4Ch() = 0;
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
		/* 78h */	virtual int func78h() = 0;
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
		/* 17Ch */	int field_17C;  // contains blocks?
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

	inline Graphics::Model* AnimatedCreature::GetModel() {
		return mpModel.get();
	}
}