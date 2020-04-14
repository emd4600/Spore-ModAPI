#ifndef MODAPI_DLL_EXPORT
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

#include <Spore\UTFWin\Image.h>

#include <EASTL\internal\thread_support.h>

namespace UTFWin
{
	auto_METHOD_VIRTUAL_VOID(Image, Image, SetSerializer, Args(Serializer& dst), Args(dst));
	auto_METHOD_VIRTUAL_const_(Image, Image, uint32_t, GetProxyID);

	auto_STATIC_METHOD(Image, bool, GetImage,
		Args(const ResourceKey& name, ImagePtr& dst, bool arg_8, int arg_C, int arg_10),
		Args(name, dst, arg_8, arg_C, arg_10));

	auto_STATIC_METHOD(Image, bool, SetBackground,
		Args(IWindow* pWindow, Image* pImage, int nImageIndex),
		Args(pWindow, pImage, nImageIndex));

	auto_STATIC_METHOD(Image, bool, SetBackgroundByKey,
		Args(IWindow* pWindow, const ResourceKey imageName, int nImageIndex),
		Args(pWindow, imageName, nImageIndex));

	int Image::AddRef()
	{
		return eastl::Internal::atomic_increment(&mnRefCount);
	}
	int Image::Release()
	{
		if (eastl::Internal::atomic_decrement(&mnRefCount) == 0)
		{
			delete this;
		}
		return mnRefCount;
	}
	void* Image::Cast(uint32_t type) const
	{
		if (type == Object::TYPE || type == ILayoutElement::TYPE)
		{
			return (ILayoutElement*) this;
		}
		else if (type == Image::TYPE)
		{
			return (Image*) this;
		}
		else if (type == Image::TYPE_DIMENSIONS)
		{
			return (Math::Dimensions*) &mDimensions;
		}
		else
		{
			return nullptr;
		}
	}
}
#endif
