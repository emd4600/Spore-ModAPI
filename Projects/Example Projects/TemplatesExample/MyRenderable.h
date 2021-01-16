#pragma once

#include <Spore\BasicIncludes.h>

// In order to use this renderable, you can add it on a IGameMode::OnEnter() method and remove it on a IGameMode::OnExit(),
// using the following:
// 		RenderManager.AddRenderable(new MyRenderable(), Graphics::kRenderQueueMain);
// 		RenderManager.RemoveRenderable(Graphics::kRenderQueueMain);
//
// Instead of Graphics::kRenderQueueMain you might need to use other numbers, modify it accordingly. 
class MyRenderable 
	: public Graphics::IRenderable
	, public DefaultRefCounted
{
public:
	MyRenderable();
	~MyRenderable();

	int AddRef() override;
	int Release() override;
	void Render(int flags, int layerIndex, App::cViewer**, void*) override;
};
