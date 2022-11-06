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

#include <Spore\UTFWin\SporeStdDrawableImageInfo.h>
#include <Spore\UTFWin\StdDrawable.h>

#define SporeStdDrawablePtr eastl::intrusive_ptr<UTFWin::SporeStdDrawable>

namespace UTFWin
{
	class SporeStdDrawable : public StdDrawable
	{
	public:
		static const uint32_t TYPE = 0x53EB526;

		SporeStdDrawable();
		virtual ~SporeStdDrawable();

		///
		/// Gets the image information that is being used for the state specified.
		/// @param stateIndex The index that corresponds to the desired state.
		///
		SporeStdDrawableImageInfo* GetImageInfo(int stateIndex);

		///
		/// Sets the image information that will be used for the state specified.
		/// @param pInfo The SporeStdDrawableImageInfo to use.
		/// @param stateIndex The index that corresponds to the desired state.
		/// @returns True if the index is valid, false otherwise.
		///
		bool SetImageInfo(SporeStdDrawableImageInfo* pInfo, int stateIndex);

		void SetIconImage(Image* pImage, int stateIndex);

		static bool SetWindowIcon(IWindow* pWindow, Image* pImage, int stateIndex = 0);

		virtual Vector2 GetScale() const;

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

	protected:
		/* 7Ch */	SporeStdDrawableImageInfo mCurrentInfo;
		/* 114h */	SporeStdDrawableImageInfoPtr mImageInfos[8];
		/* 134h */	bool field_134;
		/* 138h */	int field_138;
		/* 13Ch */	int field_13C;
		/* 140h */	int field_140;
		/* 144h */	Color field_144;
		/* 148h */	Math::Rectangle field_148;
		/* 158h */	Vector2 field_158;
	};

	/////////////////////////////////
	//// INTERNAL IMPLEMENTATION ////
	/////////////////////////////////

	static_assert(sizeof(SporeStdDrawable) == 0x160, "sizeof(SporeStdDrawable) != 160h");

	namespace Addresses(SporeStdDrawable)
	{
		DeclareAddress(Paint);
		DeclareAddress(IsColliding);
		DeclareAddress(GetDimensions);
		DeclareAddress(UseCollision);
		DeclareAddress(GetScale);

		DeclareAddress(SetSerializer);
		DeclareAddress(GetProxyID);
	}

	inline SporeStdDrawableImageInfo* SporeStdDrawable::GetImageInfo(int stateIndex)
	{
		if (stateIndex > 7) return &mCurrentInfo;

		SporeStdDrawableImageInfo* ptr = mImageInfos[stateIndex].get();
		if (!mImageInfos[stateIndex]) {
			mImageInfos[stateIndex] = &mCurrentInfo;
		}

		return mImageInfos[stateIndex].get();
	}
	inline bool SporeStdDrawable::SetImageInfo(SporeStdDrawableImageInfo* pInfo, int stateIndex)
	{
		if (stateIndex > 7) return false;

		mImageInfos[stateIndex] = pInfo;

		return true;
	}
}
