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

#include <SourceCode\Utility.h>

namespace UTFWin
{
	//// ImageDrawable ////

	auto_STATIC_METHOD(IImageDrawable, IWindow*, AddImageWindow,
		PARAMS(const ResourceKey& imageName, float offsetX, float offsetY, IWindow* parentWindow),
		PARAMS(imageName, offsetX, offsetY, parentWindow));

	DEFAULT_REFCOUNT(ImageDrawable);

	auto_METHOD_VIRTUAL_VOID(ImageDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ImageDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(ImageDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(ImageDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));

	auto_METHOD_VIRTUAL_(ImageDrawable, IImageDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetImage, PARAMS(Image* pImage), PARAMS(pImage));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, Image*, GetImage);
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, int, GetImageDrawableFlags);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetImageDrawableFlags, PARAMS(int flags), PARAMS(flags));
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetImageDrawableFlag, PARAMS(int flag, bool bValue), PARAMS(flag, bValue));
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetTiling, PARAMS(ImageTiling tiling), PARAMS(tiling));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, ImageTiling, GetTiling);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetScale, PARAMS(float fScale), PARAMS(fScale));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, float, GetScale);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetAlignmentHorizontal, PARAMS(AlignmentH alignment), PARAMS(alignment));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, AlignmentH, GetAlignmentHorizontal);
	auto_METHOD_VIRTUAL_VOID(ImageDrawable, IImageDrawable, SetAlignmentVertical, PARAMS(AlignmentV alignment), PARAMS(alignment));
	auto_METHOD_VIRTUAL_const_(ImageDrawable, IImageDrawable, AlignmentV, GetAlignmentVertical);


	void* ImageDrawable::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(StdDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(StdDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(StdDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(StdDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(StdDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(StdDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));

	auto_METHOD_VIRTUAL_const(StdDrawable, IStdDrawable, Image*, GetImage, PARAMS(StateIndices index), PARAMS(index));
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetImage, PARAMS(StateIndices index, Image* pImage), PARAMS(index, pImage));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, Scaling, GetScaleType);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetScaleType, PARAMS(Scaling value), PARAMS(value));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, const Math::Rectangle&, GetScaleArea);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetScaleArea, PARAMS(const Math::Rectangle& value), PARAMS(value));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, const Vector2&, GetScaleFactor);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetScaleFactor, PARAMS(Vector2& value), PARAMS(value));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, Object*, GetHitMask);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetHitMask, PARAMS(Object* pHitMask), PARAMS(pHitMask));
	auto_METHOD_VIRTUAL_const_(StdDrawable, IStdDrawable, float, GetHitFactor);
	auto_METHOD_VIRTUAL_VOID(StdDrawable, IStdDrawable, SetHitFactor, PARAMS(float value), PARAMS(value));

	void* StdDrawable::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(ComboBoxDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(ComboBoxDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ComboBoxDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ComboBoxDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(ComboBoxDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(ComboBoxDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));

	auto_METHOD_VIRTUAL_const(ComboBoxDrawable, ComboBoxDrawable, Image*, GetImage, PARAMS(int index), PARAMS(index));

	auto_METHOD_VIRTUAL_(ComboBoxDrawable, IComboBoxDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ComboBoxDrawable, IComboBoxDrawable, SetImage, PARAMS(int index, Image* pImage), PARAMS(index, pImage));

	void* ComboBoxDrawable::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(ScrollbarDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(ScrollbarDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ScrollbarDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ScrollbarDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(ScrollbarDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(ScrollbarDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));

	auto_METHOD_VIRTUAL_(ScrollbarDrawable, IScrollbarDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ScrollbarDrawable, IScrollbarDrawable, SetImage, PARAMS(int index, Image* pImage), PARAMS(index, pImage));

	void* ScrollbarDrawable::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(SliderDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(SliderDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(SliderDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(SliderDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(SliderDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(SliderDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));

	auto_METHOD_VIRTUAL_(SliderDrawable, ISliderDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(SliderDrawable, ISliderDrawable, SetImage, PARAMS(int index, Image* pImage), PARAMS(index, pImage));

	void* SliderDrawable::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(SpinnerDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(SpinnerDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(SpinnerDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(SpinnerDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(SpinnerDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(SpinnerDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));

	auto_METHOD_VIRTUAL_(SpinnerDrawable, ISpinnerDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(SpinnerDrawable, ISpinnerDrawable, SetImage, PARAMS(int index, Image* pImage), PARAMS(index, pImage));

	void* SpinnerDrawable::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(DialogDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(DialogDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(DialogDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(DialogDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(DialogDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(DialogDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));

	auto_METHOD_VIRTUAL_(DialogDrawable, IDialogDrawable, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(DialogDrawable, IDialogDrawable, SetImage, PARAMS(int index, Image* image), PARAMS(index, image));
	auto_METHOD_VIRTUAL_const(DialogDrawable, IDialogDrawable, Color, GetBackgroundColor, PARAMS(Color& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_VOID(DialogDrawable, IDialogDrawable, SetBackgroundColor, PARAMS(Color color), PARAMS(color));
	auto_METHOD_VIRTUAL_const(DialogDrawable, IDialogDrawable, BackgroundTiling, GetBackgroundTiling, PARAMS(BackgroundTiling& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_VOID(DialogDrawable, IDialogDrawable, SetBackgroundTiling, PARAMS(BackgroundTiling value), PARAMS(value));


	void* DialogDrawable::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(ButtonDrawableStandard, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(ButtonDrawableStandard, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ButtonDrawableStandard, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ButtonDrawableStandard, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(ButtonDrawableStandard, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(ButtonDrawableStandard, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));
	auto_METHOD_VIRTUAL_const(ButtonDrawableStandard, IDrawable, bool, GetTexCoords, PARAMS(int state, Math::Rectangle& dst), PARAMS(state, dst));

	auto_METHOD_VIRTUAL_(ButtonDrawableStandard, IButtonDrawableStandard, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ButtonDrawableStandard, IButtonDrawableStandard, SetImage, PARAMS(Image* image, bool bTileable), PARAMS(image, bTileable));


	void* ButtonDrawableStandard::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(ButtonDrawableRadio, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(ButtonDrawableRadio, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(ButtonDrawableRadio, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(ButtonDrawableRadio, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(ButtonDrawableRadio, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(ButtonDrawableRadio, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));
	auto_METHOD_VIRTUAL_const(ButtonDrawableRadio, IDrawable, bool, GetTexCoords, PARAMS(int state, Math::Rectangle& dst), PARAMS(state, dst));

	auto_METHOD_VIRTUAL_(ButtonDrawableRadio, IButtonDrawableRadio, IDrawable*, ToDrawable);
	auto_METHOD_VIRTUAL_VOID(ButtonDrawableRadio, IButtonDrawableRadio, SetImage, PARAMS(Image* image, bool bTileable), PARAMS(image, bTileable));


	void* ButtonDrawableRadio::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(FrameDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(FrameDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(FrameDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(FrameDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(FrameDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(FrameDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));


	void* FrameDrawable::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(VariableWidthDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(VariableWidthDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(VariableWidthDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(VariableWidthDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(VariableWidthDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(VariableWidthDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));


	void* VariableWidthDrawable::Cast(uint32_t type) {
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

	auto_METHOD_VIRTUAL_VOID(SporeStdDrawableImageInfo, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
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

	auto_METHOD_VIRTUAL_VOID(SporeStdDrawable, ILayoutElement, SetSerializer, PARAMS(Serializer& dst), PARAMS(dst));
	auto_METHOD_VIRTUAL_const_(SporeStdDrawable, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(SporeStdDrawable, IDrawable, Paint, PARAMS(UIRenderer* pRenderer, const Math::Rectangle& area, const RenderParams& params), PARAMS(pRenderer, area, params));
	auto_METHOD_VIRTUAL(SporeStdDrawable, IDrawable, bool, IsColliding, PARAMS(const Math::Rectangle& area, const Math::Point& point, RenderParams& params), PARAMS(area, point, params));
	auto_METHOD_VIRTUAL(SporeStdDrawable, IDrawable, bool, GetDimensions, PARAMS(Dimensions& dst, int state, int index), PARAMS(dst, state, index));
	auto_METHOD_VIRTUAL(SporeStdDrawable, IDrawable, bool, UseCollision, PARAMS(uint32_t type, bool& dst), PARAMS(type, dst));
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

	void* SporeStdDrawable::Cast(uint32_t type) {
		if (type == SporeStdDrawable::TYPE)
		{
			return (SporeStdDrawable*) this;
		}
		else
		{
			return StdDrawable::Cast(type);
		}
	}


	void* IDrawable::Cast(uint32_t type)
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
}
