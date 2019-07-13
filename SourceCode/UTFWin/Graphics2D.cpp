/****************************************************************************
* Copyright (C) 2018 Eric Mor
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

#include <Spore\UTFWin\Graphics2D.h>
#include <Spore\UTFWin\UIRenderer.h>

namespace UTFWin
{
	const wchar_t* const Graphics2D::kDefaultFontName = nullptr;
	const wchar_t* const Graphics2D::kDefaultFont = nullptr;

	auto_STATIC_METHOD_VOID(Graphics2D, DrawTiledImage,
		Args(Graphics2D* graphics, const Math::Rectangle& bounds, const Math::Rectangle& texCoords, const Image* image, float scaleX, float scaleY, float offsetX, float offsetY),
		Args(graphics, bounds, texCoords, image, scaleX, scaleY, offsetX, offsetY));

	auto_STATIC_METHOD_VOID(Graphics2D, DrawSlicedTiledImage,
		Args(Graphics2D* graphics, const Math::Rectangle& bounds, const Math::Rectangle& texCoords, const Image* image, const Math::Rectangle& sliceProportions, float scaleX, float scaleY),
		Args(graphics, bounds, texCoords, image, sliceProportions, scaleX, scaleY));

	auto_STATIC_METHOD_VOID(Graphics2D, DrawSlicedStretchedImage,
		Args(Graphics2D* graphics, const Math::Rectangle& bounds, const Math::Rectangle& texCoords, const Image* image, const Math::Rectangle& sliceProportions, float scaleX, float scaleY),
		Args(graphics, bounds, texCoords, image, sliceProportions, scaleX, scaleY));


	auto_METHOD(UIRenderer, Graphics2D&, GetGraphics2D, Args(int arg_0), Args(arg_0));
}