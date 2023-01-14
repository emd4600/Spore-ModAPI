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

#include <Spore\UTFWin\Effect.h>

#define IRotateEffectPtr eastl::intrusive_ptr<UTFWin::IRotateEffect>

namespace UTFWin
{
	class IRotateEffect : public UTFWinObject
	{
	public:
		///
		/// Get the IWinProc instance that represents this class.
		///
		/* 10h */	virtual IWinProc* ToWinProc() = 0;

		///
		/// Get rotation axis (need not be normalized).
		///
		/* 14h */	virtual const Math::Vector3& GetRotationAxis() const = 0;

		///
		/// Set rotation axis (need not be normalized).
		/// @param axis
		///
		/* 18h */	virtual void SetRotationAxis(const Math::Vector3& axis) = 0;

		///
		/// Get angle to rotate by clockwise (in degrees).
		///
		/* 1Ch */	virtual float GetRotationAngle() const = 0;

		///
		/// Set angle to rotate by clockwise (in degrees).
		/// @param angle
		///
		/* 20h */	virtual void SetRotationAngle(float angle) = 0;

		static const uint32_t TYPE = 0xEF2B293B;
	};

	class RotateEffect : public BiStateEffect, public IRotateEffect
	{
	public:
		RotateEffect();
		virtual ~RotateEffect() {}

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t typeID) const override;

		/* 14h */	virtual int GetEventFlags() const override;
		/* 18h */	virtual bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		/* 10h */	virtual IWinProc* ToWinProc() override;
		/* 14h */	virtual const Math::Vector3& GetRotationAxis() const override;
		/* 18h */	virtual void SetRotationAxis(const Math::Vector3& axis) override;
		/* 1Ch */	virtual float GetRotationAngle() const override;
		/* 20h */	virtual void SetRotationAngle(float angle) override;

		virtual int func80h() override;
		virtual void func88h(int, int, int) override;

	protected:
		/* 64h */	Math::Vector3 mRotAxis;
		/* 70h */	float mfRotAngle;
		/* 74h */	float field_74;
	};
	ASSERT_SIZE(RotateEffect, 0x78);

	namespace Addresses(RotateEffect)
	{
		DeclareAddress(GetEventFlags);
		DeclareAddress(HandleUIMessage);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(func80h);
		DeclareAddress(func88h);

		DeclareAddress(ToWinProc);
		DeclareAddress(GetRotationAxis);
		DeclareAddress(SetRotationAxis);
		DeclareAddress(GetRotationAngle);
		DeclareAddress(SetRotationAngle);
	}
};
