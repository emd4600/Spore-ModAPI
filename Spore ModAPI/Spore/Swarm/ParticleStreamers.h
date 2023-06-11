#pragma once

namespace Swarm
{
	class IModelParticleRenderer;
	class ITextureParticleRenderer;

	class IModelParticleStreamer
	{
	public:
		/* 00h */	virtual void StreamModelParticles(IModelParticleRenderer* modelRenderer) = 0;
	};

	class ITextureParticleStreamer
	{
	public:
		/* 00h */	virtual void StreamTextureParticles(ITextureParticleRenderer* particleRenderer) = 0;
	};
}