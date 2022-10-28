#pragma once

#include <Spore\Graphics\IRenderManager.h>
#include <Spore\App\IMessageManager.h>
#include <Spore\Object.h>
#include <Spore\Mutex.h>
#include <Spore\Clock.h>
#include <EASTL\vector.h>
#include <EASTL\intrusive_ptr.h>

namespace Graphics
{
	using namespace eastl;

	class cRenderManager
		: public IRenderManager
		, public IVirtual
	{
	protected:

		/* 28h */	Mutex mMutex;

		/* 58h */	App::IMessageManager* mpMessageMgr;
		/* 5Ch */	RenderererParams mRenderParams;

		/* 74h */	float mDisplayAspectRatio;

		/* 8Ch */	vector<RenderLayer> mRenderLayers;

		// /* 34Ch */	vector<RenderLayer> mRenderLayers;

		/* 5E8h */	Clock field_5E8;

		/* 608h */	RenderStatistics mStatistics;

		// 638h is Gamma?
	};
}
