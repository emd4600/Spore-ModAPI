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

#include <Spore\Graphics\IRenderManager.h>
#include <Spore\Graphics\LambdaRenderable.h>
#include <Spore\Graphics\Renderer.h>

namespace Graphics
{

	auto_STATIC_METHOD_(IRenderManager, IRenderManager*, Get);

	LambdaRenderable::LambdaRenderable(LambdaRenderable::Render_t function)
		: mnRefCount(0)
		, mFunction(function)
	{}

	int LambdaRenderable::AddRef()
	{
		++mnRefCount;
		return mnRefCount;
	}

	int LambdaRenderable::Release()
	{
		--mnRefCount;
		if (mnRefCount == 0) delete this;
		return mnRefCount;
	}

	void LambdaRenderable::Render(int arg_0, int arg_4, void* arg_8, void* arg_C)
	{
		mFunction(arg_0, arg_4, arg_8, arg_C);
	}


	auto_STATIC_METHOD_VOID(Renderer, SetShaderData, 
		Args(short index, void* value, bool overrideIfEqual), Args(index, value, overrideIfEqual));

	auto_STATIC_METHOD(Renderer, int, GetShaderDataSize, Args(short index), Args(index));

	auto_STATIC_METHOD_VOID(Renderer, SetTexture, Args(int slotIndex, RenderWare::Raster* raster), Args(slotIndex, raster));
}
#endif
