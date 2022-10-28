#pragma once

#include <Spore\Graphics\IRenderable.h>
#include <Spore\Object.h>
#include <EASTL\vector.h>

#define SequenceRenderablePtr eastl::intrusive_ptr<Graphics::SequenceRenderable>

namespace Graphics
{
	/// An implementation of IRenderable that renders a sequence of IRenderables
	class SequenceRenderable
		: public IRenderable
		, public IVirtual
	{
	public:
		SequenceRenderable();

		void Add(IRenderable* renderable, int layer, int flags);
		
		int AddRef() override;
		int Release() override;
		void Render(int flags, int layerIndex, App::cViewer**, RenderStatistics&) override;

	private:
		struct Entry {
			IRenderablePtr pRenderable;
			int layer;
			int flags;
		};

		/* 08h */	int mnRefCount;
		/* 0Ch */	vector<Entry> mEntries;
	};
	ASSERT_SIZE(SequenceRenderable, 0x20);
}