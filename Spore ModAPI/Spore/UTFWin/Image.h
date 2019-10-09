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
		static bool GetImage(const ResourceKey& name, Image*& dst, bool arg_8 = false, int nHeight = -1, int nWidth = -1);

		///
		/// Changes the drawable of the given window to display the specified image. Optionally, the index of the image
		/// can be specified (in the case you want to use a StdDrawable).
		/// @param pWindow The IWindow whose drawable will change.
		/// @param pImage The image that will be displayed in the window.
		/// @param nImageIndex [Optional] The index of the image, for StdDrawable.
		///
		static bool SetBackground(IWindow* pWindow, Image* pImage, int nImageIndex = 0);

		///
		/// Changes the drawable of the given window to display the specified image. Optionally, the index of the image
		/// can be specified (in the case you want to use a StdDrawable).
		///
		/// To detour this method, you must use GetAddress(Image, SetBackground_2).
		/// @param pWindow The IWindow whose drawable will change.
		/// @param imageName The ResourceKey that points to the image file that will be displayed in the window.
		/// @param nImageIndex [Optional] The index of the image, for StdDrawable.
		///
		static bool SetBackgroundByKey(IWindow* pWindow, const ResourceKey imageName, int nImageIndex = 0);
		
	protected:
		/* 04h */	intrusive_ptr<Object> mpImage;
		/* 08h */	int field_08;
		/* 0Ch */	Math::Rectangle mTexCoords;
		/* 1Ch */	Math::Dimensions mDimensions;
		/* 24h */	int field_24;
		/* 28h */	int mnRefCount;

	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(Image) == 0x2C, "sizeof(Image) must be 0x2C!");

	namespace Addresses(Image)
	{
		DeclareAddress(SetSerializer, SelectAddress(0x957A60, 0x957510, 957510));
		DeclareAddress(GetProxyID, SelectAddress(0x957A90, 0x957540, 0x957540));
		DeclareAddress(GetImage, SelectAddress(0x806870, 0x806290, 0x806320));
		DeclareAddress(SetBackground, SelectAddress(0x806F10, 0x806930, 0x8069C0));
		DeclareAddress(SetBackgroundByKey, SelectAddress(0x8081F0, 0x807C10, 0x807CA0));
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

