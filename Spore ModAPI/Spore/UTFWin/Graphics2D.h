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

#include <EASTL\vector.h>

#include <Spore\Internal.h>
#include <Spore\MathUtils.h>
#include <Spore\UTFWin\Image.h>

namespace UTFWin
{
	///
	/// A class that can be used to draw things in the user interface. It supports drawing basic shapes (rectangles, lines, triangles)
	/// as well as text and images. There are also some static methods that can help using more complex methods when drawing images,
	/// like tiling and slicing.
	///
	/// A Graphics2D object has a color, which is used when painting shapes and text (and it acts like a tint when painting images).
	/// Once the color is set, all subsequent operations will use that color, so it is not necessary to set it before every call.
	///
	/// A graphics context also supports clipping. All rendering operations modify only pixels which lie within the area bounded by the current clip.
	/// Clipping can be enabled/disabled and the area can be changed.
	///
	class Graphics2D
	{

	public:

		static const int kAutoLength = -1;

		// We used constexpr here before, but Visual Studio 2013 doesn't support it....
		static const wchar_t* const kDefaultFontName;
		static const wchar_t* const kDefaultFont;

		/* 00h */	virtual ~Graphics2D() = 0;

		///
		/// Sets this graphics context current color to the color specified. All subsequent operations using
		/// this graphics context will use this color.
		/// @param color The new rendering color.
		///
		/* 04h */	virtual void SetColor(Math::Color color) = 0;

		///
		/// Gets this Graphics2D current rendering color.
		///
		/* 08h */	virtual Math::Color GetColor() = 0;

		///
		/// Gets the clip area currently used by this graphics context.
		/// All rendering operations modify only pixels which lie within the area bounded by the current clip.
		/// @param[Out] dst The Rectangle where the clip will be output.
		/// @returns Whether this context is using clipping or not.
		///
		/* 0Ch */	virtual bool GetClipArea(Math::Rectangle& dst) = 0;

		///
		/// Sets the clip area or disables clipping.
		/// All rendering operations modify only pixels which lie within the area bounded by the current clip
		/// @param bUseClipArea Whether to use clipping or not.
		/// @param area The new clip area.
		///
		/* 10h */	virtual void SetClipArea(bool bUseClipArea, const Math::Rectangle& area) = 0;

		/// 
		/// Intersects the current clip area with the specified rectangle and sets the clip area to the resulting intersection.
		/// This method is used to make the clip area smaller; if 'area' is larger, the clip area will be set to 0.
		/// If this context doesn't use clipping, it will use it after calling this method with 'area' as the clip.
		/// @param area The rectangle to intersect the clip with.
		///
		/* 14h */	virtual void IntersectClip(const Math::Rectangle& area) = 0;

		///
		/// Draws a 1-pixel thick line from the (x1, y1) coordinates to the (x2, y2) coordinates,
		/// using the graphics context current color.
		/// @param x1 The start point X coordinate.
		/// @param y1 The start point Y coordinate.
		/// @param x2 The end point X coordinate.
		/// @param y2 The end point Y coordinate.
		///
		/* 18h */	virtual void DrawLine(float x1, float y1, float x2, float y2) = 0;

		///
		/// Fills a border at the specified coordinates using the graphics context current color. 
		/// @param left The X coordinate where the left edge is. The painted region will be in the [left, left + thickness] range.
		/// @param top The Y coordinate where the top edge is. The painted region will be in the [top, top + thickness] range.
		/// @param right The X coordinate where the right edge is. The painted region will be in the [right, right - thickness] range.
		/// @param bottom The Y coordinate where the bottom edge is. The painted region will be in the [bottom, bottom - thickness] range.
		///
		/* 1Ch */	virtual void FillBorder(float left, float top, float right, float bottom, float thickness) = 0;

		///
		/// Draws the given wstring at the specified area. The text will be drawn in the x1,y1 coordinates of the rectangle, the rest will be ignored. 
		/// @param area The rectangle where the top-left corner of the text begins.
		/// @param pString The wchar_t* string to draw.
		/// @param length [Optional] The number of characters of the string to draw. Use Graphics2D::kAutoLength to draw the entire text.
		/// @param pFontName [Optional] The name of the font that will be used to render this text, for example "Arial".
		///
		/* 20h */	virtual void DrawStringArea(const Math::Rectangle& area, 
			const wchar_t* pString, int nLength = kAutoLength, const wchar_t* pFontName = kDefaultFontName, int = 0, int = 0, int = 0) = 0;

		///
		/// Draws the given wstring at the specified position. 
		/// @param x The X coordinate where the top-left corner of the text begins.
		/// @param y The Y coordinate where the top-left corner of the text begins.
		/// @param pString The wchar_t* string to draw.
		/// @param length [Optional] The number of characters of the string to draw. Use Graphics2D::kAutoLength to draw the entire text.
		/// @param pFontName [Optional] The name of the font that will be used to render this text, for example "Arial".
		///
		/* 24h */	virtual void DrawString(
			float x, float y, 
			const wchar_t* pString, int length = kAutoLength, const wchar_t* pFontName = kDefaultFontName, void* = nullptr, int = 0) = 0;

		/* 28h */	virtual void func28h(float, float, float, float, const wchar_t* str, int length, void*, void*, int) = 0;
		/* 2Ch */	virtual void func2Ch(void*) = 0;
		/* 30h */	virtual void func30h(const wchar_t*, int, int) = 0;
		/* 34h */	virtual void func34h(int, int, int) = 0;

		///
		/// Fills the specified rectangle using the current color. You must specify the top-left corner and the bottom-right corner
		/// that define the rectangle to be filled.
		/// @param x1 The top-left corner X coordinate.
		/// @param y1 The top-left corner Y coordinate.
		/// @param x2 The bottom-right corner X coordinate.
		/// @param y2 The bottom-right corner Y coordinate.
		///
		/* 38h */	virtual void FillRectangle(float x1, float y1, float x2, float y2) = 0;

		///
		/// Fills the specified quadrilater using the current color. You must specify the four corners of the quadrilater.
		/// @param topRight The coordinates of the top-right corner.
		/// @param topLeft The coordinates of the top-left corner.
		/// @param bottomLeft The coordinates of the bottom-left corner.
		/// @param bottomRight The coordinates of the bottom-right corner.
		///
		/* 3Ch */	virtual void FillQuad(Math::Point& topRight, Math::Point& topLeft, Math::Point& bottomLeft, Math::Point& bottomRight) = 0;

		///
		/// Fills the specified rectangle using an horizontal color gradient. The gradient will start with the 'colorLeft' color on
		/// the left edge, and will end with the 'colorRight' color on the right edge. The current graphics context color will be
		/// used as a tint, multiplying it with the colors specified.
		/// @param area The area of the rectangle to fill.
		/// @param colorLeft The color of the gradient beginning at the left edge of the rectangle.
		/// @param colorRight The color of the gradient end at the right edge of the rectangle.
		///
		/* 40h */	virtual void FillGradientHorizontal(const Math::Rectangle& area, Math::Color colorLeft, Math::Color colorRight) = 0;

		///
		/// Fills the specified rectangle using a vertical color gradient. The gradient will start with the 'colorTop' color on
		/// the top edge, and will end with the 'colorBottom' color on the bottom edge. The current graphics context color will be
		/// used as a tint, multiplying it with the colors specified.
		/// @param area The area of the rectangle to fill.
		/// @param colorTop The color of the gradient beginning at the top edge of the rectangle.
		/// @param colorBottom The color of the gradient end at the bottom edge of the rectangle.
		///
		/* 44h */	virtual void FillGradientVertical(const Math::Rectangle& area, Math::Color colorTop, Math::Color colorBottom) = 0;

		///
		/// Fills the specified quadrilater using a gradient. You must specify the four corners of the quadrilater, as well
		/// as the color used on each corner. The color of every pixel will be lineally-interpolated depending on its position.
		/// @param topRight The coordinates of the top-right corner.
		/// @param topRightColor The color to use on the top-right corner.
		/// @param topLeft The coordinates of the top-left corner.
		/// @param topLeftColor The color to use on the top-left corner.
		/// @param bottomLeft The coordinates of the bottom-left corner.
		/// @param bottomLeftColor The color to use on the bottom-left corner.
		/// @param bottomRight The coordinates of the bottom-right corner.
		/// @param bottomRightColor The color to use on the bottom-right corner.
		///
		/* 48h */	virtual void FillQuadGradient(
			const Math::Point& topRight, Math::Color topRightColor, 
			const Math::Point& topLeft, Math::Color topLeftColor, 
			const Math::Point& bottomLeft, Math::Color bottomLeftColor, 
			const Math::Point& bottomRight, Math::Color bottomRightColor) = 0;

		///
		/// Fills the specified triangle using a gradient. You must specify the three points of the triangle, as well
		/// as the color used on each vertex. The color of every pixel will be lineally-interpolated depending on its position.
		/// @param point1 The coordinates of the first vertex.
		/// @param color1 The color to use on the first vertex.
		/// @param point2 The coordinates of the second vertex.
		/// @param color2 The color to use on the second vertex.
		/// @param point3 The coordinates of the third vertex.
		/// @param color3 The color to use on the third vertex.
		///
		/* 4Ch */	virtual void FillTriangleGradient(
			const Math::Point& point1, Math::Color color1, 
			const Math::Point& point2, Math::Color color2, 
			const Math::Point& point3, Math::Color color3) = 0;

		/* 50h */	virtual void func50h(size_t nCount, int, const Image* pImage) = 0;
		/* 54h */	virtual void func54h(size_t nCount, int, const Image* pImage) = 0;

		///
		/// Draws the image provided, scaling it so it fills the entire area specified. 
		/// Only the portion of the image determined by the 'texCoords' rectangle (in range [0, 1]) will be used.
		/// @param area The area to fill with the image.
		/// @param pImage The image to draw. 
		/// @param texCoords The UV coordinates, in the [0, 1] range, that determines which portion of the image will be used.
		///
		/* 58h */	virtual void DrawImageScaled(const Math::Rectangle& area, const Image* pImage, const Math::Rectangle& texCoords) = 0;

		///
		/// Draws the image provided at the position specified.
		/// Only the portion of the image determined by the 'texCoords' rectangle (in range [0, 1]) will be used.
		/// @param x The X coordinate where the top-left corner of the image will be drawn.
		/// @param y The Y coordinate where the top-left corner of the image will be drawn.
		/// @param pImage The image to draw. 
		/// @param texCoords The UV coordinates, in the [0, 1] range, that determines which portion of the image will be used.
		///
		/* 5Ch */	virtual void DrawImageWithTexCoords(float x, float y, const Image* pImage, const Math::Rectangle& texCoords) = 0;

		///
		/// Draws the image provided at the position specified.
		/// @param x The X coordinate where the top-left corner of the image will be drawn.
		/// @param y The Y coordinate where the top-left corner of the image will be drawn.
		/// @param pImage The image to draw. 
		///
		/* 60h */	virtual void DrawImage(float x, float y, const Image* pImage) = 0;


		///
		/// Draws the given image into the graphics context filling the area specified. The image will be tiled until
		/// the entire area specified is filled. Only the portion of the image determined by the 'texCoords' rectangle (in range [0, 1])
		/// will be used. The scale and offset of the tiling can also be specified. The context's current color will act as a tint.
		/// @param pGraphics The Graphics2D context where the image will be drawn.
		/// @param area The area of the graphics context to fill with the image.
		/// @param texCoords The UV coordinates, in the [0, 1] range, that determines which portion of the image will be used.
		/// @param pImage The image to draw. The width and height properties of the image will be used to repeat it.
		/// @param fScaleX [Optional] The scale of the width of the image, 1.0f by default.
		/// @param fScaleY [Optional] The scale of the height of the image, 1.0f by default.
		/// @param fOffsetX [Optional] The X coordinate, relative to 'area', where the first tile will begin.
		/// @param fOffsetY [Optional] The Y coordinate, relative to 'area', where the first tile will begin.
		///
		static void DrawTiledImage(
			Graphics2D* pGraphics, const Math::Rectangle& area, const Math::Rectangle& texCoords, const Image* pImage,
			float fScaleX = 1.0f, float fScaleY = 1.0f, float fOffsetX = 0.0f, float fOffsetY = 1.0f);

		///
		/// Draws the given image into the graphics context filling the area specified. The edges of the image will be rendered
		/// repeatedly until the width/height required (depending on the edge) is filled. The center of the area will be filled
		/// repeatedly rendering the center of the image. Only the portion of the image determined by the 'texCoords' rectangle (in range [0, 1])
		/// will be used. The scale of the tiling can also be specified. The context's current color will act as a tint.
		/// @param pGraphics The Graphics2D context where the image will be drawn.
		/// @param area The area of the graphics context to fill with the image.
		/// @param texCoords The UV coordinates, in the [0, 1] range, that determines which portion of the image will be used.
		/// @param pImage The image to draw. The width and height properties of the image will be used to repeat it.
		/// @param sliceProportions The UV coordinates, in the [0, 1] range, that determine where the center of the image is. The rest will be used as edges.
		/// @param fScaleX [Optional] The scale of the width of the image, 1.0f by default.
		/// @param fScaleY [Optional] The scale of the height of the image, 1.0f by default.
		///
		static void DrawSlicedTiledImage(
			Graphics2D* pGraphics, const Math::Rectangle& area, const Math::Rectangle& texCoords, const Image* pImage, 
			const Math::Rectangle& sliceProportions, float fScaleX = 1.0f, float fScaleY = 1.0f);

		///
		/// Draws the given image into the graphics context filling the area specified. The edges of the image will be rendered
		/// stretching them until the width/height required (depending on the edge) is filled. The center of the area will be filled
		/// rendering the stretched image so it fills all the empty space. Only the portion of the image determined by the 'texCoords' rectangle (in range [0, 1])
		/// will be used. The scale of the tiling can also be specified. The context's current color will act as a tint.
		/// @param pGraphics The Graphics2D context where the image will be drawn.
		/// @param area The area of the graphics context to fill with the image.
		/// @param texCoords The UV coordinates, in the [0, 1] range, that determines which portion of the image will be used.
		/// @param pImage The image to draw. The width and height properties of the image will be used to repeat it.
		/// @param sliceProportions The UV coordinates, in the [0, 1] range, that determine where the center of the image is. The rest will be used as edges.
		/// @param fScaleX [Optional] The scale of the width of the image, 1.0f by default.
		/// @param fScaleY [Optional] The scale of the height of the image, 1.0f by default.
		///
		static void DrawSlicedStretchedImage(
			Graphics2D* pGraphics, const Math::Rectangle& area, const Math::Rectangle& texCoords, const Image* pImage,
			const Math::Rectangle& sliceProportions, float fScaleX = 1.0f, float fScaleY = 1.0f);

	private:
		// This class is not documented. Therefore, we comment the structure and make a private constructor so you can't create new ones
		///* 04h */	Graphics2DBuffer* pBuffer;

		///* 0Ch */	unsigned long color;
		///* 10h */	bool field_10;
		///* 14h */	Math::Rectangle field_14;
		///* 24h */	Graphics2DBuffer buffer;

		Graphics2D() {};
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	namespace Addresses(Graphics2D)
	{
		DeclareAddress(DrawTiledImage);
		DeclareAddress(DrawSlicedTiledImage);
		DeclareAddress(DrawSlicedStretchedImage);
	}

	// Not fully documented, so we comment it out
	//class Graphics2DBuffer
	//{
	//private:
	//	struct PointData
	//	{
	//		/* 00h */	Math::Point point;
	//		/* 08h */	unsigned long color;
	//		/* 0Ch */	Math::Point texCoords;
	//	};

	//	/* 00h */	eastl::vector<PointData, spore_allocator> pointData;
	//	int field_14;
	//	/* 18h */	PointData pointBufer[600];

	//	/* 2EF8h */	eastl::vector<void*, spore_allocator> triangleData;  // ?

	//	// not meant to be used, only for documenting
	//	/*public:
	//	METHOD_VOID(SelectAddress(0x953370, 0, 0), Graphics2DBuffer, AddPoint, Args(int arg_0, int arg_4), Args(this, arg_0, arg_4));*/
	//};

}