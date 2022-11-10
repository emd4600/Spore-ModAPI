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
#include <Spore\Object.h>
#include <Spore\MathUtils.h>
#include <Spore\ResourceKey.h>

#define ImagePtr eastl::intrusive_ptr<UTFWin::Image>

namespace UTFWin
{
	class IWindow;

	///
	/// A layout element that represents an image. This class might only represent a portion of the entire image file,
	/// since it can use UV coordinates.
	/// 
	class Image : public ILayoutElement
	{
	public:
		enum
		{
			kTypePNG = 0x2F7D0004
		};
		static const uint32_t TYPE = 0x1BE6AB3;
		static const uint32_t TYPE_DIMENSIONS = 0x2F84737;

		Image();
		virtual ~Image();

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;


		const Math::Rectangle& GetTexCoords() const;
		const Math::Dimensions& GetDimensions() const;

		///
		/// Creates an UTFWin::Image instance with the image extracted from the file specified.
		///
		static bool GetImage(const ResourceKey& name, ImagePtr& dst, bool arg_8 = false, int height = -1, int width = -1);

		///
		/// Changes the drawable of the given window to display the specified image. Optionally, the index of the image
		/// can be specified (in the case you want to use a StdDrawable).
		/// 
		/// The method will try to use the existing drawable of the window; if there's no drawable or it's not an StdDrawable or
		/// an ImageDrawable, one will be created; by default an ImageDrawable will be created, unless an image index is specified.
		/// 
		/// @param pWindow The IWindow whose drawable will change.
		/// @param pImage The image that will be displayed in the window.
		/// @param nImageIndex [Optional] The index of the image, for StdDrawable.
		///
		static bool SetBackground(IWindow* pWindow, Image* pImage, int imageIndex = -1);

		///
		/// Changes the drawable of the given window to display the specified image. Optionally, the index of the image
		/// can be specified (in the case you want to use a StdDrawable).
		/// 
		/// The method will try to use the existing drawable of the window; if there's no drawable or it's not an StdDrawable or
		/// an ImageDrawable, one will be created; by default an ImageDrawable will be created, unless an image index is specified.
		///
		/// To detour this method, you must use GetAddress(Image, SetBackground_2).
		/// 
		/// @param pWindow The IWindow whose drawable will change.
		/// @param imageName The ResourceKey that points to the image file that will be displayed in the window.
		/// @param nImageIndex [Optional] The index of the image, for StdDrawable.
		///
		static bool SetBackgroundByKey(IWindow* pWindow, const ResourceKey& imageName, int imageIndex = -1);
		
	protected:
		/* 04h */	ObjectPtr mpImage;
		/* 08h */	int field_08;
		/* 0Ch */	Math::Rectangle mTexCoords;
		/* 1Ch */	Math::Dimensions mDimensions;
		/* 24h */	int field_24;
		/* 28h */	int mnRefCount;

	};
	ASSERT_SIZE(Image, 0x2C);

	namespace Addresses(Image)
	{
		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);
		DeclareAddress(GetImage);
		DeclareAddress(SetBackground);
		DeclareAddress(SetBackgroundByKey);
	}

	inline Image::Image()
		: mpImage(nullptr), mnRefCount(0)
	{
	}
	inline Image::~Image()
	{
	}

	inline const Math::Rectangle& Image::GetTexCoords() const
	{
		return mTexCoords;
	}
	inline const Math::Dimensions& Image::GetDimensions() const
	{
		return mDimensions;
	}
}

