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

#include <Spore\UTFWin\IWinProc.h>
#include <Spore\UTFWin\InteractiveWinProc.h>
#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\Clock.h>

namespace UTFWin
{
	enum class TriggerType
	{
		Visible = 0,
		Invisible = 1,
		Enabled = 2,
		Disabled = 3,
		MouseFocus = 4,
		KeyboardFocus = 5,
		AnyFocus = 6,
		NoMouseFocus = 7,
		NoKeyboardFocus = 8,
		NoFocus = 9,
		ButtonSelected = 10,
		ButtonUnselected = 11
	};

	enum class InterpolationType
	{
		Linear = 0,
		EaseInEaseOut = 1,
		DampedSpring = 2
	};


	// typedef InteractiveWinProc Effect;
	// This is better supported by the SDK-to-Ghidra script
	class Effect : public InteractiveWinProc {};

	class IBiStateEffect : public UTFWinObject
	{
	public:
		///
		/// Get the IWinProc instance that represents this class.
		///
		/* 10h */	virtual IWinProc* ToWinProc() = 0;

		///
		/// Get the duration of the effect.
		///
		/* 14h */	virtual float GetTime() const = 0;

		///
		/// Set the duration of the effect.
		/// @param value
		///
		/* 18h */	virtual void SetTime(float value) = 0;

		///
		/// Get the type of event that triggers this effect, in the TriggerType enum.
		///
		/* 1Ch */	virtual TriggerType GetTriggerType() const = 0;

		///
		/// Set the type of event that triggers this effect, in the TriggerType enum.
		/// @param value The new type of event, in the TriggerType value.
		///
		/* 20h */	virtual void SetTriggerType(TriggerType value) = 0;

		///
		/// Get ease-in and ease-out time, between 0 and 1.
		/// @param[out] easeIn The destination float where the ease-in time will be put.
		/// @param[out] easeOut The destination float where the ease-out time will be put.
		///
		/* 24h */	virtual void GetEase(float& easeIn, float& easeOut) const = 0;

		///
		/// Set ease-in and ease-out time, between 0 and 1.
		/// @param easeIn
		/// @param easeOut
		///
		/* 28h */	virtual void SetEase(float easeIn, float easeOut) = 0;

		///
		/// Get the interpolation type for the effect envelope, in the InterpolationType enum.
		///
		/* 2Ch */	virtual InterpolationType GetInterpolationType() const = 0;

		///
		/// Set the interpolation type for the effect envelope, in the InterpolationType enum.
		/// @param value The new interpolation type, in the InterpolationType enum.
		///
		/* 30h */	virtual void SetInterpolationType(InterpolationType value) = 0;

		///
		/// Get spring damping factor (0-1).
		///
		/* 34h */	virtual float GetDamping() const = 0;

		///
		/// Set spring damping factor (0-1).
		/// @param value
		///
		/* 38h */	virtual void SetDamping(float value) = 0;

		static const uint32_t TYPE = 0x8F2B630B;
	};

	class BiStateEffect : public Effect, public IBiStateEffect
	{
	public:
		BiStateEffect();

		virtual void* Cast(uint32_t typeID) const override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

		virtual int func80h();
		virtual void func84h(int arg_0, float arg_4);
		virtual void func88h(int arg_0, int arg_4, int arg_C);

		virtual IWinProc* ToWinProc() override;
		virtual float GetTime() const override;
		virtual void SetTime(float value) override;
		virtual TriggerType GetTriggerType() const override;
		virtual void SetTriggerType(TriggerType value) override;
		virtual void GetEase(float& easeIn, float& easeOut) const override;
		virtual void SetEase(float easeIn, float easeOut) override;
		virtual InterpolationType GetInterpolationType() const override;
		virtual void SetInterpolationType(InterpolationType value) override;
		virtual float GetDamping() const override;
		virtual void SetDamping(float value) override;


	protected:
		/* 10h */	float mfTime;
		/* 14h */	int field_14;  // not initialized
		/* 18h */	Clock mClock;
		/* 30h */	TriggerType mTriggerType;
		/* 34h */	InterpolationType mInterpolationType;
		/* 38h */	float mfEaseIn;
		/* 3Ch */	float mfEaseOut;
		/* 40h */	float mfDamping;
		/* 44h */	float field_44;
		/* 48h */	float field_48;
		/* 4Ch */	float field_4C;
		/* 50h */	bool field_50;
		/* 54h */	int field_54;
		/* 58h */	int field_58;
		/* 5Ch */	int field_5C;  // not initialized

	};
	ASSERT_SIZE(BiStateEffect, 0x60);

	namespace Addresses(BiStateEffect)
	{
		DeclareAddress(SetSerializer);

		DeclareAddress(GetEventFlags);
		DeclareAddress(HandleUIMessage);

		DeclareAddress(ToWinProc);
		DeclareAddress(GetTime);
		DeclareAddress(SetTime);
		DeclareAddress(GetTriggerType);
		DeclareAddress(SetTriggerType);
		DeclareAddress(GetEase);
		DeclareAddress(SetEase);
		DeclareAddress(GetInterpolationType);
		DeclareAddress(SetInterpolationType);
		DeclareAddress(GetDamping);
		DeclareAddress(SetDamping);
	}
};