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
	/// An abstract class that has the methods that a drawable for a simple standard button would require.
	///
	class IButtonDrawableStandard : public UTFWinObject
	{
	public:
		///
		/// Get the IDrawable instance that represents this class.
		///
		/* 10h */	virtual IDrawable* ToDrawable() = 0;

		///
		/// Set the image used by this drawable. The image must be composed of 4 different images of the same dimensions, 
		/// that represent different states: Disabled | Normal | Highlighted | Depressed.
		/// @param pImage The image to use in this drawable.
		/// @param bTileable Specifies whether the image should be edge tiled.
		///
		/* 14h */	virtual void SetImage(Image* pImage, bool bTileable) = 0;

		static const uint32_t TYPE = 0x2F02135C;
	};

	///
	/// The standard IDrawable for a standard, simple button component.
	///
	class ButtonDrawableStandard : public IDrawable, public DefaultLayoutElement, public IButtonDrawableStandard
	{
	public:
		ButtonDrawableStandard();
		virtual ~ButtonDrawableStandard();

		///
		/// Gets the texture coordinates that must be used to render the image that corresponds to the given state.
		/// @param state The state of the window.
		/// @param[Out] dst The Rectangle where the texture coordinates will be written.
		/// @returns Whether there's a valid image or not.
		///
		virtual bool GetTexCoords(int state, Math::Rectangle& dst) const;

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
		virtual void SetImage(Image* pImage, bool bTileable) override;

	protected:
		/* 10h */	intrusive_ptr<Image> mpImage;
		/* 14h */	bool mbTileable;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(ButtonDrawableStandard) == 0x18, "sizeof(ButtonDrawableStandard) != 18h");

	namespace Addresses(ButtonDrawableStandard)
	{
		DeclareAddress(Paint, SelectAddress(0x965970, 0x9655F0, 0x9655F0));
		DeclareAddress(IsColliding, SelectAddress(0x689880, 0x5ACA30, 0x5ACA30));
		DeclareAddress(GetDimensions, SelectAddress(0x964A20, 0x964690, 0x964690));
		DeclareAddress(UseCollision, SelectAddress(0x951320, 0x950E00, 0x950E00));
		DeclareAddress(GetTexCoords, SelectAddress(0x966DC0, 0x966A40, 0x966A40));

		DeclareAddress(SetSerializer, SelectAddress(0x9658E0, 0x965560, 0x965560));
		DeclareAddress(GetProxyID, SelectAddress(0x964A10, 0x964680, 0x964680));

		DeclareAddress(ToDrawable, SelectAddress(0x97E760, 0x96FEB0, 0x96FEB0));
		DeclareAddress(SetImage, SelectAddress(0x9649C0, 0x964630, 0x964630));

	}

	inline ButtonDrawableStandard::ButtonDrawableStandard()
		: mpImage(nullptr)
		, mbTileable(false)
	{

	}

	inline ButtonDrawableStandard::~ButtonDrawableStandard() {}
}