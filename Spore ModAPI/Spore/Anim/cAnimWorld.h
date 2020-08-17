#pragma once

#include <Spore\Anim\IAnimWorld.h>

namespace Anim
{
	class cAnimWorld : public IAnimWorld
	{
	protected:
		/* 0Ch */	string16 mName;
		/* 1Ch */	IAnimManagerPtr mpManager;

		/* 24h */	vector<AnimatedCreaturePtr> mCreatures;

		/* 44h */	IModelWorldPtr mpModelWorld;

		/* 4Ch */	IEffectWorldPtr	mpEffectWorld;


	};
}