#pragma once

#include <EASTL\intrusive_ptr.h>

#define IEffectMapPtr eastl::intrusive_ptr<Swarm::IEffectMap>

namespace Swarm
{
	class IEffectMap
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;

		//PLACEHOLDER
	};
}