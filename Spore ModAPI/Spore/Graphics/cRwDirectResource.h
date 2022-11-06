#pragma once

#include <Spore\Resource\ResourceObject.h>
#include <Spore\RenderWare\Raster.h>

#define cRwRasterDirectResourcePtr eastl::intrusive_ptr<Graphics::cRwRasterDirectResource>

namespace Graphics
{
	template <typename ObjClass, uint32_t TYPE_ID>
	class cRwDirectResource
		: public Resource::ResourceObject
	{
	public:
		static const uint32_t TYPE = TYPE_ID;

		inline ObjClass* GetData() {
			return mpObject;
		}

	public:
		/* 14h */	int field_14;
		/* 18h */	ObjClass* mpObject;
	};

	typedef cRwDirectResource<RenderWare::Raster, 0x2F4E681C> cRwRasterDirectResource;
}