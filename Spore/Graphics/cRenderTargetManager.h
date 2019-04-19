#pragma once

#include <Spore\Graphics\IRenderTargetManager.h>
#include <Spore\App\IMessageListener.h>
#include <Spore\Object.h>
#include <EASTL\vector.h>

namespace Graphics
{
	class cRenderTargetManager
		: public IRenderTargetManager
		, public App::IMessageListener
		, public DefaultRefCounted
	{
	public:

	public:
		/* 10h */	bool mbInitialized;
		/* 14h */	int field_14;
		/* 18h */	vector<int> field_18;
	};

	static_assert(sizeof(cRenderTargetManager) == 0x2C, "sizeof(cRenderTargetManager) != 2Ch");
}