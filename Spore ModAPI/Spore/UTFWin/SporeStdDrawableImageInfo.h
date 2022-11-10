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
#include <Spore\UTFWin\Image.h>
#include <Spore\UTFWin\OutlineFormat.h>
#include <Spore\MathUtils.h>
#include <Spore\Object.h>

#define SporeStdDrawableImageInfoPtr eastl::intrusive_ptr<UTFWin::SporeStdDrawableImageInfo>

using namespace Math;

namespace UTFWin
{
	enum class IconDrawModes : uint32_t
	{
		ImageSize = 0,
		WindowSize = 1
	};

	enum class ShadowModes : uint32_t
	{
		/// Don't use shadows.
		None = 0,
		/// Use shadows for both the background and the icon.
		Full = 1,
		/// Only use shadows for the background.
		Background = 2,
		/// Only use shadows for the icon.
		Icon = 3,
	};

	///
	/// A structure that represents an state of a SporeStdDrawable.
	///
	class SporeStdDrawableImageInfo : public ILayoutElement, public DefaultRefCounted
	{
	public:
		static const uint32_t TYPE = 0x5400186;

		SporeStdDrawableImageInfo();
		SporeStdDrawableImageInfo(const SporeStdDrawableImageInfo& other);
		virtual ~SporeStdDrawableImageInfo();

		Image* GetBackgroundImage() const;
		void SetBackgroundImage(Image* pImage);

		Image* GetIconImage() const;
		void SetIconImage(Image* pImage);

		Color GetBackgroundColor() const;
		void SetBackgroundColor(Color color);

		Color GetIconColor() const;
		void SetIconColor(Color color);

		IconDrawModes GetIconDrawMode() const;
		void SetIconDrawMode(IconDrawModes mode);

		ShadowModes GetStrokeMode() const;
		void SetStrokeMode(ShadowModes mode);

		ShadowModes GetHaloMode() const;
		void SetHaloMode(ShadowModes mode);

		const Vector2& GetBackgroundScale() const;
		void SetBackgroundScale(const Vector2& value);

		const Vector2& GetBackgroundOffset() const;
		void SetBackgroundOffset(const Vector2& value);

		const Vector2& GetIconScale() const;
		void SetIconScale(const Vector2& value);

		const Vector2& GetIconOffset() const;
		void SetIconOffset(const Vector2& value);

		const OutlineFormat& GetStrokeShadow() const;
		void SetStrokeShadow(const OutlineFormat& value);

		const OutlineFormat& GetHaloShadow() const;
		void SetHaloShadow(const OutlineFormat& value);

		virtual bool func18h(int) { return true; }
		virtual bool func1Ch(int) { return true; }

		//// OVERRIDES ////

		virtual int AddRef() override;
		virtual int Release() override;
		virtual void* Cast(uint32_t type) const override;

		virtual void SetSerializer(Serializer& dst) override;
		virtual uint32_t GetProxyID() const override;

	protected:
		/* 0Ch */	ImagePtr mpBackgroundImage;
		/* 10h */	ImagePtr mpIconImage;
		/* 14h */	Color mBackgroundColor;
		/* 18h */	Color mIconColor;
		/* 1Ch */	IconDrawModes mIconDrawMode;
		/* 20h */	ShadowModes mStrokeMode;
		/* 24h */	ShadowModes mHaloMode;
		/* 28h */	Vector2 mBackgroundScale;
		/* 30h */	Vector2 mBackgroundOffset;
		/* 38h */	Vector2 mIconScale;
		/* 40h */	Vector2 mIconOffset;
		/* 48h */	OutlineFormat mStrokeShadow;
		/* 70h */	OutlineFormat mHaloShadow;
	};
	ASSERT_SIZE(SporeStdDrawableImageInfo, 0x98);

	namespace Addresses(SporeStdDrawableImageInfo)
	{
		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);
	}

	inline Image* SporeStdDrawableImageInfo::GetBackgroundImage() const { return mpBackgroundImage.get(); }
	inline void SporeStdDrawableImageInfo::SetBackgroundImage(Image* pImage) { mpBackgroundImage = pImage; }

	inline Image* SporeStdDrawableImageInfo::GetIconImage() const { return mpIconImage.get(); }
	inline void SporeStdDrawableImageInfo::SetIconImage(Image* pImage) { mpIconImage = pImage; }

	inline Color SporeStdDrawableImageInfo::GetBackgroundColor() const { return mBackgroundColor; }
	inline void SporeStdDrawableImageInfo::SetBackgroundColor(Color color) { mBackgroundColor = color; }

	inline Color SporeStdDrawableImageInfo::GetIconColor() const { return mIconColor; }
	inline void SporeStdDrawableImageInfo::SetIconColor(Color color) { mIconColor = color; }

	inline IconDrawModes SporeStdDrawableImageInfo::GetIconDrawMode() const { return mIconDrawMode; }
	inline void SporeStdDrawableImageInfo::SetIconDrawMode(IconDrawModes mode) { mIconDrawMode = mode; }

	inline ShadowModes SporeStdDrawableImageInfo::GetStrokeMode() const { return mStrokeMode; }
	inline void SporeStdDrawableImageInfo::SetStrokeMode(ShadowModes mode) { mStrokeMode = mode; }

	inline ShadowModes SporeStdDrawableImageInfo::GetHaloMode() const { return mHaloMode; }
	inline void SporeStdDrawableImageInfo::SetHaloMode(ShadowModes mode) { mHaloMode = mode; }

	inline const Vector2& SporeStdDrawableImageInfo::GetBackgroundScale() const { return mBackgroundScale; }
	inline void SporeStdDrawableImageInfo::SetBackgroundScale(const Vector2& value) { mBackgroundScale = value; }

	inline const Vector2& SporeStdDrawableImageInfo::GetBackgroundOffset() const { return mBackgroundOffset; }
	inline void SporeStdDrawableImageInfo::SetBackgroundOffset(const Vector2& value) { mBackgroundOffset = value; }

	inline const Vector2& SporeStdDrawableImageInfo::GetIconScale() const { return mIconScale; }
	inline void SporeStdDrawableImageInfo::SetIconScale(const Vector2& value) { mIconScale = value; }

	inline const Vector2& SporeStdDrawableImageInfo::GetIconOffset() const { return mIconOffset; }
	inline void SporeStdDrawableImageInfo::SetIconOffset(const Vector2& value) { mIconOffset = value; }

	inline const OutlineFormat& SporeStdDrawableImageInfo::GetStrokeShadow() const { return mStrokeShadow; }
	inline void SporeStdDrawableImageInfo::SetStrokeShadow(const OutlineFormat& value) { mHaloShadow = value; }

	inline const OutlineFormat& SporeStdDrawableImageInfo::GetHaloShadow() const { return mHaloShadow; }
	inline void SporeStdDrawableImageInfo::SetHaloShadow(const OutlineFormat& value) { mHaloShadow = value; }
}