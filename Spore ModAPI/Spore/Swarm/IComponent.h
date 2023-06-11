#pragma once

#include <Spore\Swarm\IVisualEffect.h>
#include <Spore\Swarm\Components\cDescription.h>

namespace Swarm
{
	class IEffectsWorld;
	class IEffectsManager;

#ifdef SDK_TO_GHIDRA
	struct cEffectParams { int todo; };
	struct cComponentStats { int todo; };
#else
	struct cEffectParams;  //TODO
	struct cComponentStats;  //TODO
#endif

	class IComponent
	{
	public:
		/* 00h */	virtual void Initialize(IEffectsWorld* world, IEffectsManager* manager, cEffectParams* params) = 0;
		/* 04h */	virtual void Dispose() = 0;
		/* 08h */	virtual void Start(int hardStart = 1) = 0;
		/* 0Ch */	virtual int Stop(int hardStop = 1) = 0;
		/* 10h */	virtual int IsRunning() = 0;
		/* 14h */	virtual void ApplyEffect(float, float, cComponentStats*) = 0;
		/* 18h */	virtual void SetTransforms(const Transform& sourceTransform, const Transform& rigidTransform) = 0;
		/* 20h */	virtual bool SetFloatParams(FloatParams param, const float* data, int count) = 0;
		/* 24h */	virtual bool SetIntParams(IntParams param, const int* data, int count) = 0;
		/* 28h */	virtual bool SetUnknownParam(ObjectParams param, Object* data) = 0;
		/* 2Ch */	virtual void SetIsVisible(bool visible) = 0;
		/* 30h */	virtual void SetChainEffect(IComponent* component) = 0;
		/* 34h */	virtual void SwitchDescription(Swarm::cDescription* description) = 0;
		/* 38h */	virtual int AddRef() = 0;
		/* 3Ch */	virtual int Release() = 0;
	};

	class cComponentBase
		: public IComponent
		, public RefCountTemplate
	{
	};
	ASSERT_SIZE(cComponentBase, 0xC);
}