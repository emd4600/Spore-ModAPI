#include "stdafx.h"
#include "MyRenderable.h"

MyRenderable::MyRenderable()
{
}

MyRenderable::~MyRenderable()
{
}

// For internal use, do not modify.
int MyRenderable::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int MyRenderable::Release()
{
	return DefaultRefCounted::Release();
}


void MyRenderable::DrawLayer(int flags, int layerIndex, App::cViewer**, Graphics::RenderStatistics& stats)
{
	// Do your rendering.
}
