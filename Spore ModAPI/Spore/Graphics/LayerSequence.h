#pragma once

#include <Spore\Graphics\ILayer.h>
#include <Spore\Object.h>
#include <EASTL\intrusive_ptr.h>
#include <EASTL\vector.h>

#define LayerSequencePtr eastl::intrusive_ptr<Graphics::LayerSequence>

namespace Graphics
{
	class LayerSequence
		: public ILayer
		, public RefCountTemplate
	{
	public:
		virtual int AddRef() override;
		virtual int Release() override;
		virtual ~LayerSequence();
		virtual void DrawLayer(int flags, int layerIndex, App::cViewer** viewers, RenderStatistics& statistics) override;

		inline void AddLayer(ILayer* layer, int index, int flags) {
			mLayers.push_back({layer, index, flags});
		}

	public:
		struct SequenceLayer {
			ILayerPtr layer;
			int layerIndex;
			int flags;
		};

		eastl::vector<SequenceLayer> mLayers;
	};
	ASSERT_SIZE(LayerSequence, 0x20);
}