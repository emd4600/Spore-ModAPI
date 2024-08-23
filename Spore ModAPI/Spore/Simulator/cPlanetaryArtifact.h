#pragma once

#include <Spore\Simulator\cMovableDestructibleOrnament.h>
#include <Spore\Simulator\SimulatorEnums.h>

#define cPlanetaryArtifactPtr eastl::intrusive_ptr<Simulator::cPlanetaryArtifact>

namespace Simulator
{
	class cPlanetaryArtifact
		: public cMovableDestructibleOrnament
	{
	public:
		static const uint32_t TYPE = 0x2DD8C33;
		static const uint32_t NOUN_ID = 0x2DD8C42;

		using Object::AddRef;
		using Object::Release;
		using Object::Cast;

		/// Creates a `cGroundLocomotion` locomotion strategy, and adds this object to the behavior manager.
		void SetLocomotion();

		void LoadFromItem(SpaceInventoryItemType itemType, const ResourceKey& itemKey, int count, bool);

	public:
		/* 638h */	int mItemCount;
		/* 63Ch */	PropertyListPtr mItemPropList;
		/* 640h */	int field_640;
		/* 644h */	float mInventoryItemArtifactPlumpScale;  // not initialized
		/* 648h */	float mInventoryItemArtifactNormalScale;  // not initialized
		/* 64Ch */	ResourceKey mInventoryItemKey;
		/* 658h */	SpaceInventoryItemType mItemType;  // -1
		/* 65Ch */	bool field_65C;
		/* 65Dh */	bool field_65D;
		/* 65Eh */	bool field_65E;  // true
		/* 660h */	float field_660;  // -1
	};
	ASSERT_SIZE(cPlanetaryArtifact, 0x668);

	namespace Addresses(cPlanetaryArtifact)
	{
		DeclareAddress(SetLocomotion);  // 0xC687D0 0xC69230
		DeclareAddress(LoadFromItem);  // 0xC73F90 0xC74ED0
	}
}