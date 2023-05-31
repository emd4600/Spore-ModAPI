#pragma once

#include <Spore\MathUtils.h>
#include <Spore\Object.h>
#include <EASTL\intrusive_ptr.h>

#define IEffectMapPtr eastl::intrusive_ptr<Swarm::IEffectMap>

namespace Swarm
{
	/// Effect maps are one of the way effects can react to environment information from the game. 
	/// Effect maps are used to retrieve color, height, normal, or velocity information that changes on each point in space.
	/// More information: https://github.com/emd4600/SporeModder-FX/wiki/Effect-Maps
	class IEffectMap
	{
	public:
		/* 00h */	virtual int AddRef() = 0;
		/* 04h */	virtual int Release() = 0;

		/* 08h */	virtual void Start() = 0;
		/* 0Ch */	virtual void Finish() = 0;
		/* 10h */	virtual int ModificationCount() = 0;

		/// Returns the bounding box that contains the whole map.
		/// @returns
		/* 14h */	virtual Math::BoundingBox GetBounds() = 0;

		/// Returns whether the given point is considered to be inside of the map.
		/// @param position
		/// @returns
		/* 18h */	virtual bool PointInMap(const Math::Vector3& position) = 0;

		/// Returns whether this map is in world space or not.
		/// @returns
		/* 1Ch */	virtual bool InWorldSpace() = 0;

		/// Returns the height of the map at the given position.
		/// @param position
		/// @returns
		/* 20h */	virtual float Height(const Math::Vector3& position) = 0;

		/// Returns the normal direction of the map at the given position.
		/// @param position
		/// @returns
		/* 24h */	virtual Math::Vector3 Normal(const Math::Vector3& position) = 0;

		/// Returns the velocity (i.e., speed with direction) of the map at the given position.
		/// @param position
		/// @returns
		/* 28h */	virtual Math::Vector3 Velocity(const Math::Vector3& position) = 0;

		/// Returns the RGBA color of the map at the given position.
		/// @param unk
		/// @returns
		/* 2Ch */	virtual Math::ColorRGBA ColorAlpha(void* unk) = 0;
	};

	class cEffectMapBase
		: public IEffectMap
		, public RefCountTemplate
	{
	public:
		virtual ~cEffectMapBase();

		/* 08h */	virtual void Start() override;
		/* 0Ch */	virtual void Finish() override;
		/* 10h */	virtual int ModificationCount() override;

		/* 20h */	virtual float Height(const Math::Vector3& position) override;
		/* 24h */	virtual Math::Vector3 Normal(const Math::Vector3& position) override;
		/* 28h */	virtual Math::Vector3 Velocity(const Math::Vector3& position) override;
		/* 2Ch */	virtual Math::ColorRGBA ColorAlpha(void* unk) override;
	};
	ASSERT_SIZE(cEffectMapBase, 0xC);
}