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

namespace UTFWin
{
	///
	/// An abstract class that has the methods that a drawable for a slider would require.
	///
	class ISliderDrawable : public UTFWinObject
	{
	public:
		enum
		{
			kImageBackground = 0,
			kImageThumb = 1,
			kImageThumbContainer = 2
		};

		///
		/// Get the IDrawable instance that represents this class.
		///
		/* 10h */	virtual IDrawable* ToDrawable() = 0;
		
		///
		/// Set the images used by this drawable. The index is one of the AbstractSliderDrawable::kImage... values.
		/// @param index The index of the image to set.
		/// @param pImage The image.
		///
		/* 14h */	virtual void SetImage(int index, Image* image) = 0;

		static const uint32_t TYPE = 0x4F00A9EB;
	};

	///
	/// The standard IDrawable for a slider component.
	///
	class SliderDrawable : public IDrawable, public DefaultLayoutElement, public ISliderDrawable
	{
	public:
		SliderDrawable();
		virtual ~SliderDrawable();

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) override;

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

	static_assert(sizeof(SliderDrawable) == 0x1C, "sizeof(SliderDrawable) != 1Ch");

	namespace InternalAddressList(SliderDrawable)
	{
		DefineAddress(Paint, GetAddress(0x984C70, 0x9849A0, 0x9849A0));
		DefineAddress(IsColliding, GetAddress(0x689880, 0x5ACA30, 0x5ACA30));
		DefineAddress(GetDimensions, GetAddress(0x984240, 0x983F20, 0x983F20));
		DefineAddress(UseCollision, GetAddress(0x951320, 0x950E00, 0x950E00));

		DefineAddress(SetSerializer, GetAddress(0x984BA0, 0x9848D0, 0x9848D0));
		DefineAddress(GetProxyID, GetAddress(0x9841E0, 0x983ED0, 0x983ED0));

		DefineAddress(ToDrawable, GetAddress(0x97E760, 0x96FEB0, 0x96FEB0));
		DefineAddress(SetImage, GetAddress(0x9863B0, 0x983F70, 0x983F70));
	}

	inline SliderDrawable::SliderDrawable()
		: mpImages()
	{}

	inline SliderDrawable::~SliderDrawable() {}
}