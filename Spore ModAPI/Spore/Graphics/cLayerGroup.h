#pragma once

#include <Spore\Graphics\ILayer.h>
#include <Spore\Object.h>
#include <EASTL\vector.h>

#define cLayerGroupPtr eastl::intrusive_ptr<Graphics::cLayerGroup>

namespace Graphics
{
	/// An implementation of ILayer that renders a sequence of layers
	class cLayerGroup
		: public ILayer
		, public IVirtual
	{
	public:
		cLayerGroup();

		void Add(ILayer* layer, int layerIndex, int flags);
		
		int AddRef() override;
		int Release() override;
		void DrawLayer(int flags, int layerIndex, App::cViewer**, RenderStatistics&) override;

	private:
		struct cLayerInfo {
			ILayerPtr pRenderable;
			int layer;
			int flags;
		};

		/* 08h */	int mnRefCount;
		/* 0Ch */	eastl::vector<cLayerInfo> mEntries;
	};
	ASSERT_SIZE(cLayerGroup, 0x20);
}