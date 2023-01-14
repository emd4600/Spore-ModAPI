#pragma once

#include <Spore\BasicIncludes.h>

// In order to use this renderable, you can add it on a IGameMode::OnEnter() method and remove it on a IGameMode::OnExit(),
// using the following:
// 		Renderer.RegisterLayer(new MyRenderable(), Graphics::kRenderQueueMain);
// 		Renderer.UnregisterLayer(Graphics::kRenderQueueMain);
//
// Instead of Graphics::kRenderQueueMain you might need to use other numbers, modify it accordingly. 
class MyRenderable 
	: public Graphics::ILayer
	, public DefaultRefCounted
{
public:
	MyRenderable();
	~MyRenderable();

	int AddRef() override;
	int Release() override;
	void DrawLayer(int flags, int layerIndex, App::cViewer**, Graphics::RenderStatistics& stats) override;
};
