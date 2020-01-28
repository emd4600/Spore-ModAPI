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

#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\IDrawable.h>

#define FrameDrawablePtr intrusive_ptr<UTFWin::FrameDrawable>

namespace UTFWin
{
	struct FrameStyle
	{
		enum
		{
			kBorderDefault = 0,
			kBorderHidden = 1,
			kBorderSolid = 2,
			kBorderDotted = 3,
			kBorderDashed = 4,
			kBorderInset = 5,
			kBorderOutset = 6,
			kBorderGroove = 7,
			kBorderRidge = 8,
			kBorderOutsetOutline = 9,
			kBorderInsetOutline = 10
		};

		FrameStyle();
		FrameStyle(int nBorderStyle, Color color);

		int mnBorderStyle;
		Color mColor;
	};


	///
	/// FrameDrawable is a procedural drawable that renders multiple frame styles depending on the current state.
	///
	class FrameDrawable : public IDrawable, public DefaultLayoutElement
	{
	public:
		static const uint32_t TYPE = 0x30D54AC;

		FrameDrawable();
		virtual ~FrameDrawable();

		///
		/// Gets the border style that is being used for the state specified.
		/// @param stateIndex The index that corresponds to the desired state.
		/// @param[out] dst The FrameStyle where the style will be written.
		/// @returns True if the index is valid, false otherwise.
		///
		bool GetStyle(size_t stateIndex, FrameStyle& dst) const;

		///
		/// Sets the border style that will be used for the state specified.
		/// @param style The style to use.
		/// @param stateIndex The index that corresponds to the desired state.
		/// @returns True if the index is valid, false otherwise.
		///
		bool SetStyle(const FrameStyle& style, size_t stateIndex);

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

	protected:
		/* 0Ch */	FrameStyle mStyles[8];
		/* 4Ch */	Math::Rectangle mBorderWidth;
		/* 5Ch */	Color field_5C;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(FrameDrawable) == 0x60, "sizeof(FrameDrawable) != 60h");

	namespace Addresses(FrameDrawable)
	{
		DeclareAddress(Paint);
		DeclareAddress(IsColliding);
		DeclareAddress(GetDimensions);
		DeclareAddress(UseCollision);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

	}

	inline FrameStyle::FrameStyle()
		: mColor(0), mnBorderStyle(0)
	{

	}
	inline FrameStyle::FrameStyle(int nBorderStyle, Color color)
		: mColor(color), mnBorderStyle(nBorderStyle)
	{

	}

	inline FrameDrawable::FrameDrawable()
		: mStyles{}
		, mBorderWidth{ 1.0f, 1.0f, 1.0f, 1.0f }
		, field_5C(0, 0, 0, 255)
	{
		mStyles[0].mColor = Color::WHITE;
		mStyles[0].mnBorderStyle = FrameStyle::kBorderSolid;
	}

	inline FrameDrawable::~FrameDrawable() {}

	inline bool FrameDrawable::GetStyle(size_t stateIndex, FrameStyle& dst) const
	{
		if (stateIndex > 7) return false;

		dst = mStyles[stateIndex];

		return true;
	}

	inline bool FrameDrawable::SetStyle(const FrameStyle& style, size_t stateIndex)
	{
		if (stateIndex > 7) return false;

		mStyles[stateIndex] = style;

		return true;
	}
}