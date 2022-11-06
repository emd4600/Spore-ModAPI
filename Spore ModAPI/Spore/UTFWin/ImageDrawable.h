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


#include <Spore\UTFWin\OutlineFormat.h>
#include <Spore\UTFWin\IDrawable.h>
#include <Spore\UTFWin\ILayoutElement.h>
#include <Spore\UTFWin\Image.h>

#define IImageDrawablePtr eastl::intrusive_ptr<UTFWin::IImageDrawable>
#define ImageDrawablePtr eastl::intrusive_ptr<UTFWin::ImageDrawable>

namespace UTFWin
{
	///
	/// An enumeration used by ImageDrawable, that determine how the image is tiled.
	///
	enum class ImageTiling
	{
		/// No tiling is used.
		None = 0,
		/// The entire image is tiled to fill the space.
		Standard = 1,
		/// Draws the edges (whcih are considered 1/3 of the space) normally and tiles the rest of the image until it fills all the space.
		Edge = 2
	};

	///
	/// An abstract class that has the methods that a drawable that renders an image would require.
	///
	class IImageDrawable : public UTFWinObject
	{
	public:
		enum
		{
			/// Preserves the original width of the image
			kFlagFixedWidth = 1,
			/// Preserves the original height of the image.
			kFlagFixedHeight = 2
		};

		///
		/// Get the IDrawable instance that represents this class.
		///
		/* 10h */	virtual IDrawable* ToDrawable() = 0;

		///
		/// Sets the image to be shown.
		/// @param pImage The image that will be used by this drawable.
		///
		/* 14h */	virtual void SetImage(Image* pImage) = 0;

		///
		/// Gets the image to be shown.
		///
		/* 18h */	virtual Image* GetImage() const = 0;

		///
		/// Gets the flags used in this drawable. The flags are the AbstractImageDrawable::kFlag... values.
		///
		/* 1Ch */	virtual int GetImageDrawableFlags() const = 0;

		///
		/// Sets the flags used in this drawable. The flags are the AbstractImageDrawable::kFlag... values.
		/// @param flags The new flags value.
		///
		/* 20h */	virtual void SetImageDrawableFlags(int flags) = 0;

		///
		/// Sets the specific drawable flag to the value given. The possible flags are the AbstractImageDrawable::kFlag... values.
		/// @param flag The flag to set.
		/// @param bValue The new bool value of the flag.
		///
		/* 24h */	virtual void SetImageDrawableFlag(int flag, bool bValue) = 0;
		
		///
		/// Sets the tiling method that will be used in this drawable.
		/// @param tiling ImageTiling The tiling to use, in the ImageTiling enum.
		///
		/* 28h */	virtual void SetTiling(ImageTiling tiling) = 0;
		
		///
		/// Gets the tiling method that is being used in this drawable.
		///
		/* 2Ch */	virtual ImageTiling GetTiling() const = 0;
		
		///
		/// Sets the scale of the image.
		/// @param fScale The new scale value.
		///
		/* 30h */	virtual void SetScale(float fScale) = 0;
		
		///
		/// Gets the scale of the image, as a float value.
		///
		/* 34h */	virtual float GetScale() const = 0;
		
		///
		/// Sets the horizontal alignment of the image.
		/// @param alignment The new alignment value, in the enum AlignmentH.
		///
		/* 38h */	virtual void SetAlignmentHorizontal(AlignmentH alignment) = 0;

		///
		/// Gets the horizontal alignment of the image.
		///
		/* 3Ch */	virtual AlignmentH GetAlignmentHorizontal() const = 0;

		///
		/// Sets the vertical alignment of the image.
		/// @param alignment The new alignment value, in the enum AlignmentV.
		///
		/* 40h */	virtual void SetAlignmentVertical(AlignmentV alignment) = 0;
		
		///
		/// Gets the vertical alignment of the image.
		///
		/* 44h */	virtual AlignmentV GetAlignmentVertical() const = 0;


		///
		/// Creates an IWindow that will display the image with the name specified.
		/// @param imageName The ResourceKey of the image to display.
		/// @param offsetX The X coordinate of the newly generated window, relative to its parent.
		/// @param offsetY The Y coordinate of the newly generated window, relative to its parent.
		/// @param pParentWindow The IWindow that will be the parent of the created window.
		/// @returns The newly created window.
		///
		static IWindow* AddImageWindow(const ResourceKey& imageName, float offsetX, float offsetY, IWindow* pParentWindow);

		static const uint32_t TYPE = 0xEF3C47CF;
	};

	///
	/// A standard IDrawable that renders an image.
	///
	class ImageDrawable : public IDrawable, public DefaultLayoutElement, public IImageDrawable
	{
	public:
		ImageDrawable();
		virtual ~ImageDrawable();

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
		virtual void SetImage(Image* pImage) override;
		virtual Image* GetImage() const override;
		virtual int GetImageDrawableFlags() const override;
		virtual void SetImageDrawableFlags(int flags) override;
		virtual void SetImageDrawableFlag(int flag, bool bValue) override;
		virtual void SetTiling(ImageTiling tiling) override;
		virtual ImageTiling GetTiling() const override;
		virtual void SetScale(float fScale) override;
		virtual float GetScale() const override;
		virtual void SetAlignmentHorizontal(AlignmentH alignment) override;
		virtual AlignmentH GetAlignmentHorizontal() const override;
		virtual void SetAlignmentVertical(AlignmentV alignment) override;
		virtual AlignmentV GetAlignmentVertical() const override;

	protected:

		/* 10h */	float mfScale;
		/* 14h */	int mnFlags;
		/* 18h */	ImageTiling mTiling;
		/* 1Ch */	AlignmentH mAlignmentHorizontal;
		/* 20h */	AlignmentV mAlignmentVertical;
		/* 24h */	intrusive_ptr<Image> mpImage;
		/* 28h */	OutlineFormat mImageOutline;

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(ImageDrawable) == 0x50, "sizeof(ImageDrawable) must be 50h");

	namespace Addresses(ImageDrawable)
	{
		DeclareAddress(Paint);
		DeclareAddress(IsColliding);
		DeclareAddress(GetDimensions);
		DeclareAddress(UseCollision);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);

		DeclareAddress(ToDrawable);
		DeclareAddress(SetImage);
		DeclareAddress(GetImage);
		DeclareAddress(GetImageDrawableFlags);
		DeclareAddress(SetImageDrawableFlags);
		DeclareAddress(SetImageDrawableFlag);
		DeclareAddress(SetTiling);
		DeclareAddress(GetTiling);
		DeclareAddress(SetScale);
		DeclareAddress(GetScale);
		DeclareAddress(SetAlignmentHorizontal);
		DeclareAddress(GetAlignmentHorizontal);
		DeclareAddress(SetAlignmentVertical);
		DeclareAddress(GetAlignmentVertical);
	}

	namespace Addresses(IImageDrawable)
	{
		DeclareAddress(AddImageWindow);
	}

	inline ImageDrawable::ImageDrawable()
		: mfScale(1.0f)
		, mnFlags()
		, mTiling(ImageTiling::None)
		, mAlignmentHorizontal(AlignmentH::Center)
		, mAlignmentVertical(AlignmentV::Middle)
		, mpImage(nullptr)
		, mImageOutline()
	{
		mImageOutline.SetStrength(2);
	}

	inline ImageDrawable::~ImageDrawable() {}
}
