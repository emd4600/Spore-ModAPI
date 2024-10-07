#pragma once

#include <Spore\Simulator\cGameData.h>

namespace Simulator
{
	struct cLayoutSlot 
	{
		void SetObject(cGameData* object);
		void RemoveObject(cGameData* object);

		/* 00h */	bool mIsOccupied;
		/// A building, turret, ornament, etc
		/* 04h */	cGameDataPtr mpObject;
		/* 08h */	int field_8; // 0
		/* 0Ch */	Math::Vector3 mPosition;
	};
	ASSERT_SIZE(cLayoutSlot, 0x18);

	namespace Addresses(cLayoutSlot)
	{
		DeclareAddress(SetObject);  // 0xAF9890 0xAF9FB0
		DeclareAddress(RemoveObject);  // 0xAF9900 0xAFA020
	}

	/// Also used by Tribe, related with city layout
	struct cCommunityLayout
	{
	public:
		void SetParameters(const Math::Vector3& origin, float, const Math::Vector3& direction, float);

		/// Initializes the layout with all empty slots, in the specified positions.
		void InitializeSlots(const eastl::vector<Math::Vector3>& positions, float);

		/// Moves all existing slots to be on the surface of the planet.
		void SnapSlotsToPlanet();

	public:
		/// Local Y axis
		/* 00h */	Vector3 mDirection;
		/* 0Ch */	float field_C;  // -1.0
		/* 10h */	float field_10;  // -1.0
		/* 14h */	Vector3 mOrigin;
		/* 20h */	float field_20;
		/* 24h */	int field_24;  // not initialized
		/* 28h */	bool field_28;
		/* 2Ch */	Quaternion field_2C;
		/* 3Ch */	eastl::vector<int> field_3C;
		/* 50h */	eastl::vector<cLayoutSlot> mSlots;
	};
	ASSERT_SIZE(cCommunityLayout, 0x64);

	namespace Addresses(cCommunityLayout) 
	{
		DeclareAddress(InitializeSlots);  // 0xAFE620 0xAFEB80
		DeclareAddress(SnapSlotsToPlanet);  // 0xAFA690 0xAFAE40
		DeclareAddress(SetParameters);  // 0xAF95D0 0xAF9C70
	}
}