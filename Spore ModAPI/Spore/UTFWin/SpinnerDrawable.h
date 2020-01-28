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

#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\Image.h>

#define ISpinnerDrawablePtr intrusive_ptr<UTFWin::ISpinnerDrawable>

namespace UTFWin
{
	///
	/// An abstract class that has the methods that a drawable for a spinner would require.
	///
	class ISpinnerDrawable : public UTFWinObject
	{
	public:
		enum
		{
			kImageBackground = 0,
			kImageIncrementButton = 1,
			kImageDecrementButton = 2
		};

		///
		/// Get the IDrawable instance that represents this class.
		///
		/* 10h */	virtual IDrawable* ToDrawable() = 0;

		///
		/// Set the images used by this drawable. The index is one of the AbstractComboBoxDrawable::kImage... values.
		/// @param index The index of the image to set.
		/// @param image The image.
		///
		/* 14h */	virtual void SetImage(int index, Image* image) = 0;

		static const uint32_t TYPE = 0x6F0631DF;
	};

	///
	/// The standard IDrawable for a spinner component.
	///
	class SpinnerDrawable : public IDrawable, public DefaultLayoutElement, public ISpinnerDrawable
	{
	public:
		SpinnerDrawable();
		virtual ~SpinnerDrawable();

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

		virtual IDrawable* ToDrawable() override;
		virtual void SetImage(int index, Image* pImage) override;

	protected:
		/* 10h */	intrusive_ptr<Image> mpImages[3];
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(SpinnerDrawable) == 0x1C, "sizeof(SpinnerDrawable) != 1Ch");

	namespace Addresses(SpinnerDrawable)
	{
		DeclareAddress(Paint);
		DeclareAddress(IsColliding);
		DeclareAddress(GetDimensions);
		DeclareAddress(UseCollision);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(ToDrawable);
		DeclareAddress(SetImage);
	}

	inline SpinnerDrawable::SpinnerDrawable()
		: mpImages()
	{}

	inline SpinnerDrawable::~SpinnerDrawable() {}
}