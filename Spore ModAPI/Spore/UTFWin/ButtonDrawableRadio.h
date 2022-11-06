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

#define IButtonDrawableRadioPtr eastl::intrusive_ptr<UTFWin::IButtonDrawableRadio>

namespace UTFWin
{
	///
	/// An abstract class that has the methods that a drawable for a simple radio or checkbox button would require.
	///
	class IButtonDrawableRadio : public UTFWinObject
	{
	public:
		///
		/// Get the IDrawable instance that represents this class.
		///
		/* 10h */	virtual IDrawable* ToDrawable() = 0;

		///
		/// Set the image used by this drawable. The image must be composed of 6 different images of the same dimensions, 
		/// that represent different states: Normal | Highlighted | Depressed | Selected | Selected Highlighted | Selected Depressed.
		/// @param pImage The image to use in this drawable.
		/// @param bTileable Specifies whether the image should be edge tiled.
		///
		/* 14h */	virtual void SetImage(Image* pImage, bool bTileable) = 0;

		static const uint32_t TYPE = 0x2F02135C;
	};

	///
	/// The standard IDrawable for a standard, simple radio or checkbox button component.
	///
	class ButtonDrawableRadio : public IDrawable, public DefaultLayoutElement, public IButtonDrawableRadio
	{
	public:
		ButtonDrawableRadio();
		virtual ~ButtonDrawableRadio();

		///
		/// Gets the texture coordinates that must be used to render the image that corresponds to the given state.
		/// @param state The state of the window.
		/// @param[out] dst The Rectangle where the texture coordinates will be written.
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

	static_assert(sizeof(ButtonDrawableRadio) == 0x18, "sizeof(ButtonDrawableRadio) != 18h");

	namespace Addresses(ButtonDrawableRadio)
	{
		DeclareAddress(Paint);
		DeclareAddress(IsColliding);
		DeclareAddress(GetDimensions);
		DeclareAddress(UseCollision);
		DeclareAddress(GetTexCoords);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(ToDrawable);
		DeclareAddress(SetImage);

	}

	inline ButtonDrawableRadio::ButtonDrawableRadio()
		: mpImage(nullptr)
		, mbTileable(false)
	{

	}

	inline ButtonDrawableRadio::~ButtonDrawableRadio() {}
}