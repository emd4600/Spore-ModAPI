#pragma once

#include <Spore\Graphics\ILayer.h>
#include <Spore\Object.h>
#include <EASTL\vector.h>

#define SequenceRenderablePtr eastl::intrusive_ptr<Graphics::SequenceRenderable>

namespace Graphics
{
	/// An implementation of ILayer that renders a sequence of layers
	class SequenceRenderable
		: public ILayer
		, public IVirtual
	{
	public:
		SequenceRenderable();

		void Add(ILayer* layer, int layerIndex, int flags);
		
		int AddRef() override;
		int Release() override;
		void DrawLayer(int flags, int layerIndex, App::cViewer**, RenderStatistics&) override;

	private:
		struct Entry {
			ILayerPtr pRenderable;
			int layer;
			int flags;
		};

		/* 08h */	int mnRefCount;
		/* 0Ch */	vector<Entry> mEntries;
	};
	ASSERT_SIZE(SequenceRenderable, 0x20);
}