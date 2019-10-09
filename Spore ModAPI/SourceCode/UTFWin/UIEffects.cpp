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

#include <Spore\UTFWin\Effect.h>
#include <Spore\UTFWin\CascadeEffect.h>
#include <Spore\UTFWin\GlideEffect.h>
#include <Spore\UTFWin\InflateEffect.h>
#include <Spore\UTFWin\ModulateEffect.h>
#include <Spore\UTFWin\PerspectiveEffect.h>
#include <Spore\UTFWin\RotateEffect.h>
#include <Spore\UTFWin\FadeEffect.h>

namespace UTFWin
{
	int BiStateEffect::func80h() { return 0; };
	void BiStateEffect::func84h(int, float) {};
	void BiStateEffect::func88h(int, int, int) {};

	uint32_t BiStateEffect::GetProxyID() const
	{
		return 0x4F2B639E;
	}

	BiStateEffect::BiStateEffect()
		: mfTime(0)
		, mClock()
		, mTriggerType(TriggerType::Invisible)
		, mInterpolationType(InterpolationType::Linear)
		, mfEaseIn(0)
		, mfEaseOut(0)
		, mfDamping(0.1f)
		, field_44(0)
		, field_48(0)
		, field_4C(0)
		, field_50(false)
		, field_54(2)
		, field_58(0)
	{
		mClock.SetMode(Clock::Mode::Seconds);
	}

	void* BiStateEffect::Cast(uint32_t typeID) const
	{
		if (typeID == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (typeID == IWinProc::TYPE || typeID == Object::TYPE)
		{
			return (IWinProc*) this;
		}
		else if (typeID == IBiStateEffect::TYPE)
		{
			return (IBiStateEffect*) this;
		}
		else
		{
			return nullptr;
		}
	}

	auto_METHOD_VIRTUAL_VOID(BiStateEffect, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL(BiStateEffect, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	auto_METHOD_VIRTUAL_(BiStateEffect, IBiStateEffect, IWinProc*, ToWinProc);
	auto_METHOD_VIRTUAL_const_(BiStateEffect, IBiStateEffect, float, GetTime);
	auto_METHOD_VIRTUAL_VOID(BiStateEffect, IBiStateEffect, SetTime, Args(float value), Args(value));
	auto_METHOD_VIRTUAL_const_(BiStateEffect, IBiStateEffect, TriggerType, GetTriggerType);
	auto_METHOD_VIRTUAL_VOID(BiStateEffect, IBiStateEffect, SetTriggerType, Args(TriggerType value), Args(value));
	auto_METHOD_VIRTUAL_VOID_const(BiStateEffect, IBiStateEffect, GetEase, Args(float& easeIn, float& easeOut), Args(easeIn, easeOut));
	auto_METHOD_VIRTUAL_VOID(BiStateEffect, IBiStateEffect, SetEase, Args(float easeIn, float easeOut), Args(easeIn, easeOut));
	auto_METHOD_VIRTUAL_const_(BiStateEffect, IBiStateEffect, InterpolationType, GetInterpolationType);
	auto_METHOD_VIRTUAL_VOID(BiStateEffect, IBiStateEffect, SetInterpolationType, Args(InterpolationType value), Args(value));
	auto_METHOD_VIRTUAL_const_(BiStateEffect, IBiStateEffect, float, GetDamping);
	auto_METHOD_VIRTUAL_VOID(BiStateEffect, IBiStateEffect, SetDamping, Args(float value), Args(value));



	//// CASCADE EFFECT ////

	CascadeEffect::CascadeEffect()
		: mfDelay(0)
		, mfInterval(0.1f)
		, mClock()
		, field_30(0)
		, field_38(false)
		, field_3C(false)
	{
		mClock.SetMode(Clock::Mode::Milliseconds);
	}

	void* CascadeEffect::Cast(uint32_t typeID) const
	{
		if (typeID == ICascadeEffect::TYPE)
		{
			return (ICascadeEffect*) this;
		}
		else
		{
			return Effect::Cast(typeID);
		}
	}

	int	CascadeEffect::AddRef()
	{
		return Effect::AddRef();
	}

	int	CascadeEffect::Release()
	{
		return Effect::Release();
	}

	auto_METHOD_VIRTUAL_const_(CascadeEffect, IWinProc, int, GetEventFlags);
	auto_METHOD_VIRTUAL(CascadeEffect, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	auto_METHOD_VIRTUAL_VOID(CascadeEffect, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(CascadeEffect, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_(CascadeEffect, ICascadeEffect, IWinProc*, ToWinProc);
	auto_METHOD_VIRTUAL_const_(CascadeEffect, ICascadeEffect, float, GetDelay);
	auto_METHOD_VIRTUAL_VOID(CascadeEffect, ICascadeEffect, SetDelay, Args(float delay), Args(delay));
	auto_METHOD_VIRTUAL_const_(CascadeEffect, ICascadeEffect, float, GetInterval);
	auto_METHOD_VIRTUAL_VOID(CascadeEffect, ICascadeEffect, SetInterval, Args(float interval), Args(interval));


	//// GLIDE EFFECT ////

	GlideEffect::GlideEffect()
		: mOffset()
	{
	}

	void* GlideEffect::Cast(uint32_t typeID) const
	{
		if (typeID == IGlideEffect::TYPE)
		{
			return (IGlideEffect*) this;
		}
		else
		{
			return Effect::Cast(typeID);
		}
	}

	int	GlideEffect::AddRef()
	{
		return Effect::AddRef();
	}

	int	GlideEffect::Release()
	{
		return Effect::Release();
	}

	auto_METHOD_VIRTUAL_const_(GlideEffect, IWinProc, int, GetEventFlags);
	auto_METHOD_VIRTUAL(GlideEffect, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	auto_METHOD_VIRTUAL_VOID(GlideEffect, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(GlideEffect, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_(GlideEffect, IGlideEffect, IWinProc*, ToWinProc);
	auto_METHOD_VIRTUAL_const_(GlideEffect, IGlideEffect, const Point&, GetOffset);
	auto_METHOD_VIRTUAL_VOID(GlideEffect, IGlideEffect, SetOffset, Args(const Point& offset), Args(offset));

	auto_METHOD_VIRTUAL_(GlideEffect, BiStateEffect, int, func80h);
	auto_METHOD_VIRTUAL_VOID(GlideEffect, BiStateEffect, func88h, Args(int arg_0, int arg_4, int arg_8), Args(arg_0, arg_4, arg_8));


	//// INFLATE EFFECT ////

	InflateEffect::InflateEffect()
		: mfScale(1.0f)
	{
	}

	void* InflateEffect::Cast(uint32_t typeID) const
	{
		if (typeID == IInflateEffect::TYPE)
		{
			return (IInflateEffect*) this;
		}
		else
		{
			return Effect::Cast(typeID);
		}
	}

	int	InflateEffect::AddRef()
	{
		return Effect::AddRef();
	}

	int	InflateEffect::Release()
	{
		return Effect::Release();
	}

	auto_METHOD_VIRTUAL_const_(InflateEffect, IWinProc, int, GetEventFlags);
	auto_METHOD_VIRTUAL(InflateEffect, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	auto_METHOD_VIRTUAL_VOID(InflateEffect, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(InflateEffect, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_(InflateEffect, IInflateEffect, IWinProc*, ToWinProc);
	auto_METHOD_VIRTUAL_const_(InflateEffect, IInflateEffect, float, GetScale);
	auto_METHOD_VIRTUAL_VOID(InflateEffect, IInflateEffect, SetScale, Args(float scale), Args(scale));

	auto_METHOD_VIRTUAL_(InflateEffect, BiStateEffect, int, func80h);
	auto_METHOD_VIRTUAL_VOID(InflateEffect, BiStateEffect, func88h, Args(int arg_0, int arg_4, int arg_8), Args(arg_0, arg_4, arg_8));


	//// MODULATE EFFECT ////

	ModulateEffect::ModulateEffect()
		: mColor1()
		, mColor2()
	{
	}

	void* ModulateEffect::Cast(uint32_t typeID) const 
	{
		if (typeID == IModulateEffect::TYPE)
		{
			return (IModulateEffect*) this;
		}
		else
		{
			return Effect::Cast(typeID);
		}
	}

	int	ModulateEffect::AddRef()
	{
		return Effect::AddRef();
	}

	int	ModulateEffect::Release()
	{
		return Effect::Release();
	}

	auto_METHOD_VIRTUAL_const_(ModulateEffect, IWinProc, int, GetEventFlags);
	auto_METHOD_VIRTUAL(ModulateEffect, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	auto_METHOD_VIRTUAL_VOID(ModulateEffect, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(ModulateEffect, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_(ModulateEffect, IModulateEffect, IWinProc*, ToWinProc);
	auto_METHOD_VIRTUAL_const(ModulateEffect, IModulateEffect, void, GetColors, Args(Color& c1, Color& c2), Args(c1, c2));
	auto_METHOD_VIRTUAL_VOID(ModulateEffect, IModulateEffect, SetColors, Args(Color c1, Color c2), Args(c1, c2));

	auto_METHOD_VIRTUAL_VOID(ModulateEffect, BiStateEffect, func84h, Args(int arg_0, float arg_4), Args(arg_0, arg_4));


	//// PERSPECTIVE EFFECT ////

	PerspectiveEffect::PerspectiveEffect()
		: mfNearPlane(0)
	{
	}

	void* PerspectiveEffect::Cast(uint32_t typeID) const
	{
		if (typeID == IPerspectiveEffect::TYPE)
		{
			return (IPerspectiveEffect*) this;
		}
		else
		{
			return Effect::Cast(typeID);
		}
	}

	int	PerspectiveEffect::AddRef()
	{
		return Effect::AddRef();
	}

	int	PerspectiveEffect::Release()
	{
		return Effect::Release();
	}

	auto_METHOD_VIRTUAL_const_(PerspectiveEffect, IWinProc, int, GetEventFlags);
	auto_METHOD_VIRTUAL(PerspectiveEffect, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	auto_METHOD_VIRTUAL_VOID(PerspectiveEffect, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(PerspectiveEffect, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_(PerspectiveEffect, IPerspectiveEffect, IWinProc*, ToWinProc);
	auto_METHOD_VIRTUAL_const_(PerspectiveEffect, IPerspectiveEffect, float, GetNearPlane);
	auto_METHOD_VIRTUAL_VOID(PerspectiveEffect, IPerspectiveEffect, SetNearPlane, Args(float delay), Args(delay));

	auto_METHOD_VIRTUAL_VOID(PerspectiveEffect, PerspectiveEffect, func80h, Args(int arg_0), Args(arg_0));


	//// ROTATE EFFECT ////

	RotateEffect::RotateEffect()
		: mRotAxis(0, 0, 1.0f)
		, mfRotAngle(45.0f)
	{
	}

	void* RotateEffect::Cast(uint32_t typeID) const
	{
		if (typeID == IRotateEffect::TYPE)
		{
			return (IRotateEffect*) this;
		}
		else
		{
			return Effect::Cast(typeID);
		}
	}

	int	RotateEffect::AddRef()
	{
		return Effect::AddRef();
	}

	int	RotateEffect::Release()
	{
		return Effect::Release();
	}

	auto_METHOD_VIRTUAL_const_(RotateEffect, IWinProc, int, GetEventFlags);
	auto_METHOD_VIRTUAL(RotateEffect, IWinProc, bool, HandleUIMessage, Args(IWindow* pWindow, const Message& message), Args(pWindow, message));

	auto_METHOD_VIRTUAL_VOID(RotateEffect, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(RotateEffect, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_(RotateEffect, IRotateEffect, IWinProc*, ToWinProc);
	auto_METHOD_VIRTUAL_const_(RotateEffect, IRotateEffect, const Vector3&, GetRotationAxis);
	auto_METHOD_VIRTUAL_VOID(RotateEffect, IRotateEffect, SetRotationAxis, Args(const Vector3& delay), Args(delay));
	auto_METHOD_VIRTUAL_const_(RotateEffect, IRotateEffect, float, GetRotationAngle);
	auto_METHOD_VIRTUAL_VOID(RotateEffect, IRotateEffect, SetRotationAngle, Args(float delay), Args(delay));

	auto_METHOD_VIRTUAL_(RotateEffect, BiStateEffect, int, func80h);
	auto_METHOD_VIRTUAL_VOID(RotateEffect, BiStateEffect, func88h, Args(int arg_0, int arg_4, int arg_8), Args(arg_0, arg_4, arg_8));

	//// FADE EFFECT ////

	void* FadeEffect::Cast(uint32_t typeID) const
	{
		if (typeID == IRotateEffect::TYPE)
		{
			return (IRotateEffect*) this;
		}
		else
		{
			return Effect::Cast(typeID);
		}
	}

	int	FadeEffect::AddRef()
	{
		return Effect::AddRef();
	}

	int	FadeEffect::Release()
	{
		return Effect::Release();
	}

	auto_METHOD_VIRTUAL_VOID(FadeEffect, ILayoutElement, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(FadeEffect, ILayoutElement, uint32_t, GetProxyID);

	auto_METHOD_VIRTUAL_VOID(FadeEffect, BiStateEffect, func84h, Args(int arg_0, float arg_4), Args(arg_0, arg_4));
}