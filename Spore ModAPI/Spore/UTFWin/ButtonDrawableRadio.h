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
#include <Spore\UTFWin\IButton.h>
#include <Spore\UTFWin\Image.h>

#define ButtonDrawableRadioPtr eastl::intrusive_ptr<UTFWin::ButtonDrawableRadio>

namespace UTFWin
{
	///
	/// The standard IDrawable for a standard, simple radio or checkbox button component.
	///
	class ButtonDrawableRadio : public IDrawable, public DefaultLayoutElement, public IButtonDrawable
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
		/* 10h */	ImagePtr mpImage;
		/* 14h */	bool mbTileable;
	};
	ASSERT_SIZE(ButtonDrawableRadio, 0x18);

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