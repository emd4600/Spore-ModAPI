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
#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\Image.h>

#define IDialogDrawablePtr eastl::intrusive_ptr<UTFWin::IDialogDrawable>

namespace UTFWin
{
	enum class BackgroundTiling : uint32_t
	{
		/// Stretches background image.
		Stretch = 0,
		/// Tiles image.
		Tile = 1,
		/// Stretches center of image and tiles edges,
		CenterStretch = 2,
		/// Tiles center and edges.
		CenterTile = 3
	};

	///
	/// An abstract class that has the methods that a drawable for a dialog would require.
	///
	class IDialogDrawable : public UTFWinObject
	{
	public:
		enum Indices
		{
			kImageBackground = 0,
			kImageTitleBar = 1,
			kImageBorderLeft = 2,
			kImageBorderRight = 3,
			kImageBorderTop = 4,
			kImageBorderBottom = 5,
			kImageBorderTopLeft = 6,
			kImageBorderTopRight = 7,
			kImageBorderBottomLeft = 8,
			kImageBorderBottomRight = 9
		};

		///
		/// Get the IDrawable instance that represents this class.
		///
		virtual IDrawable* ToDrawable() = 0;

		///
		/// Set the images used by this drawable. The index is one of the AbstractDialogDrawable::kImage... values.
		/// @param index The index of the image to set.
		/// @param pImage The image.
		///
		/* 14h */	virtual void SetImage(int index, Image* image) = 0;

		///
		/// Gets the color used to fill the background.
		/// @param dst The Color where the value will be set.
		/// @returns The background fill color.
		///
		/* 18h */	virtual Color GetBackgroundColor(Color& dst) const = 0;

		///
		/// Sets the color used to fill the background.
		/// @param color The new Color value.
		/// @returns The background fill color.
		///
		/* 1Ch */	virtual void SetBackgroundColor(Color color) = 0;

		///
		/// Gets the tiling mode used to fill the background.
		/// @param dst The BackgroundTiling where the value will be set.
		/// @returns The background tiling mode.
		///
		/* 20h */	virtual BackgroundTiling GetBackgroundTiling(BackgroundTiling& dst) const = 0;

		///
		/// Sets the color used to fill the background.
		/// @param value The new tiling value, from the BackgroundTiling enum.
		/// @returns The background tiling mode.
		///
		/* 24h */	virtual void SetBackgroundTiling(BackgroundTiling value) = 0;
	};

	///
	/// The standard IDrawable for a dialog component.
	///
	class DialogDrawable : public IDrawable, public DefaultLayoutElement, public IDialogDrawable
	{
	public:
		static const uint32_t TYPE = 0x6F0C6FF6;

		DialogDrawable();
		virtual ~DialogDrawable();

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
		virtual void SetImage(int index, Image* image) override;
		virtual Color GetBackgroundColor(Color& dst) const override;
		virtual void SetBackgroundColor(Color color) override;
		virtual BackgroundTiling GetBackgroundTiling(BackgroundTiling& dst) const override;
		virtual void SetBackgroundTiling(BackgroundTiling value) override;


	protected:
		/* 10h */	Color mBackgroundFillColor;
		/* 14h */	BackgroundTiling mBackgroundTiling;
		/* 18h */	ImagePtr mpImages[10];
	};
	ASSERT_SIZE(DialogDrawable, 0x40);

	namespace Addresses(DialogDrawable)
	{
		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(Paint);
		DeclareAddress(IsColliding);
		DeclareAddress(GetDimensions);
		DeclareAddress(UseCollision);

		DeclareAddress(ToDrawable);
		DeclareAddress(SetImage);
		DeclareAddress(GetBackgroundColor);
		DeclareAddress(SetBackgroundColor);
		DeclareAddress(GetBackgroundTiling);
		DeclareAddress(SetBackgroundTiling);
	}

	inline DialogDrawable::DialogDrawable()
		: mBackgroundFillColor(0xFF7F7F7F)
		, mBackgroundTiling()
		, mpImages{}
	{

	}

	inline DialogDrawable::~DialogDrawable() {}
}