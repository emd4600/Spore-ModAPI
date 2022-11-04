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

#include <Spore\Graphics\IRenderer.h>
#include <Spore\Graphics\LambdaRenderable.h>
#include <Spore\Graphics\SequenceRenderable.h>
#include <Spore\Graphics\RenderUtils.h>
#include <Spore\Graphics\GlobalState.h>

namespace Graphics
{

	auto_STATIC_METHOD_(IRenderer, IRenderer*, Get);

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
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}

	void LambdaRenderable::Render(int arg_0, int arg_4, App::cViewer** arg_8, RenderStatistics& arg_C)
	{
		mFunction(arg_0, arg_4, arg_8, arg_C);
	}



	SequenceRenderable::SequenceRenderable()
		: mnRefCount(0)
		, mEntries()
	{}

	int SequenceRenderable::AddRef()
	{
		++mnRefCount;
		return mnRefCount;
	}

	int SequenceRenderable::Release()
	{
		--mnRefCount;
		if (mnRefCount == 0) {
			delete this;
			return 0;
		}
		return mnRefCount;
	}

	void SequenceRenderable::Add(IRenderable* renderable, int layer, int flags) 
	{
		auto it = mEntries.begin();
		while (it != mEntries.end() && layer > it->layer) ++it;

		if (it == mEntries.end()) {
			mEntries.push_back({ renderable, layer, flags });
		}
		else {
			mEntries.insert(it, { renderable, layer, flags });
		}
	}

	void SequenceRenderable::Render(int, int, App::cViewer** arg_8, RenderStatistics& arg_C)
	{
		for (auto& entry : mEntries) {
			entry.pRenderable->Render(entry.flags, entry.layer, arg_8, arg_C);
		}
	}



	auto_STATIC_METHOD_VOID(RenderUtils, SetShaderData,
		Args(short index, void* value, bool overrideIfEqual), Args(index, value, overrideIfEqual));

	auto_STATIC_METHOD(RenderUtils, int, GetShaderDataSize, Args(short index), Args(index));

	auto_STATIC_METHOD(RenderUtils, void, RegisterShaderData,
		Args(short index, ShaderDataInformation::UnfixCB arg_4, ShaderDataInformation::RefixCB arg_8, ShaderDataInformation::FixupCB arg_C, ShaderDataInformation::UploadCB loadFunction),
		Args(index, arg_4, arg_8, arg_C, loadFunction));

	auto_STATIC_METHOD_VOID(RenderUtils, SetTexture, Args(int slotIndex, RenderWare::Raster* raster), Args(slotIndex, raster));


	namespace GlobalState
	{
		auto_STATIC_METHOD_VOID_(GlobalState, D3D9Sync);
		auto_STATIC_METHOD_VOID_(GlobalState, Dispatch);

		MatrixType GetTransformType() {
			return *(MatrixType*)GetAddress(GlobalState, transformType_ptr);
		}
		Math::Matrix4* GetTransform() {
			return *(Math::Matrix4**)GetAddress(GlobalState, transform_ptr);
		}
		auto_STATIC_METHOD_VOID(GlobalState, SetTransform,
			Args(const Math::Matrix4& matrix, MatrixType type), Args(matrix, type));

		Math::ColorRGBA& GetColor() {
			return *(Math::ColorRGBA*)GetAddress(GlobalState, color_ptr);
		}
		void SetColor(const Math::ColorRGBA& color) {
			SetSoftStateDirty(kSoftStateColor | GetSoftStateDirty());
			*(Math::ColorRGBA*)GetAddress(GlobalState, color_ptr) = color;
		}

		int GetSoftStateDirty() {
			return *(int*)GetAddress(GlobalState, softStateDirty_ptr);
		}
		void SetSoftStateDirty(int state) {
			*(int*)GetAddress(GlobalState, softStateDirty_ptr) = state;
		}

		int* GetRenderStates() {
			return (int*)GetAddress(GlobalState, renderStates_ptr);
		}
		eastl::bitset<203>& GetRenderStateDirty() {
			return *(eastl::bitset<203>*)GetAddress(GlobalState, renderStateDirty_ptr);
		}
	}
}
#endif
