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

#include <Spore\UTFWin\UTFWinObject.h>
#include <Spore\MathUtils.h>
#include <Spore\UTFWin\UIRenderer.h>

using namespace Math;

namespace UTFWin
{
	class IWindow;

	///
	/// A structure used to represent various parameters for the IDrawable::Paint() method, 
	/// like which image to draw, the current state of the window, etc
	///
	struct RenderParams
	{
		/* 00h */	int state;
		/* 04h */	int index;
		/* 08h */	Math::Color fillColor;
		/* 0Ch */	Math::Color shadeColor;
	};

	///
	/// An enumeration used by certain drawables, that determines how to draw the images.
	///
	enum class Scaling
	{
		/// Stretch the entire image so it fills all the space.
		StretchImage = 1,
		/// Draw the edges of the image normally and then stretch the center.
		StretchCenter = 2,
		/// Use tiling to fill the space, repeatedly rendering the image.
		TileImage = 3,
		/// Draw the edges of the iamge normally, and then tile the center.
		TileCenter = 4
	};

	///
	/// A class that is capable of drawing a user interface component. IDrawables are used by IWindow objects to render.
	/// The most important method is the IDrawable::Paint() method, which is the only one that is really required.
	/// 
	/// An IDrawable::Paint() call doesn't need to paint the entire component at once; some components might do multiple calls
	/// varying the RenderParams object that is passed as an argument. This way the IWindow can draw different images, for example,
	/// on different positions (for example, in a WinScrollbar you first want to draw the background, then the handle at the handle position, etc).
	///
	/// An IDrawable can also take care of collision detection. This can be useful in buttons, for example, where the shape might not
	/// necessarily be a rectangle.
	///
	class IDrawable : public UTFWinObject
	{
	public:
		static const uint32_t TYPE = 0x6EC581FD;

		enum
		{
			kDefaultCollisionType = 0x19C46FB
		};

		virtual void* Cast(uint32_t) const override;

		///
		/// Paints this drawable onto the given UIRenderer.
		/// @param pRenderer The UIRenderer where this must be drawn.
		/// @param area The area of the window to draw.
		/// @param params RenderParams that contain additional information (e.g. what image do draw, the current state, etc).
		///
		/* 10h */	virtual void Paint(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params) = 0;

		///
		/// Tells whether the point specified is colliding in this drawable or not. This method is useful for drawables that use hitmasks.
		/// @param area The area of the window that is using this drawable.
		/// @param point The Point to check whether it collides or not. Its coordinates are relative to the window position.
		/// @param params Additional information, probably unused.
		///
		/* 14h */	virtual bool IsColliding(const Math::Rectangle& area, const Math::Point& point, RenderParams& params) = 0;

		///
		/// Used to get the dimensions of an image contained in this drawable. 
		/// @param[out] dst The Dimensions where the result must be written.
		/// @param state The current state flags of the window.
		/// @param index The index of the image whose dimensions must be returned.
		/// @returns True if the dimensions were got, false otherwise.
		///
		/* 18h */	virtual bool GetDimensions(Dimensions& dst, int state, int index) = 0;

		///
		/// Tells whether the collision of a window should be handled by this drawable or not.
		/// @param type The type, usually kDefaultCollisionType.
		/// @param[out] dst If the collision type is supported, whether it must be handled by this drawable or not.
		/// @returns True if the collision type is supported (even if it's not handled by this drawable), false otherwise.
		///
		/* 1Ch */	virtual bool UseCollision(uint32_t type, bool& dst) = 0;
	};

	///
	/// A class that implements all the methods of an IDrawable. This can be used to easily create custom
	/// drawables, only overriding the methods you need.
	///
	class DefaultDrawable : public IDrawable
	{
	public:
		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual void Paint(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params) override;
		virtual bool IsColliding(const Math::Rectangle& area, const Math::Point& point, RenderParams& params) override;
		virtual bool GetDimensions(Dimensions& dst, int state, int index) override;
		virtual bool UseCollision(uint32_t type, bool& dst) override;

	protected:
		int mnRefCount;
	};
}