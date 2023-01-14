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
#include <Spore\UTFWin\Image.h>

namespace UTFWin
{
	///
	/// A drawable that completely fills the window of variable width with a graphic without a horizontal stretch.
	///
	class VariableWidthDrawable : public IDrawable, public DefaultLayoutElement
	{
	public:
		VariableWidthDrawable();
		virtual ~VariableWidthDrawable();

		///
		/// Gets the background image.
		///
		Image* GetImage() const;

		///
		/// Sets the background image.
		/// @param pImage The image.
		///
		void SetImage(Image* pImage);

		///
		/// Gets the fill color that will be used if no image is specified.
		///
		Color GetFillColor() const;

		///
		/// Sets the fill color that will be used if no image is specified.
		/// @param color The new fill color.
		///
		void SetFillColor(Color color);

		virtual VariableWidthDrawable& ToDrawable();

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
		/* 0Ch */	ImagePtr mpImage;
		/* 10h */	Color mFillColor;
	};
	ASSERT_SIZE(VariableWidthDrawable, 0x14);

	typedef VariableWidthDrawable ProgressBarDrawable;

	namespace Addresses(VariableWidthDrawable)
	{
		DeclareAddress(Paint);
		DeclareAddress(IsColliding);
		DeclareAddress(GetDimensions);
		DeclareAddress(UseCollision);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);
	}

	inline VariableWidthDrawable::VariableWidthDrawable()
		: mpImage(nullptr)
		, mFillColor(Color::WHITE)
	{
	}

	inline VariableWidthDrawable::~VariableWidthDrawable() {}

	inline Image* VariableWidthDrawable::GetImage() const
	{
		return mpImage.get();
	}
	inline void VariableWidthDrawable::SetImage(Image* pImage)
	{
		mpImage = pImage;
	}

	inline Color VariableWidthDrawable::GetFillColor() const
	{
		return mFillColor;
	}
	inline void VariableWidthDrawable::SetFillColor(Color color)
	{
		mFillColor = color;
	}

}