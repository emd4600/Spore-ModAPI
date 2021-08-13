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

#include <Spore\UTFWin\ComboBoxDrawable.h>
#include <Spore\UTFWin\ImageDrawable.h>
#include <Spore\UTFWin\ScrollbarDrawable.h>
#include <Spore\UTFWin\SliderDrawable.h>
#include <Spore\UTFWin\SpinnerDrawable.h>
#include <Spore\UTFWin\DialogDrawable.h>
#include <Spore\UTFWin\ButtonDrawableStandard.h>
#include <Spore\UTFWin\ButtonDrawableRadio.h>
#include <Spore\UTFWin\FrameDrawable.h>
#include <Spore\UTFWin\VariableWidthDrawable.h>
#include <Spore\UTFWin\StdDrawable.h>
#include <Spore\UTFWin\SporeStdDrawableImageInfo.h>
#include <Spore\UTFWin\SporeStdDrawable.h>
#include <Spore\UTFWin\IWindow.h>
#include <Spore\App\IClassManager.h>

#include <SourceCode\Utility.h>

namespace UTFWin
{
	//// ImageDrawable ////

	auto_STATIC_METHOD(IImageDrawable, IWindow*, AddImageWindow,
		Args(const ResourceKey& imageName, float offsetX, float offsetY, IWindow* parentWindow),
		Args(imageName, offsetX, offsetY, parentWindow));

	DEFAULT_REFCOUNT(ImageDrawable);

	auto_METHOD_VIRTUAL_VOID(ImageDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ImageDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(ImageDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(ImageDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));

	auto_METHOD_VIRTUAL_(ImageDrawable, IImageDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetImage, Args(Image* pImage), Args(pImage));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, Image*, GetImage);
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, int, GetImageDrawableFlags);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetImageDrawableFlags, Args(int flags), Args(flags));
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetImageDrawableFlag, Args(int flag, bool bValue), Args(flag, bValue));
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetTiling, Args(ImageTiling tiling), Args(tiling));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, ImageTiling, GetTiling);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetScale, Args(float fScale), Args(fScale));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, float, GetScale);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetAlignmentHorizontal, Args(AlignmentH alignment), Args(alignment));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, AlignmentH, GetAlignmentHorizontal);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetAlignmentVertical, Args(AlignmentV alignment), Args(alignment));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, AlignmentV, GetAlignmentVertical);


	void* ImageDrawable::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == IImageDrawable::TYPE)
		{
			return (IImageDrawable*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}

	//// StdDrawable ////

	DEFAULT_REFCOUNT(StdDrawable);

	auto_METHOD_VIRTUAL_VOID(StdDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(StdDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(StdDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(StdDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(StdDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(StdDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));

	auto_METHOD_VIRTUAL_const(StdDrawable, IStdDrawable, Image*, GetImage, Args(StateIndices index), Args(index));
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetImage, Args(StateIndices index, Image* pImage), Args(index, pImage));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, Scaling, GetScaleType);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetScaleType, Args(Scaling value), Args(value));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, const Math::Rectangle&, GetScaleArea);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetScaleArea, Args(const Math::Rectangle& value), Args(value));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, const Vector2&, GetScaleFactor);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetScaleFactor, Args(Vector2& value), Args(value));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, Object*, GetHitMask);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetHitMask, Args(Object* pHitMask), Args(pHitMask));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, float, GetHitFactor);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetHitFactor, Args(float value), Args(value));

	void* StdDrawable::Cast(uint32_t type) const {
		if (type == IStdDrawable::TYPE)
		{
			return (IStdDrawable*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}


	//// ComboBoxDrawable ////

	DEFAULT_REFCOUNT(ComboBoxDrawable);

	auto_METHOD_VIRTUAL_VOID(ComboBoxDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(ComboBoxDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ComboBoxDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ComboBoxDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(ComboBoxDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(ComboBoxDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));

	auto_METHOD_VIRTUAL_const(ComboBoxDrawable, ComboBoxDrawable, Image*, GetImage, Args(int index), Args(index));

	auto_METHOD_VIRTUAL_(ComboBoxDrawable, IComboBoxDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ComboBoxDrawable, IComboBoxDrawable, SetImage, Args(int index, Image* pImage), Args(index, pImage));

	void* ComboBoxDrawable::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == IComboBoxDrawable::TYPE)
		{
			return (IComboBoxDrawable*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}

	//// ScrollbarDrawable ////

	DEFAULT_REFCOUNT(ScrollbarDrawable);

	auto_METHOD_VIRTUAL_VOID(ScrollbarDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(ScrollbarDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ScrollbarDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ScrollbarDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(ScrollbarDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(ScrollbarDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));

	auto_METHOD_VIRTUAL_(ScrollbarDrawable, IScrollbarDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ScrollbarDrawable, IScrollbarDrawable, SetImage, Args(int index, Image* pImage), Args(index, pImage));

	void* ScrollbarDrawable::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == IScrollbarDrawable::TYPE)
		{
			return (IScrollbarDrawable*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}

	//// SliderDrawable ////

	DEFAULT_REFCOUNT(SliderDrawable);

	auto_METHOD_VIRTUAL_VOID(SliderDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(SliderDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(SliderDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(SliderDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(SliderDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(SliderDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));

	auto_METHOD_VIRTUAL_(SliderDrawable, ISliderDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(SliderDrawable, ISliderDrawable, SetImage, Args(int index, Image* pImage), Args(index, pImage));

	void* SliderDrawable::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == ISliderDrawable::TYPE)
		{
			return (ISliderDrawable*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}

	//// SpinnerDrawable ////

	DEFAULT_REFCOUNT(SpinnerDrawable);

	auto_METHOD_VIRTUAL_VOID(SpinnerDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(SpinnerDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(SpinnerDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(SpinnerDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(SpinnerDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(SpinnerDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));

	auto_METHOD_VIRTUAL_(SpinnerDrawable, ISpinnerDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(SpinnerDrawable, ISpinnerDrawable, SetImage, Args(int index, Image* pImage), Args(index, pImage));

	void* SpinnerDrawable::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == ISpinnerDrawable::TYPE)
		{
			return (ISpinnerDrawable*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}

	//// DialogDrawable ////

	DEFAULT_REFCOUNT(DialogDrawable);

	auto_METHOD_VIRTUAL_VOID(DialogDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(DialogDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(DialogDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(DialogDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(DialogDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(DialogDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));

	auto_METHOD_VIRTUAL_(DialogDrawable, IDialogDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(DialogDrawable, IDialogDrawable, SetImage, Args(int index, Image* image), Args(index, image));
	auto_METHOD_VIRTUAL_const(DialogDrawable, IDialogDrawable, Color, GetBackgroundColor, Args(Color& dst), Args(dst));
	auto_METHOD_VIRTUAL_VOID(DialogDrawable, IDialogDrawable, SetBackgroundColor, Args(Color color), Args(color));
	auto_METHOD_VIRTUAL_const(DialogDrawable, IDialogDrawable, BackgroundTiling, GetBackgroundTiling, Args(BackgroundTiling& dst), Args(dst));
	auto_METHOD_VIRTUAL_VOID(DialogDrawable, IDialogDrawable, SetBackgroundTiling, Args(BackgroundTiling value), Args(value));


	void* DialogDrawable::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == DialogDrawable::TYPE)
		{
			return (DialogDrawable*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}

	//// ButtonDrawableStandard ////

	DEFAULT_REFCOUNT(ButtonDrawableStandard);

	auto_METHOD_VIRTUAL_VOID(ButtonDrawableStandard, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(ButtonDrawableStandard, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ButtonDrawableStandard, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ButtonDrawableStandard, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(ButtonDrawableStandard, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(ButtonDrawableStandard, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));
	auto_METHOD_VIRTUAL_const(ButtonDrawableStandard, IDrawable, bool, GetTexCoords, Args(int state, Math::Rectangle& dst), Args(state, dst));

	auto_METHOD_VIRTUAL_(ButtonDrawableStandard, IButtonDrawableStandard, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ButtonDrawableStandard, IButtonDrawableStandard, SetImage, Args(Image* image, bool bTileable), Args(image, bTileable));


	void* ButtonDrawableStandard::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == IButtonDrawableStandard::TYPE)
		{
			return (IButtonDrawableStandard*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}

	//// ButtonDrawableRadio ////

	DEFAULT_REFCOUNT(ButtonDrawableRadio);

	auto_METHOD_VIRTUAL_VOID(ButtonDrawableRadio, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(ButtonDrawableRadio, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ButtonDrawableRadio, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ButtonDrawableRadio, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(ButtonDrawableRadio, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(ButtonDrawableRadio, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));
	auto_METHOD_VIRTUAL_const(ButtonDrawableRadio, IDrawable, bool, GetTexCoords, Args(int state, Math::Rectangle& dst), Args(state, dst));

	auto_METHOD_VIRTUAL_(ButtonDrawableRadio, IButtonDrawableRadio, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ButtonDrawableRadio, IButtonDrawableRadio, SetImage, Args(Image* image, bool bTileable), Args(image, bTileable));


	void* ButtonDrawableRadio::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == IButtonDrawableRadio::TYPE)
		{
			return (IButtonDrawableRadio*) this;
		}
		else 
		{
			return IDrawable::Cast(type);
		}
	}

	//// FrameDrawable ////

	DEFAULT_REFCOUNT(FrameDrawable);

	auto_METHOD_VIRTUAL_VOID(FrameDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(FrameDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(FrameDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(FrameDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(FrameDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(FrameDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));


	void* FrameDrawable::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == FrameDrawable::TYPE)
		{
			return (FrameDrawable*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}


	//// VariableWidthDrawable ////

	DEFAULT_REFCOUNT(VariableWidthDrawable);

	auto_METHOD_VIRTUAL_VOID(VariableWidthDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(VariableWidthDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(VariableWidthDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(VariableWidthDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(VariableWidthDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(VariableWidthDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));


	void* VariableWidthDrawable::Cast(uint32_t type) const {
		if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else
		{
			return IDrawable::Cast(type);
		}
	}

	VariableWidthDrawable& VariableWidthDrawable::ToDrawable()
	{
		return *this;
	}


	//// SporeStdDrawableImageInfo ////

	DEFAULT_REFCOUNT(SporeStdDrawableImageInfo);

	auto_METHOD_VIRTUAL_VOID(SporeStdDrawableImageInfo, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(SporeStdDrawableImageInfo, ILayoutElement, uint32_t, GetProxyID);

	SporeStdDrawableImageInfo::SporeStdDrawableImageInfo()
		: mpBackgroundImage(nullptr)
		, mpIconImage(nullptr)
		, mBackgroundColor(Color::WHITE)
		, mIconColor(Color::WHITE)
		, mIconDrawMode(IconDrawModes::WindowSize)
		, mStrokeMode(ShadowModes::Full)
		, mHaloMode(ShadowModes::Full)
		, mStrokeShadow()
		, mHaloShadow()
		, mBackgroundScale(1.0f, 1.0f)
		, mIconScale(1.0f, 1.0f)
		, mBackgroundOffset()
		, mIconOffset()
	{
		mStrokeShadow.SetStrength(2);
		mHaloShadow.SetStrength(2);
	}

	SporeStdDrawableImageInfo::SporeStdDrawableImageInfo(const SporeStdDrawableImageInfo& other)
		: mpBackgroundImage(other.mpBackgroundImage)
		, mpIconImage(other.mpIconImage)
		, mBackgroundColor(other.mBackgroundColor)
		, mIconColor(other.mIconColor)
		, mIconDrawMode(other.mIconDrawMode)
		, mStrokeMode(other.mStrokeMode)
		, mHaloMode(other.mHaloMode)
		, mStrokeShadow(other.mStrokeShadow)
		, mHaloShadow(other.mHaloShadow)
		, mBackgroundScale(other.mBackgroundScale)
		, mIconScale(other.mIconScale)
		, mBackgroundOffset(other.mBackgroundOffset)
		, mIconOffset(other.mIconOffset)
	{
	}

	SporeStdDrawableImageInfo::~SporeStdDrawableImageInfo()
	{

	}

	void* SporeStdDrawableImageInfo::Cast(uint32_t type) const {
		if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == SporeStdDrawableImageInfo::TYPE || type == 0xAE9CB0FA)
		{
			return (SporeStdDrawableImageInfo*) this;
		}
		else
		{
			return nullptr;
		}
	}


	//// SporeStdDrawable ////

	DEFAULT_REFCOUNT(SporeStdDrawable);

	auto_METHOD_VIRTUAL_VOID(SporeStdDrawable, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(SporeStdDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(SporeStdDrawable, IDrawable, Paint, Args(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), Args(pRenderer, area, params));
	auto_METHOD_VIRTUAL(SporeStdDrawable, IDrawable, bool, IsColliding, Args(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), Args(area, point, params));
	auto_METHOD_VIRTUAL(SporeStdDrawable, IDrawable, bool, GetDimensions, Args(Dimensions& dst, int state, int index), Args(dst, state, index));
	auto_METHOD_VIRTUAL(SporeStdDrawable, IDrawable, bool, UseCollision, Args(uint32_t type, bool& dst), Args(type, dst));
	auto_METHOD_VIRTUAL_const_(SporeStdDrawable, IDrawable, Vector2, GetScale);

	SporeStdDrawable::SporeStdDrawable()
		: mCurrentInfo()
		, mImageInfos{}
		, field_134(false)
		, field_138()
		, field_13C()
		, field_140()
		, field_144(Color::WHITE)
		, field_148()
		, field_158(1.0f, 1.0f)
	{
		mCurrentInfo.AddRef();
	}
	SporeStdDrawable::~SporeStdDrawable() 
	{
		for (int i = 0; i < 8; ++i)
		{
			mImageInfos[i]->SetBackgroundImage(nullptr);
			mImageInfos[i]->SetIconImage(nullptr);
		}
	}

	void* SporeStdDrawable::Cast(uint32_t type) const {
		if (type == SporeStdDrawable::TYPE)
		{
			return (SporeStdDrawable*) this;
		}
		else
		{
			return StdDrawable::Cast(type);
		}
	}


	void* IDrawable::Cast(uint32_t type) const
	{
		if (type == IDrawable::TYPE)
		{
			return (IDrawable*) this;
		}
		else if (type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == Object::TYPE)
		{
			return (Object*) this;
		}
		else
		{
			return nullptr;
		}
	}

	void SporeStdDrawable::SetIconImage(Image* pImage, int stateIndex)
	{
		auto info = GetImageInfo(stateIndex);
		if (stateIndex < 8 && info != &mCurrentInfo) 
		{
			mImageInfos[stateIndex] = info = (SporeStdDrawableImageInfo*)ClassManager.CreateCasted(0x540037E, SporeStdDrawableImageInfo::TYPE);
			*mImageInfos[stateIndex] = SporeStdDrawableImageInfo(mCurrentInfo);
		}
		info->SetIconImage(pImage);

		if (field_134 || stateIndex == 8) {
			field_134 = true;
		}
		else field_134 = false;

		if (!field_134) {
			if (!mImageInfos[0]) {
				mImageInfos[0] = &mCurrentInfo;
			}
			mCurrentInfo = SporeStdDrawableImageInfo(*mImageInfos[0]);
		}
	}

	bool SporeStdDrawable::SetWindowIcon(IWindow* pWindow, Image* pImage, int stateIndex)
	{
		if (!pWindow) return false;
		auto drawable = pWindow->GetDrawable();
		if (!drawable) return false;
		auto stdDrawable = object_cast<SporeStdDrawable>(drawable);
		if (!stdDrawable) return false;

		stateIndex = Math::clamp(stateIndex, 0, 7);
		if (stdDrawable->GetImageInfo(stateIndex)->GetIconImage() != pImage)
		{
			stdDrawable->SetIconImage(pImage, stateIndex);
		}

		return true;
	}
}
