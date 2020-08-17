#pragma once

#include <Spore\Graphics\IRenderable.h>
#include <Spore\Graphics\IModelWorld.h>
#include <Spore\Swarm\IEffectWorld.h>
#include <Spore\Anim\AnimatedCreature.h>
#include <Spore\Object.h>

#define IAnimWorldPtr intrusive_ptr<Anim::IAnimWorld>

namespace Anim
{
	typedef float(*AnimFunction)(void* object, AnimatedCreature* creature, const Quaternion&, Vector3* dstNormal, bool, bool);

	class IAnimWorld
		: public Graphics::IRenderable
		, public DefaultRefCounted
	{
	public:
		using IRenderable::AddRef;
		using IRenderable::Release;

		// second argument is function, sub_B36750 for planets and sub_572BE0 for editor
		/* 10h */	virtual void func10h(bool, AnimFunction, void* object) = 0;
		/* 14h */	virtual void func14h(bool) = 0;
		/* 18h */	virtual void SetEffectWorld(Swarm::IEffectWorld*) = 0;
		// arg_8 is ignored
		// arg_4 does something with model when loading creature
		/* 1Ch */	virtual bool SetModelWorld(Graphics::IModelWorld*, bool = true, int = 1, bool = true, bool = false) = 0;
		/* 20h */	virtual bool Dispose() = 0;
		// first argument is delta seconds?, calls func28h 
		// does something with all creatures, which are at 24h vector
		// when finishes calls func2Ch
		/* 24h */	virtual void Update(float deltaTime, App::cViewer* = nullptr) = 0;  // must be called every frame?
		/* 28h */	virtual void UpdateCreatures(float deltaTime, App::cViewer* = nullptr) = 0;
		/* 2Ch */	virtual void PostUpdateCreatures(float deltaTime, App::cViewer* = nullptr) = 0;
		// model is not visible by default
		/* 30h */	virtual AnimatedCreature* LoadCreature(const ResourceKey& key, int = 2, const Vector3& = Vector3(), const Vector3& = Vector3(), bool = true) = 0;
		/* 34h */	virtual int func34h(int, int, int, int, int) = 0;
		// Loads a *.blocks file
		/* 38h */	virtual int LoadCreatureByName(const char*, int, int, int, int, int) = 0;
		// this is called by AnimatedCreature destructor, users shouldn't call it
		/* 3Ch */	virtual void DestroyCreature(AnimatedCreature*) = 0;
		// int is second argument of func30h too
		/* 40h */	virtual int func40h(AnimatedCreature*, int, bool) = 0;
		/* 44h */	virtual const vector<AnimatedCreature*>& GetCreatures() const = 0;
		/* 48h */	virtual void func48h(int index, int) = 0;  // related with lod max
		/* 4Ch */	virtual int func4Ch(int index) = 0;
		/* 50h */	virtual void func50h(bool) = 0;
		/* 54h */	virtual bool func54h() = 0;
		/* 58h */	virtual bool func58h() = 0;
	};
}