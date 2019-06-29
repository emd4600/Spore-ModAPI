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


#include "IDrawable.h"
#include "ILayoutElement.h"
#include "OutlineFormat.h"
#include "Image.h"
#include "../MathUtils.h"

#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\Image.h>
#include <Spore\UTFWin\OutlineFormat.h>

namespace UTFWin
{
	///
	/// An abstract class that has the methods that a standard drawable would require.
	/// A standard drawable is capable of drawing different images depending on the window state, therefore it is
	/// suitable for any components that allow user interaction. A StdDrawable is also capable of detecting collisions based on 
	/// a hit mask object.
	///
	class IStdDrawable : public UTFWinObject
	{
	public:
		///
		/// Gets the image for the specified state.
		/// @param index The index for the state required.
		///
		/* 10h */	virtual Image* GetImage(StateIndices index) const = 0;
		
		///
		/// Sets the image for the specified state.
		/// @param index The index for the state required.
		/// @param pImage The image.
		///
		/* 14h */	virtual void SetImage(StateIndices index, Image* pImage) = 0;
		
		///
		/// Specifies how the image should be stretched when the window changes size.
		///
		/* 18h */	virtual Scaling GetScaleType() const = 0;
		
		///
		/// Specifies how the image should be stretched when the window changes size.
		/// @param value The new value, from the Scaling enumeration.
		///
		/* 1Ch */	virtual void SetScaleType(Scaling value) = 0;

		///
		/// Indicates the width of each non-stretched edge, as a proportion of image size (0 to 1).
		///

		/* 20h */	virtual const Math::Rectangle& GetScaleArea() const = 0;

		///
		/// Indicates the width of each non-stretched edge, as a proportion of image size (0 to 1).
		/// @param value The new value.
		///
		/* 24h */	virtual void SetScaleArea(const Math::Rectangle& value) = 0;

		///
		/// Gets the scaling factor for the non-stretched portions of the artwork.
		///
		/* 28h */	virtual const Vector2& GetScaleFactor() const = 0;

		///
		/// Sets the scaling factor for the non-stretched portions of the artwork
		/// @param value A Vector2 value containing the X and Y scale.
		///
		/* 2Ch */	virtual void SetScaleFactor(Vector2& value) = 0;

		///
		/// Gets the hit mask for this drawable.
		///
		/* 30h */	virtual Object* GetHitMask() const = 0;

		///
		/// Sets the hit mask for this drawable.
		/// @param pHitMask The new hit mask object.
		///
		/* 34h */	virtual void SetHitMask(Object* pHitMask) = 0;

		/* 38h */	virtual float GetHitFactor() const = 0;
		/* 3Ch */	virtual void SetHitFactor(float value) = 0;

		static const uint32_t TYPE = 0x103C1908;
	};

	///
	/// The standard IDrawable for user interactive components. Check AbstractStdDrawable for more information.
	///
	class StdDrawable : public IDrawable, public DefaultLayoutElement, public IStdDrawable
	{
	public:
		StdDrawable();
		virtual ~StdDrawable();

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

		virtual void Paint(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params) override;
		virtual bool IsColliding(const Math::Rectangle& area, const Math::Point& point, RenderParams& params) override;
		virtual bool GetDimensions(Dimensions& dst, int state, int index) override;
		virtual bool UseCollision(uint32_t type, bool& dst) override;

		virtual Image* GetImage(StateIndices index) const override;
		virtual void SetImage(StateIndices index, Image* pImage) override;
		virtual Scaling GetScaleType() const override;
		virtual void SetScaleType(Scaling value) override;
		virtual const Math::Rectangle& GetScaleArea() const override;
		virtual void SetScaleArea(const Math::Rectangle& value) override;
		virtual const Vector2& GetScaleFactor() const override;
		virtual void SetScaleFactor(Vector2& value) override;
		virtual Object* GetHitMask() const override;
		virtual void SetHitMask(Object* pHitMask) override;
		virtual float GetHitFactor() const override;
		virtual void SetHitFactor(float value) override;


	protected:

		/* 10h */	intrusive_ptr<Image> mpImages[8];

		/* 30h */	Scaling			mScaleType;
		/* 34h */	Math::Rectangle mScaleArea;
		/* 44h */	Math::Vector2	mScaleFactor;
		/* 4Ch */	intrusive_ptr<Object> mpHitMask;
		/* 50h */	float property_0F3C000E;

		/* 54h */	OutlineFormat mImageOutline;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(StdDrawable) == 0x7C, "sizeof(StdDrawable) != 7Ch");

	namespace InternalAddressList(StdDrawable)
	{
		DefineAddress(Paint, GetAddress(0x987FC0, 0x987C70, 0x987C70));
		DefineAddress(IsColliding, GetAddress(0x988360, 0x988010, 0x988010));
		DefineAddress(GetDimensions, GetAddress(0x988670, 0x988320, 0x988320));
		DefineAddress(UseCollision, GetAddress(0x988640, 0x9882F0, 0x9882F0));

		DefineAddress(SetSerializer, GetAddress(0x987D60, 0x987A10, 0x987A10));
		DefineAddress(GetProxyID, GetAddress(0x987C60, 0x987910, 0x987910));

		DefineAddress(GetImage, GetAddress(0x987C40, 0x9878E0, 0x9878E0));
		DefineAddress(SetImage, GetAddress(0x987C00, 0x9878A0, 0x9878A0));
		DefineAddress(GetScaleType, GetAddress(0x804E30, 0xFF3480, 0xFF3480));
		DefineAddress(SetScaleType, GetAddress(0x112EBC0, 0x987900, 0x987900));
		DefineAddress(GetScaleArea, GetAddress(0xFF0B60, 0x830AB0, 0x830B30));
		DefineAddress(SetScaleArea, GetAddress(0x8313B0, 0x830B30, 0x830BB0));
		DefineAddress(GetScaleFactor, GetAddress(0xAD25F0, 0xAD2700, 0xAD2740));
		DefineAddress(SetScaleFactor, GetAddress(0x8313D0, 0x830B50, 0x830BD0));
		DefineAddress(GetHitMask, GetAddress(0x97F0E0, 0xA1AC50, 0xA1ACE0));
		DefineAddress(SetHitMask, GetAddress(0x987E30, 0x987AE0, 0x987AE0));
		DefineAddress(GetHitFactor, GetAddress(0x831340, 0x830AC0, 0x830B40));
		DefineAddress(SetHitFactor, GetAddress(0x831350, 0x830AD0, 0x830B50));

	}

	inline StdDrawable::StdDrawable()
		: mpImages{}
		, mScaleFactor(1.0f, 1.0f)
		, mScaleArea(0.333f, 0.333f, 0.333f, 0.333f)
		, mScaleType(Scaling::StretchImage)
		, mpHitMask(nullptr)
		, property_0F3C000E(6.0f)
		, mImageOutline()
	{
		mImageOutline.SetStrength(2);
	}
	inline StdDrawable::~StdDrawable() {}
}

